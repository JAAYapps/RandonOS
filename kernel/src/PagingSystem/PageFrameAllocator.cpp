#include "PageFrameAllocator.h"

uint64_t freeMemory;
uint64_t reservedMemory;
uint64_t usedMemory;
bool initialized = false;
PageFrameAllocator GlobalAllocator;
PageFrameAllocator::PageFrameAllocator(EFI_MEMORY_DESCRIPTOR* mMap, size_t mMapSize, size_t mMapDescSize)
{
    // ReadEFIMemoryMap(mMap, mMapSize, mMapDescSize);
    if (initialized) return;

    initialized = true;

    uint64_t mMapEntries = mMapSize / mMapDescSize;

    void* largestFreeMemSeg = NULL;
    size_t largestFreeMemSegSize = 0;

    for (int i = 0; i < mMapEntries; i++)
    {
        EFI_MEMORY_DESCRIPTOR* desc = (EFI_MEMORY_DESCRIPTOR*)((uint64_t)mMap + (i * mMapDescSize));
        if (desc->type == 7)
        {
            if (desc->numPages * 4096 > largestFreeMemSegSize)
            {
                largestFreeMemSeg = desc->physAddr;
                largestFreeMemSegSize = desc->numPages * 4096;
            }
        }
    }

    uint64_t memorySize = GetMemorySize(mMap, mMapEntries, mMapDescSize);
    freeMemory = memorySize;
    uint64_t bitMapSize = memorySize / 4096 / 8 + 1;

    // initBitMap(bitMapSize, largestFreeMemSeg);
    this->pageBitMap = BitMap((uint8_t*)largestFreeMemSeg, bitMapSize);

    LockPages(&pageBitMap, pageBitMap.GetSize() / 4096 + 1);

    for (int i = 0; i < mMapEntries; i++)
    {
        EFI_MEMORY_DESCRIPTOR* desc = (EFI_MEMORY_DESCRIPTOR*)((uint64_t)mMap + (i * mMapDescSize));
        if (desc->type != 7)
        {
            ReservePages(desc->physAddr, desc->numPages);
        }
    }
}

void PageFrameAllocator::ReadEFIMemoryMap(EFI_MEMORY_DESCRIPTOR* mMap, size_t mMapSize, size_t mMapDescSize)
{
    
}

void PageFrameAllocator::initBitMap(size_t bitMapSize, void* bufferAddress)
{

}

uint64_t pageBitMapIndex = 0;
void PageFrameAllocator::ReservePage(void* Address)
{
    uint64_t index = (uint64_t)Address / 4096;
    if (pageBitMap[index]) return;
    if (pageBitMap.Set(index, true))
    {
        freeMemory -= 4096;
        reservedMemory += 4096;
    }
}

void PageFrameAllocator::ReservePages(void* Address, uint64_t pageCount)
{
    for (uint64_t i = 0; i < pageCount; i++)
    {
        ReservePage((void*)((uint64_t)Address + (i * 4096)));
    }
}

void PageFrameAllocator::UnreservePage(void* Address)
{
    uint64_t index = (uint64_t)Address / 4096;
    if (!pageBitMap[index]) return;
    if (pageBitMap.Set(index, false))
    {
        freeMemory += 4096;
        reservedMemory -= 4096;
        if (pageBitMapIndex > index) pageBitMapIndex = index;
    }
}

void PageFrameAllocator::UnreservePages(void* Address, uint64_t pageCount)
{
    for (uint64_t i = 0; i < pageCount; i++)
    {
        UnreservePage((void*)((uint64_t)Address + (i * 4096)));
    }
}

void PageFrameAllocator::FreePage(void* Address)
{
    uint64_t index = (uint64_t)Address / 4096;
    if (!pageBitMap[index]) return;
    if (pageBitMap.Set(index, false))
    {
        freeMemory += 4096;
        usedMemory -= 4096;
        if (pageBitMapIndex > index) pageBitMapIndex = index;
    }
}

void PageFrameAllocator::FreePages(void* Address, uint64_t pageCount)
{
    for (uint64_t i = 0; i < pageCount; i++)
    {
        FreePage((void*)((uint64_t)Address + (i * 4096)));
    }
}

void PageFrameAllocator::LockPage(void* Address)
{
    uint64_t index = (uint64_t)Address / 4096;
    if (pageBitMap[index]) return;
    if (pageBitMap.Set(index, true))
    {
        freeMemory -= 4096;
        usedMemory += 4096;
    }
}

void PageFrameAllocator::LockPages(void* Address, uint64_t pageCount)
{
    for (uint64_t i = 0; i < pageCount; i++)
    {
        LockPage((void*)((uint64_t)Address + (i * 4096)));
    }
}


void* PageFrameAllocator::RequestPage()
{
    for (; pageBitMapIndex < this->pageBitMap.GetSize() * 8; pageBitMapIndex++)
    {
        if (pageBitMap[pageBitMapIndex]) continue;
        LockPage((void*)(pageBitMapIndex * 4096));
        return (void*)(pageBitMapIndex * 4096);
    }
    
    return NULL;
}

uint64_t PageFrameAllocator::GetFreeRAM()
{
    return freeMemory;
}

uint64_t PageFrameAllocator::GetUsedRAM()
{
return usedMemory;
}

uint64_t PageFrameAllocator::GetReserveRAM()
{
    return reservedMemory;
}