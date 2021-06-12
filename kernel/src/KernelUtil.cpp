#include "KernelUtil.h"
#include "GDT/GDT.h"
#include "Interrupts/IDT.h"
#include "Interrupts/Interrupts.h"
#include "IO.h"
#include "pci.h"

KernelInfo kernelInfo;
void PrepareMemory(BootInfo* bootInfo)
{
    uint64_t mMapEntries = bootInfo->mMapSize / bootInfo->mDescriptorSize;

    GlobalAllocator = PageFrameAllocator(bootInfo->mMap, bootInfo->mMapSize, bootInfo->mDescriptorSize);

    uint64_t KernelSize = (uint64_t)&_KernelEnd - (uint64_t)&_KernelStart;
    uint64_t kernelPages = (uint64_t)KernelSize / 4096 + 1;

    GlobalAllocator.LockPages(&_KernelStart, kernelPages);

    PageTable* PML4 = (PageTable*)GlobalAllocator.RequestPage();
    MemorySet(PML4, 0, 0x1000);

    GPTM = PageTableManager(PML4);

    for (uint64_t t = 0; t < GetMemorySize(bootInfo->mMap, mMapEntries, bootInfo->mDescriptorSize); t += 0x1000)
    {
        GPTM.MapMemory((void*)t, (void*)t);
    }
    
    uint64_t fbBase = (uint64_t)bootInfo->frameBuffer->BaseAddress;
    uint64_t fbSize = (uint64_t)bootInfo->frameBuffer->BufferSize + 0x1000;
    GlobalAllocator.LockPages((void*)fbBase, fbSize / 0x10000 + 1);
    for (uint64_t t = fbBase; t < fbBase + fbSize; t += 4096)
    {
        GPTM.MapMemory((void*)t, (void*)t);
    }
    
    asm ("mov %0, %%cr3" : : "r" (PML4));

    kernelInfo.PTM = &GPTM;
}

IDTR idtr;
void SetIDTGate(void* handler, uint8_t entryOffset, uint8_t type_attr, uint8_t selector)
{
    IDTDescEntry* interrupt = (IDTDescEntry*)(idtr.offset + entryOffset * sizeof(IDTDescEntry));
    interrupt->SetOffset((uint64_t)handler);
    interrupt->type_attr = type_attr;
    interrupt->selector = selector;
}

void PrepareInterrupts()
{
    idtr.limit = 0x0fff;
    idtr.offset = (uint64_t)GlobalAllocator.RequestPage();

    SetIDTGate((void*)PageFault_Handler, 0xE, IDT_TA_InterruptGate, 0x08);
    SetIDTGate((void*)DoubleFault_Handler, 0x8, IDT_TA_InterruptGate, 0x08);
    SetIDTGate((void*)GPFault_Handler, 0xD, IDT_TA_InterruptGate, 0x08);
    SetIDTGate((void*)Keyboard_Handler, 0x21, IDT_TA_InterruptGate, 0x08);
    SetIDTGate((void*)Mouse_Handler, 0x2C, IDT_TA_InterruptGate, 0x08);

    asm ("lidt %0" : : "m" (idtr));

    //RemapPIC();

    //InitPS2Mouse();

    //outb(PIC1_DATA, 0b11111101);
    //outb(PIC2_DATA, 0b11111111);

    //asm ("sti");
}

void PrepareACPI(BootInfo* bootInfo)
{
    ACPI::SDTHeader* xsdt = (ACPI::SDTHeader*)(bootInfo->rsdp->XSDTAddress);

    ACPI::MCFGHeader* mcfg = (ACPI::MCFGHeader*)ACPI::FindTable(xsdt, (char*)"MCFG");

    GBR->Print(to_hstring((uint64_t)mcfg));
    GBR->GoToNextLine();
    for (int t = 0; t < 4; t++)
    {
        GBR->PutChar(mcfg->Header.Signature[t]);
    }

    PCI::EnumeratePCI(mcfg);

    // int entries = (xsdt->Length - sizeof(ACPI::SDTHeader)) / 8;

    // for (int t = 0; t < entries; t++)
    // {
    //     ACPI::SDTHeader* newSDTHeader = (ACPI::SDTHeader*)*(uint64_t*)((uint64_t)xsdt + sizeof(ACPI::SDTHeader) + (t * 8));
    //     for (int i = 0; i < 4; i++)
    //     {
    //         GBR->PutChar(newSDTHeader->Signature[i]);
    //     }
    //     GBR->PutChar(' ');
    // }
    // GBR->GoToNextLine();
}

BasicRenderer r = BasicRenderer(NULL, NULL);
KernelInfo InitializeKernel(BootInfo* bootInfo)
{
    r = BasicRenderer(bootInfo->frameBuffer, bootInfo->psf1_font);
    GBR = &r;

    GDTDescriptor gdtDescriptor;
    gdtDescriptor.Size = sizeof(GDT) - 1;
    gdtDescriptor.Offset = (uint64_t)&DefaultGDT;
    LoadGDT(&gdtDescriptor);

    PrepareMemory(bootInfo);
    MemorySet(bootInfo->frameBuffer->BaseAddress, 0, bootInfo->frameBuffer->BufferSize);

    PrepareInterrupts();

    PrepareACPI(bootInfo);

    return kernelInfo;
}