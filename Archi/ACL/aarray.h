#ifndef AARRAY
#define AARRAY

#include "container_data.h"
#include "aexception.h"
#include "aiterator.h"
#include "asize.h"


class Cap
{};


template< typename Type, class SizeState, class Parent = Cap >
class AArray : public SizeState, public Parent
{
    typedef std::initializer_list<Type> init_list_array;
    typedef std::initializer_list< init_list_array > init_list_matrix;
    typedef std::initializer_list< init_list_matrix > init_list_tenzor;


public:
    AArray():SizeState()
    {}

    explicit AArray( unsigned size ):SizeState( size )
    {}

    explicit AArray( unsigned rows, unsigned cols ):SizeState( rows, cols )
    {}

    AArray( const AArray<Type, SizeState, Parent>& b ):SizeState( b._data, b._depth, b._rows, b._columns )
    {}

    AArray( init_list_array elmts ):SizeState( elmts )
    {}


    AArray( init_list_matrix matrix ):SizeState( matrix )
    { /*std::cout << "c 1" << std::endl;*/ }

    AArray( init_list_tenzor tenzor ):SizeState( tenzor )
    {}

    AArray( Type * data, unsigned depth, unsigned rows, unsigned columns ):SizeState( data, depth, rows, columns )
    {}

    /*
    explicit AArray( size_t rows, size_t columns, size_t depth)
    {
        if( SizeState::size() != 3 )
        {
            throw AException( INVALID_ARGUMENT );
        }

        Data::_size = rows * columns * depth;
        _rows = rows;
        _columns = columns;
        _depth = depth;
       Data::_data = new Type[Data::_size];

        for(size_t i = 0; i < Data::_size; i++)
        {
            Data::_data[i] = Type();
        }
    }*/

    /*

    AArray( std::initializer_list< std::initializer_list< std::initializer_list<Type> > > tenzor ) throw ( AException )
    {
        if( SizeState::size() != 3 )
        {
            throw AException( INVALID_ARGUMENT );
        }

        typename std::initializer_list< std::initializer_list< std::initializer_list<Type> > >::iterator matrix = tenzor.begin();
        typename std::initializer_list< std::initializer_list<Type> >::iterator elmts = matrix->begin();
        typename std::initializer_list<Type>::iterator elm = elmts->begin();

        size_t rows = tenzor.size();
        size_t columns = matrix->size();
        size_t depth = elmts->size();


        Data::_size = rows * columns * depth;
        _rows = rows;
        _columns = columns;
        _depth = depth;
        Data::_data = new Type[Data::_size];

        for( int i = 0; i < _rows, matrix != tenzor.end(); i++, matrix++ )
        {
            elmts = matrix->begin();
            for( size_t j = 0; j < _columns, elmts != matrix->end(); j++, elmts++ )
            {
                elm = elmts->begin();
                for( size_t k = 0; k < _depth, elm != elmts->end(); k++, elm++ )
                {
                    Data::_data[ (i * _columns + j) * _depth + k ] = *elm;
                }
            }
        }
    }*/

    // операции присваивания

/*




    std::initializer_list< std::initializer_list< std::initializer_list<Type> > > operator=( std::initializer_list< std::initializer_list< std::initializer_list<Type> > > tenzor ) throw ( AException )
    {
        if( SizeState::size() != 3 )
        {
            throw AException( INVALID_ARGUMENT );
        }

        typename std::initializer_list< std::initializer_list< std::initializer_list<Type> > >::iterator matrix = tenzor.begin();
        typename std::initializer_list< std::initializer_list<Type> >::iterator elmts = matrix->begin();
        typename std::initializer_list<Type>::iterator elm = elmts->begin();

        size_t rows = tenzor.size();
        size_t columns = matrix->size();
        size_t depth = elmts->size();


        Data::_size = rows * columns * depth;
        _rows = rows;
        _columns = columns;
        _depth = depth;
        Data::_data = new Type[Data::_size];

        for( int i = 0; i < _rows, matrix != tenzor.end(); i++, matrix++ )
        {
            elmts = matrix->begin();
            for( size_t j = 0; j < _columns, elmts != matrix->end(); j++, elmts++ )
            {
                elm = elmts->begin();
                for( size_t k = 0; k < _depth, elm != elmts->end(); k++, elm++ )
                {
                    Data::_data[ (i * _columns + j) * _depth + k ] = *elm;
                }
            }
        }

        return tenzor;
    }*/


    ASize size() const
    { return SizeState::size(); }

    AIterator<Type> begin() const
    { return AIterator<Type>( SizeState::_data, SizeState::_data, SizeState::_data + SizeState::size()-1 ); }

    AIterator<Type> end() const
    {
        return AIterator<Type>( SizeState::_data, SizeState::_data + SizeState::size(), SizeState::_data + SizeState::size()-1 );
    }

};

template< typename Type >
class Array : public ContainerData<Type, 1>
{
protected:
    typedef ContainerData<Type, 1> Data;
    typedef std::initializer_list<Type> init_list_array;

    Array();
    Array( unsigned size );
    Array( Type * data, unsigned depth, unsigned rows, unsigned columns ):Data( data, depth, rows, columns )
    {}
    Array( init_list_array elmts );

public:
    init_list_array                 operator=   ( init_list_array elmts )       throw ( AException );
    Type&                           operator[]  ( unsigned index )              const;
    ASize                           size()                                      const;
};

template< typename Type >
class Matrix : public ContainerData<Type, 2>
{
protected:
    typedef ContainerData<Type, 2> Data;
    typedef std::initializer_list<Type> init_list_array;
    typedef std::initializer_list< init_list_array > init_list_matrix;

    Matrix();
    Matrix( unsigned size );
    Matrix( unsigned rows, unsigned cols );
    Matrix( Type* data, unsigned depth, unsigned rows, unsigned columns ):Data( data, depth, rows, columns )
    {}
    explicit Matrix( init_list_matrix matrix );


public:
    init_list_matrix                operator=   ( init_list_matrix matrix )     throw ( AException );
    AArray<Type, Array<Type> >      operator[]  ( unsigned row )                const;
    ASize                           size()                                      const;

protected:

};

template< typename Type >
class Tenzor : public ContainerData<Type, 3>
{
protected:
    typedef ContainerData<Type, 3> Data;
    typedef std::initializer_list<Type> init_list_array;
    typedef std::initializer_list< init_list_array > init_list_matrix;
    typedef std::initializer_list< init_list_matrix > init_list_tenzor;

    Tenzor();
    Tenzor( unsigned size );
    Tenzor( unsigned rows, unsigned cols, unsigned depth );
    Tenzor( Type* data, unsigned depth, unsigned rows, unsigned columns ):Data( data, depth, rows, columns )
    {}
    explicit Tenzor( init_list_tenzor tenzor );

public:
    AArray<Type, Matrix<Type> >      operator[]  ( unsigned depth )                const;
    ASize                           size()                                      const;

};





#endif // AARRAY

