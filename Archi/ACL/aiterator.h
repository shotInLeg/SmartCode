#ifndef AITERATOR
#define AITERATOR

#include "aexception.h"

template< typename Type >
class AIterator
{
public:
    AIterator():_begin(nullptr),_elm(nullptr),_end(nullptr)
    {}
    AIterator( Type * begin, Type * elm, Type * end ):_begin(begin),_elm(elm),_end(end)
    {}
    AIterator( Type * elm ):_begin(nullptr),_elm(elm),_end(nullptr)
    {}
    AIterator( const AIterator<Type>& itr ):_begin(itr._begin),_elm(itr._elm),_end(itr._end)
    {}

    AIterator<Type> operator=( const AIterator<Type>& itr )
    {
        _begin = itr._begin;
        _elm = itr._elm;
        _end = itr._end;

        return itr;
    }

    size_t offset() const throw ( AException )
    {
        if( ( _begin != nullptr && _end != nullptr && (_elm < _begin || _elm > _end) ) ||
              _begin == nullptr || _end == nullptr)
        {
            throw AException( INVALID_ARGUMENT );
        }

        return _elm - _begin;
    }

    Type& get() const throw ( AException )
    {

        if( _begin != nullptr && _end != nullptr && (_elm < _begin || _elm > _end) )
        {
            throw AException( INVALID_ARGUMENT );
        }

        return *_elm;
    }

    Type& operator*() const throw ( AException )
    {
        if( _begin != nullptr && _end != nullptr && (_elm < _begin || _elm > _end) )
        {
            throw AException( INVALID_ARGUMENT );
        }

        return *_elm;
    }

    AIterator<Type> operator++()
    {
        ++_elm;
        return *this;
    }
    AIterator<Type> operator--()
    {
        --_elm;
        return *this;
    }
    AIterator<Type> operator++(int)
    {
        ++_elm;
        return AIterator<Type>(_begin, _elm-1, _end);
    }
    AIterator<Type> operator--(int)
    {
        --_elm;
        return AIterator<Type>(_begin, _elm+1, _end);
    }

    bool operator==( const AIterator<Type>& b )
    {
        return _elm == b._elm;
    }
    bool operator!=( const AIterator<Type>& b )
    {
        return _elm != b._elm;
    }

    template< typename bType >
    friend bool outof( const AIterator<bType>& a ) throw ( AException );



protected:
    Type * _begin;
    Type * _elm;
    Type * _end;
};





#endif // AITERATOR

