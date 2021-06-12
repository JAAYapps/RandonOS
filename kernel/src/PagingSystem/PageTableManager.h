#pragma once
#include "Paging.h"

class PageTableManager 
{
    public:
        PageTableManager() = default;
        PageTableManager(PageTable* PMLAddress);
        PageTable* PMLAddress;
        void MapMemory(void* virtualMemory, void* physicalMemory);
};

extern PageTableManager GPTM;