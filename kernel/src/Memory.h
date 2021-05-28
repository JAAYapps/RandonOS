#pragma once
#include <stdint.h>
#include "EfiMemory.h"

uint64_t GetMemorySize(EFI_MEMORY_DESCRIPTOR* mMap, uint64_t mMapEntries, uint64_t mMapDescSize);
void MemorySet(void* start, uint8_t value, uint64_t num);