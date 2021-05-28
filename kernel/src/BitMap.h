#pragma once
#include <stddef.h>
#include <stdint.h>

class BitMap
{
    private:
        size_t Size; 
        uint8_t* Buffer;
    public:
        BitMap() = default;
        BitMap(uint8_t* Buffer, size_t Size);
        void ZeroOutMemory(size_t bitMapSize);
        bool operator[](uint64_t index);
        bool Set(uint64_t index, bool value);
        size_t GetSize() const;
};