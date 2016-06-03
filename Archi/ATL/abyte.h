#ifndef ABYTE_H
#define ABYTE_H

#include "abit.h"

class AByte
{
public:
    AByte();
    AByte( char v );
    AByte( const AByte& v );

    char operator=( char v );
    ABit operator[]( char i );
private:
    char value;

};

#endif // ABYTE_H
