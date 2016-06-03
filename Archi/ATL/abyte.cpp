#include "abyte.h"

AByte::AByte()
{
    value = 0x00;
}

AByte::AByte(char v)
{
    value = v;
}

AByte::AByte(const AByte &v)
{
    value = v.value;
}

char AByte::operator=(char v)
{
    value = v;

    return v;
}

ABit AByte::operator[](char i)
{
    ABit bit(i, value);

    return bit;
}
