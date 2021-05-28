#include "BitMap.h"

BitMap::BitMap(uint8_t* Buffer, size_t Size)
{
    this->Buffer = Buffer;
    this->Size = Size;
    ZeroOutMemory(Size);
}

bool BitMap::operator[](uint64_t index)
{
    if (index > Size * 8) return false;
    uint64_t byteIndex = index / 8;
    uint8_t bitIndex = index % 8;
    uint8_t bitIndexer = 0b10000000 >> bitIndex;
    if ((Buffer[byteIndex] & bitIndexer) > 0)
    {
        return true;
    }
    return false;
}

bool BitMap::Set(uint64_t index, bool value)
{
    if (index > Size * 8) return false;
    uint64_t byteIndex = index / 8;
    uint8_t bitIndex = index % 8;
    uint8_t bitIndexer = 0b10000000 >> bitIndex;
    Buffer[byteIndex] &= ~bitIndexer;
    if (value)
    {
        Buffer[byteIndex] |= bitIndexer;
    }
    return true;
}

void BitMap::ZeroOutMemory(size_t bitMapSize)
{
    for(int i = 0; i < bitMapSize; i++)
    {
        *(uint8_t*)(this->Buffer + i) = 0;
    }
}

size_t BitMap::GetSize() const
{
    return this->Size;
}