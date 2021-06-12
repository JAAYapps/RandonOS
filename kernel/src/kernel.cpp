#include "KernelUtil.h"

extern "C" void _start(BootInfo* bootInfo)
{
    KernelInfo kernelInfo = InitializeKernel(bootInfo);

    PageTableManager* PTM = kernelInfo.PTM;

    GBR->Print(0xffffffff, (const char**)"Kernel Initialization is Complete. :)");
    GBR->GoToNextLine();
    GBR->Print(0x001545ff, to_hstring((uint64_t)bootInfo->rsdp));
    GBR->GoToNextLine();

    // while (true)
    // {
    //     ProcessMousePacket();
    // }

    while (true);

    // int* test = (int*)0x80000000000;
    // *test = 200;

    // PTM->MapMemory((void*)0x600000000, (void*)0x80000);

    // uint64_t* test = (uint64_t*)0x600000000;
    // *test = 26;
    // render.Print(0xff0025ff, (const char**)to_string(*test));

    // PageMapIndexer pageIndexer = PageMapIndexer(0x1000 * 52 + 0x50000 * 7);
    // const char str[4] = " - ";
    // render.Print(0xff0025ff, (const char**)to_string(pageIndexer.P_i));
    // render.Print(0xffffffff, (const char**)&str);
    // render.Print(0xff0025ff, (const char**)to_string(pageIndexer.PT_i));
    // render.Print(0xffffffff, (const char**)&str);
    // render.Print(0xff0025ff, (const char**)to_string(pageIndexer.PD_i));
    // render.Print(0xffffffff, (const char**)&str);
    // render.Print(0xff0025ff, (const char**)to_string(pageIndexer.PDP_i));


    // const char FR[9] = "Free Ram";
    // const char UR[9] = "Used Ram";
    // const char RR[13] = "Reserved Ram";
    // const char KB[4] = " KB";
    // render.GoToNextLine();
    // render.GoToNextLine();
    // // for(int i = 0; i < 128; i++)
    // // {
    // //     render.Print(0xffffffff, );
    // //     render.GoToNextLine();
    // // }
    // render.GoToNextLine();
    // render.GoToNextLine();
    // render.Print(0xffffffff, (const char**)&FR);
    // render.Print(0xff0025ff, (const char**)to_string(newPFA.GetFreeRAM() / 1024));
    // render.Print(0xff0025ff, (const char**)&KB);
    // render.GoToNextLine();

    // render.Print(0xffffffff, (const char**)&UR);
    // render.Print(0xff0025ff, (const char**)to_string(newPFA.GetUsedRAM() / 1024));
    // render.Print(0xff0025ff, (const char**)&KB);
    // render.GoToNextLine();

    // render.Print(0xffffffff, (const char**)&RR);
    // render.Print(0xff0025ff, (const char**)to_string(newPFA.GetReserveRAM() / 1024));
    // render.Print(0xff0025ff, (const char**)&KB);
    // render.GoToNextLine();

    // for (int i = 0; i < 20; i++)
    // {
    //     void* address = newPFA.RequestPage();
    //     render.Print(0xff2525ff, (const char**)to_hstring((uint64_t)address));
    //     render.GoToNextLine();
    // }

    // BitMap testBitMap = BitMap(&testBuffer[0], 20);
    // testBitMap.Set(0, false);
    // testBitMap.Set(1, true);
    // testBitMap.Set(2, false);
    // testBitMap.Set(3, false);
    // testBitMap.Set(4, true);
    // String text = (const char**)&"Heap Test";
    // render.Print(0xffffffff, text.c_str());
    // render.GoToNextLine();
    // const char True[5] = "true";
    // const char False[6] = "false";    
    // for (int i = 0; i < 20; i++)
    // {
    //     render.Print(0xff0025ff, testBitMap[i] ? (const char**)&True : (const char**)&False);
    //     render.GoToNextLine();
    // }
    
    // uint64_t mMapEntries = bootInfo->mMapSize / bootInfo->mDescriptorSize;
    // render.Print(0xff0025ff, to_string((uint64_t)GetMemorySize(bootInfo->mMap, mMapEntries, bootInfo->mDescriptorSize)));
    // for (size_t i = 0; i < mMapEntries; i++)
    // {
    //     EFI_MEMORY_DESCRIPTOR* desc = (EFI_MEMORY_DESCRIPTOR*)((uint64_t)bootInfo->mMap + (i * bootInfo->mDescriptorSize));
    //     render.Print(EFI_MEMORY_TYPE_STRINGS[desc->type]);
    //     render.Print(0xffffff00, ": \0");
    //     uint64_t pages = (desc->numPages * 4096 / 1024);
    //     if (pages > 0)
    //     {
    //         // render.Print(0xff0025ff, to_string((uint64_t)77));
    //         // render.Print(0xff0025ff, to_string((uint64_t)77));
    //         render.Print(0xff0025ff, to_string((uint64_t)pages));
    //         render.Print(0xff0025ff, " Kb");         
    //     }
    //     else
    //     {
    //         render.Print(0xff0025ff, "Well something went wrong.");   
    //     }
    //     render.GoToNextLine();
    // }
}