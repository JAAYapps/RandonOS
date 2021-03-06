#include "cstr.h"

char uintToStringOutput[128];
const char** to_string(uint64_t value)
{
    uint8_t size;
    uint64_t sizeTest = value;
    while (sizeTest / 10 > 0)
    {
        sizeTest /= 10;
        size++;
    }
    uint8_t index = 0;
    while (value / 10 > 0)
    {
        uint8_t remainder = value % 10;
        value /= 10;
        uintToStringOutput[size - index] = remainder + '0';
        index++;
    }
    uint8_t remainder = value % 10;
    uintToStringOutput[size - index] = remainder + '0';
    uintToStringOutput[size + 1] = 0;
    return (const char**)&uintToStringOutput;
}

char hexToStringOutput[128];
const char** to_hstring(uint64_t value){
    uint64_t* valPtr = &value;
    uint8_t* ptr;
    uint8_t tmp;
    uint8_t size = 8 * 2 - 1;
    for (uint8_t i = 0; i < size; i++){
        ptr = ((uint8_t*)valPtr + i);
        tmp = ((*ptr & 0xF0) >> 4);
        hexToStringOutput[size - (i * 2 + 1)] = tmp + (tmp > 9 ? 55 : '0');
        tmp = ((*ptr & 0x0F));
        hexToStringOutput[size - (i * 2)] = tmp + (tmp > 9 ? 55 : '0');
    }
    hexToStringOutput[size + 1] = 0;
    return (const char**)&hexToStringOutput;
}

char hexToStringOutput32[128];
const char** to_hstring(uint32_t value){
    uint32_t* valPtr = &value;
    uint8_t* ptr;
    uint8_t tmp;
    uint8_t size = 4 * 2 - 1;
    for (uint8_t i = 0; i < size; i++){
        ptr = ((uint8_t*)valPtr + i);
        tmp = ((*ptr & 0xF0) >> 4);
        hexToStringOutput32[size - (i * 2 + 1)] = tmp + (tmp > 9 ? 55 : '0');
        tmp = ((*ptr & 0x0F));
        hexToStringOutput32[size - (i * 2)] = tmp + (tmp > 9 ? 55 : '0');
    }
    hexToStringOutput32[size + 1] = 0;
    return (const char**)&hexToStringOutput32;
}

char hexToStringOutput16[128];
const char** to_hstring(uint16_t value){
    uint16_t* valPtr = &value;
    uint8_t* ptr;
    uint8_t tmp;
    uint8_t size = 2 * 2 - 1;
    for (uint8_t i = 0; i < size; i++){
        ptr = ((uint8_t*)valPtr + i);
        tmp = ((*ptr & 0xF0) >> 4);
        hexToStringOutput16[size - (i * 2 + 1)] = tmp + (tmp > 9 ? 55 : '0');
        tmp = ((*ptr & 0x0F));
        hexToStringOutput16[size - (i * 2)] = tmp + (tmp > 9 ? 55 : '0');
    }
    hexToStringOutput16[size + 1] = 0;
    return (const char**)&hexToStringOutput16;
}

char hexToStringOutput8[128];
const char** to_hstring(uint8_t value){
    uint8_t* valPtr = &value;
    uint8_t* ptr;
    uint8_t tmp;
    uint8_t size = 1 * 2 - 1;
    for (uint8_t i = 0; i < size; i++){
        ptr = ((uint8_t*)valPtr + i);
        tmp = ((*ptr & 0xF0) >> 4);
        hexToStringOutput8[size - (i * 2 + 1)] = tmp + (tmp > 9 ? 55 : '0');
        tmp = ((*ptr & 0x0F));
        hexToStringOutput8[size - (i * 2)] = tmp + (tmp > 9 ? 55 : '0');
    }
    hexToStringOutput8[size + 1] = 0;
    return (const char**)&hexToStringOutput8;
}


char intToStringOutput[128];
const char** to_string(int64_t value)
{
    uint8_t isNegative = 0;
    if (value < 0)
    {
        isNegative = 1;
        value *= -1;
        intToStringOutput[0] = '-';
    }

    uint8_t size;
    uint64_t sizeTest = value;
    while (sizeTest / 10 > 0)
    {
        sizeTest /= 10;
        size++;
    }
    uint8_t index = 0;
    while (value / 10 > 0)
    {
        uint8_t remainder = value % 10;
        value /= 10;
        intToStringOutput[isNegative + size - index] = remainder + '0';
        index++;
    }
    uint8_t remainder = value % 10;
    intToStringOutput[isNegative + size - index] = remainder + '0';
    intToStringOutput[isNegative + size + 1] = 0;
    return (const char**)&intToStringOutput;
}

// char doubleToStringOutput[128];
// const char** to_string(double value, uint8_t decimalPlaces)
// {
//     if (decimalPlaces > 20) decimalPlaces = 20;

//     const char* intPtr = &(to_string((int64_t)value));
//     char* doublePtr = doubleToStringOutput;
//     if (value < 0)
//     {
//         value *= -1;
//     }
//     value = 431.145;
//     while(*intPtr != 0)
//     {
//         *doublePtr = *intPtr;
//         intPtr++;
//         doublePtr++;
//     }

//     *doublePtr = '.';
//     doublePtr++;

//     double newValue = value - (int)value;

//     for (uint8_t i = 0; i < decimalPlaces; i++)
//     {
//         newValue *= 10;
//         *doublePtr = (int)newValue + '0';
//         newValue -= (int)newValue;
//         doublePtr++;
//     }
    
//     return (const char**)&doubleToStringOutput;
// }