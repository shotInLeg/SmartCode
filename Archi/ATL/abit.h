#ifndef ABIT_H
#define ABIT_H

#include <iostream>
#include <cmath>
#include "anum16.h"
//#include "abyte.h"

class ABit
{
public:
    ABit();
    ABit( const ABit& v );
    //ABit( const ANum16& position, const AByte& byte );
    ABit( const ANum16& position, const ANum16& v );
    ABit( const ANum16& position, char& byte );
    ABit( char position, int v );
    ABit( char position, char& byte );

    char operator=(char v);
    ANum16 operator=(const ANum16& v);

    friend std::ostream& operator<<( std::ostream& os, const ABit& v )
    {
        os << int(v.value);

        return os;
    }
    friend std::istream& operator>>( std::istream& is, ABit& v )
    {
        is >> v.value;

        return is;
    }

private:
    void set_bit(char *byte, char i, char bit);
    char get_bit(const char * byte, char i );

private:
    char value;
    char pos;
    char * ref_byte;
};


#endif // ABIT_H
