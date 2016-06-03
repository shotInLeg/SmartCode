#ifndef ABOOL_H
#define ABOOL_H


#include <iostream>

enum ABoolConst { True = 1, False = 0, Unknow = -1 };

class ABool
{
public:
    ABool();
    ABool( const ABool& v );
    ABool( bool v );
    ABool( ABoolConst v );

    bool operator=( bool v );
    ABoolConst operator=(ABoolConst v );

    friend std::ostream& operator<<( std::ostream& os, const ABool& v );
    friend std::istream& operator>>( std::istream& is, const ABool& v );

    ABoolConst operator>( ABoolConst v );
    ABoolConst operator<( ABoolConst v );
    ABoolConst operator==( ABoolConst v );
    ABoolConst operator>=( ABoolConst v );
    ABoolConst operator<=( ABoolConst v );
    ABoolConst operator!=( ABoolConst v );

    ABoolConst operator>( const ABool& v );
    ABoolConst operator<( const ABool& v );
    ABoolConst operator==( const ABool& v );
    ABoolConst operator>=( const ABool& v );
    ABoolConst operator<=( const ABool& v );
    ABoolConst operator!=( const ABool& v );

private:
    ABoolConst value;
};

#endif // ABOOL_H
