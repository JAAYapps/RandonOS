#pragma once
#include <stdint.h>

enum PT_Flag {
    Present = 0,
    ReadWrite = 1,
    UserSuper = 2,
    WriteThrough = 3,
    CacheDisabled = 4,
    Accessed = 5,
    LargerPages = 7,
    Custom0 = 9,
    Custom1 = 10,
    Custom2 = 11,
    NX = 63 // only if it is supported.
};

struct PageDirectoryEntry {
    uint64_t value;
    void SetFlag(PT_Flag flag, bool Enabled);
    bool GetFlag(PT_Flag flag);
    void SetAddress(uint64_t address);
    uint64_t GetAddress();
    // bool present : 1;
    // bool ReadWrite : 1;
    // bool UserSuper : 1;
    // bool WriteThrough : 1;
    // bool CacheDisabled : 1;
    // bool Accessed : 1;
    // bool Ignore0 : 1;
    // bool LargerPages : 1;
    // bool Ignore1 : 1;
    // uint8_t Availble : 3;
    // uint64_t Address : 52;
};

struct PageTable {
    PageDirectoryEntry Entries [512];
}__attribute__((aligned(0x1000)));