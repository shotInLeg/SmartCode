#ifndef ACHARASCII_H
#define ACHARASCII_H

#include <iostream>

class ACharASCII
{
public:
    ACharASCII();
    ACharASCII( char v );
    ACharASCII( const char * v );
    ACharASCII( const ACharASCII& v );

    friend std::ostream& operator<<( std::ostream& os, const ACharASCII& v )
    {
        os << v.value;

        return os;
    }

    friend std::istream& operator>>( std::istream& is, ACharASCII& v )
    {
        is >> v.value;

        return is;
    }

private:
    char value;
};



#endif // ACHARASCII_H
