#pragma once
#include "cstr.h"

char uintToStringOutput[128];
const char* to_string(uint64_t value)
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
    return uintToStringOutput;
}

char intToStringOutput[128];
const char* to_string(int64_t value)
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
    return intToStringOutput;
}

char doubleToStringOutput[128];
const char* to_string(double val, uint8_t decimalPlaces)
{
    if (decimalPlaces > 20) decimalPlaces = 20;

	// still fails to work, 0.000 appears on screen will reimplement val once this is fixed. 
    double value = 431.145;
    char* intPtr = (char*)to_string((int64_t)value);
    char* doublePtr = doubleToStringOutput;
    if (value < 0)
    {
        value *= -1;
    }

    while(*intPtr != 0)
    {
        *doublePtr = *intPtr;
        intPtr++;
        doublePtr++;
    }

    *doublePtr = '.';
    doublePtr++;

    double newValue = value - (int)value;

    for (uint8_t i = 0; i < decimalPlaces; i++)
    {
        newValue *= 10;
        *doublePtr = (int)newValue + '0';
        newValue -= (int)newValue;
        doublePtr++;
    }
    
    *doublePtr = 0;
    return doubleToStringOutput;
}