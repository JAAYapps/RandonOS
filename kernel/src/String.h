#pragma once
#include <stddef.h>
#include <stdint.h>

class String
{
    private:
        const char* text;
    public:
        String(const char** text) : text((char*)text) {};
        char operator[](uint64_t index);
        void operator=(const char** text);
        const char** c_str();
        ~String();
};