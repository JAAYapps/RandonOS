#pragma once
#include "../EfiMemory.h"
#include <stdint.h>
#include "../BitMap.h"
#include "../Memory.h"

class PageFrameAllocator 
{
    private:
        void initBitMap(size_t bitMapSize, void* bufferAddress);
        void ReservePage(void* Address);
        void UnreservePage(void* Address);
        void ReservePages(void* Address, uint64_t pageCount);
        void UnreservePages(void* Address, uint64_t pageCount);        
        BitMap pageBitMap;
    public:
        PageFrameAllocator() = default;
        PageFrameAllocator(EFI_MEMORY_DESCRIPTOR* mMap, size_t mMapSize, size_t mMapDescSize);
        void FreePage(void* Address);
        void LockPage(void* Address);
        void FreePages(void* Address, uint64_t pageCount);
        void LockPages(void* Address, uint64_t pageCount);
        void* RequestPage();
        uint64_t GetFreeRAM();
        uint64_t GetUsedRAM();
        uint64_t GetReserveRAM();


        void ReadEFIMemoryMap(EFI_MEMORY_DESCRIPTOR* mMap, size_t mMapSize, size_t mMapDescSize);
};

extern PageFrameAllocator GlobalAllocator;