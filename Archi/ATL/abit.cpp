#include "abit.h"

ABit::ABit()
{
    value = 0;
    pos = 0;
    ref_byte = NULL;
}

ABit::ABit(const ABit &v)
{
    value = v.value;
    pos = v.pos;
    ref_byte = v.ref_byte;
}

//ABit::ABit(const ANum16 &position, const AByte &byte)
//{
//}

ABit::ABit(const ANum16 &position, const ANum16 &v)
{

}

ABit::ABit(const ANum16 &position, char &byte)
{

}

ABit::ABit(char position, int v )
{
    value = v;
    pos = position;
    ref_byte = NULL;
}

ABit::ABit(char position, char &byte )
{
    value = 2;
    pos = position;
    ref_byte = &byte;
}

char ABit::operator=(char v)
{
    if(ref_byte != NULL)
    {
        set_bit(ref_byte, pos, v);
    }
    else
    {
        value = v;
    }

    return v;
}

ANum16 ABit::operator=(const ANum16 &v)
{
    return v;
}

void ABit::set_bit( char *byte, char i, char bit)
{

    if( bit == 1)
        (*byte) = (*byte) | (char)(pow(2,i));
    else if( bit == 0 )
        (*byte) = (*byte) & (char)(~(char)(pow(2,i)));

}

char ABit::get_bit(const char *byte, char i)
{
    if ( ((*byte) & (char)(pow(2,i))) == ((char)(pow(2,i))) )
        return char(1);

    return char(0);
}
