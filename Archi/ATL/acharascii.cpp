#include "acharascii.h"

ACharASCII::ACharASCII()
{
    value = 'A';
}

ACharASCII::ACharASCII(char v)
{
    value = v;
}

ACharASCII::ACharASCII(const char *v)
{
    value = v[0];
}

ACharASCII::ACharASCII(const ACharASCII &v)
{
    value = v.value;
}

