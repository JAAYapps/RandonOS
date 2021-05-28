#include "String.h"

char String::operator[](uint64_t index)
{
    return this->text[index];
}

void String::operator=(const char** text)
{
    this->text = *text;
}

const char** String::c_str()
{
    return &this->text;
}

String::~String()
{
}