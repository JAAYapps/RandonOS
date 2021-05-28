#pragma once
#include "BasicRenderer.h"
#include "cstr.h"
#include "EfiMemory.h"
#include "Memory.h"
#include "BitMap.h"
#include "String.h"
#include "PagingSystem/PageFrameAllocator.h"
#include "PagingSystem/PageMapIndexer.h"
#include "PagingSystem/Paging.h"
#include "PagingSystem/PageTableManager.h"

struct BootInfo {
	Framebuffer* frameBuffer;
	PSF1_FONT* psf1_font;
	EFI_MEMORY_DESCRIPTOR* mMap;
	uint64_t mMapSize;
	uint64_t mDescriptorSize;
};

extern uint64_t _KernelStart;
extern uint64_t _KernelEnd;

struct KernelInfo {
    PageTableManager* PTM;
};

KernelInfo InitializeKernel(BootInfo* bootInfo);