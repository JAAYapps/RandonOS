#include "KernelUtil.h"
#include "GDT/GDT.h"

KernelInfo kernelInfo;
PageTableManager PTM;
void PrepareMemory(BootInfo* bootInfo)
{
    uint64_t mMapEntries = bootInfo->mMapSize / bootInfo->mDescriptorSize;

    GlobalAllocator = PageFrameAllocator(bootInfo->mMap, bootInfo->mMapSize, bootInfo->mDescriptorSize);

    uint64_t KernelSize = (uint64_t)&_KernelEnd - (uint64_t)&_KernelStart;
    uint64_t kernelPages = (uint64_t)KernelSize / 4096 + 1;

    GlobalAllocator.LockPages(&_KernelStart, kernelPages);

    PageTable* PML4 = (PageTable*)GlobalAllocator.RequestPage();
    MemorySet(PML4, 0, 0x1000);

    PTM = PageTableManager(PML4);

    for (uint64_t t = 0; t < GetMemorySize(bootInfo->mMap, mMapEntries, bootInfo->mDescriptorSize); t += 0x1000)
    {
        PTM.MapMemory((void*)t, (void*)t);
    }
    
    uint64_t fbBase = (uint64_t)bootInfo->frameBuffer->BaseAddress;
    uint64_t fbSize = (uint64_t)bootInfo->frameBuffer->BufferSize + 0x1000;
    GlobalAllocator.LockPages((void*)fbBase, fbSize / 0x1000 + 1);
    for (uint64_t t = fbBase; t < fbBase + fbSize; t += 4096)
    {
        PTM.MapMemory((void*)t, (void*)t);
    }
    
    asm ("mov %0, %%cr3" : : "r" (PML4));

    kernelInfo.PTM = &PTM;
}

KernelInfo InitializeKernel(BootInfo* bootInfo)
{
    GDTDescriptor gdtDescriptor;
    gdtDescriptor.Size = sizeof(GDT) - 1;
    gdtDescriptor.Offset = (uint64_t)&DefaultGDT;
    LoadGDT(&gdtDescriptor);
    while(true);

    PrepareMemory(bootInfo);
    MemorySet(bootInfo->frameBuffer->BaseAddress, 0, bootInfo->frameBuffer->BufferSize);

    
    return kernelInfo;
}