#include "abool.h"

ABool::ABool()
{
    value = False;
}

ABool::ABool(const ABool &v)
{
    value = v.value;
}

ABool::ABool(bool v)
{
    if( v == true )
        value = True;
    else
        value = False;
}

ABool::ABool(ABoolConst v)
{
    value = v;
}

bool ABool::operator=(bool v)
{
    if( v == true )
        value = True;
    else
        value = False;

    return v;
}

ABoolConst ABool::operator=(ABoolConst v)
{
    value = v;

    return v;
}

ABoolConst ABool::operator>(ABoolConst v)
{
    return (value > v)?True:False;
}

ABoolConst ABool::operator<(ABoolConst v)
{
    return (value < v)?True:False;
}

ABoolConst ABool::operator==(ABoolConst v)
{
    return (value == v)?True:False;
}

ABoolConst ABool::operator>=(ABoolConst v)
{
    return (value >= v)?True:False;
}

ABoolConst ABool::operator<=(ABoolConst v)
{
    return (value <= v)?True:False;
}

ABoolConst ABool::operator!=(ABoolConst v)
{
    return (value != v)?True:False;
}

ABoolConst ABool::operator>(const ABool &v)
{
    return (value > v.value)?True:False;
}

ABoolConst ABool::operator<(const ABool &v)
{
    return (value < v.value)?True:False;
}

ABoolConst ABool::operator==(const ABool &v)
{
    return (value == v.value)?True:False;
}

ABoolConst ABool::operator>=(const ABool &v)
{
    return (value >= v.value)?True:False;
}

ABoolConst ABool::operator<=(const ABool &v)
{
    return (value <= v.value)?True:False;
}

ABoolConst ABool::operator!=(const ABool &v)
{
    return (value != v.value)?True:False;
}
