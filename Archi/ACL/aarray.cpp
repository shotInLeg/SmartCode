#include "aarray.h"


// class Array ********************************************************************************** Array

template< typename Type >
Array<Type>::Array()
{
    Data::_depth = 1;
    Data::_rows = 1;
    Data::_columns = 0;
    Data::_data = new Type[ Data::size() ];
}

template< typename Type >
Array<Type>::Array(unsigned size)
{
    Data::_depth = 1;
    Data::_rows = 1;
    Data::_columns = size;
    Data::_data = new Type[ Data::size() ];

    for(unsigned i = 0; i < Data::size(); i++)
    {
        Data::_data[i] = Type();
    }
}

template< typename Type >
Array<Type>::Array(init_list_array elmts)
{
    Data::_depth = 1;
    Data::_rows = 1;
    Data::_columns = elmts.size();
    Data::_data = new Type[ Data::size() ];

    typename init_list_array::iterator elm = elmts.begin();

    for( unsigned i = 0; i < Data::size() && elm != elmts.end(); i++, elm++ )
    {
        Data::_data[i] = *elm;
    }
}

template< typename Type >
std::initializer_list<Type> Array<Type>::operator=(init_list_array elmts) throw ( AException )
{
    delete [] Data::_data;

    Data::_depth = 1;
    Data::_rows = 1;
    Data::_columns = elmts.size();
    Data::_data = new Type[ Data::size() ];

    typename init_list_array::iterator elm = elmts.begin();

    for( unsigned i = 0; i < Data::size() && elm != elmts.end(); i++, elm++ )
    {
        Data::_data[i] = *elm;
    }

    return elmts;
}

template< typename Type >
Type& Array<Type>::operator[](unsigned index) const
{
    return Data::_data[index];
}

template< typename Type >
ASize Array<Type>::size() const
{
    return ASize(1, 1, Data::_columns );
}


// class Matrix ******************************************************************************* Matrix

template< typename Type >
Matrix<Type>::Matrix()
{
    Data::_depth = 1;
    Data::_rows = 0;
    Data::_columns = 0;
    Data::_data = new Type[ Data::_size() ];
}

template< typename Type >
Matrix<Type>::Matrix(unsigned size)
{
    Data::_depth = 1;
    Data::_rows = size;
    Data::_columns = size;
    Data::_data = new Type[ Data::size() ];

    for(unsigned i = 0; i < Data::size(); i++)
    {
        Data::_data[i] = Type();
    }
}

template< typename Type >
Matrix<Type>::Matrix(unsigned rows, unsigned cols)
{
    Data::_depth = 1;
    Data::_rows = rows;
    Data::_columns = cols;
    Data::_data = new Type[ Data::size() ];

    for(unsigned i = 0; i < Data::size(); i++)
    {
        Data::_data[i] = Type();
    }
}


template< typename Type >
Matrix<Type>::Matrix( init_list_matrix matrix )
{
    typename init_list_matrix::iterator elmts = matrix.begin();

    unsigned rows = matrix.size();
    unsigned columns = (*elmts).size();

    Data::_depth = 1;
    Data::_rows = rows;
    Data::_columns = columns;

    Data::_data = new Type[ Data::size() ];

    for( unsigned i = 0; i < Data::_rows && elmts != matrix.end(); i++, elmts++ )
    {
        typename init_list_array::iterator elm = elmts->begin();

        for( unsigned j = 0; j < Data::_columns && elm != elmts->end(); j++, elm++ )
        {
            Data::_data[ i * Data::_columns + j ] = *elm;
        }
    }
}


template< typename Type >
std::initializer_list< std::initializer_list<Type> > Matrix<Type>::operator=(init_list_matrix matrix) throw ( AException )
{
    delete [] Data::_data;

    typename init_list_matrix::iterator elmts = matrix.begin();

    unsigned rows = matrix.size();
    unsigned columns = (*elmts).size();

    Data::_depth = 1;
    Data::_rows = rows;
    Data::_columns = columns;

    Data::_data = new Type[ Data::size() ];

    for( unsigned i = 0; i < Data::_rows && elmts != matrix.end(); i++, elmts++ )
    {
        typename init_list_array::iterator elm = elmts->begin();

        for( unsigned j = 0; j < Data::_columns && elm != elmts->end(); j++, elm++ )
        {
            Data::_data[ i * Data::_columns + j ] = *elm;
        }
    }

    return matrix;
}

template< typename Type >
AArray<Type, Array<Type> > Matrix<Type>::operator[](unsigned row) const
{
    return AArray<Type, Array<Type> >( &Data::_data[ row * Data::_columns + 0 ], 1, 1, Data::_columns );
}

template< typename Type >
ASize Matrix<Type>::size() const
{
    return ASize ( Data::_depth, Data::_rows, Data::_columns );
}


// class Tenzor ****************************************************************************** Tenzor

template< typename Type >
Tenzor<Type>::Tenzor()
{
    Data::_depth = 0;
    Data::_rows = 0;
    Data::_columns = 0;
    Data::_data = new Type[ Data::size() ];
}

template< typename Type >
Tenzor<Type>::Tenzor( unsigned size)
{
    Data::_depth = size;
    Data::_rows = size;
    Data::_columns = size;
    Data::_data = new Type[ Data::size() ];

    for(unsigned i = 0; i < Data::size(); i++)
    {
        Data::_data[i] = Type();
    }
}

template< typename Type >
Tenzor<Type>::Tenzor(unsigned rows, unsigned cols, unsigned depth)
{
    Data::_rows = rows;
    Data::_columns = cols;
    Data::_depth = depth;
    Data::_data = new Type[ Data::size() ];

    for(unsigned i = 0; i < Data::size(); i++)
    {
        Data::_data[i] = Type();
    }
}

template< typename Type >
Tenzor<Type>::Tenzor( init_list_tenzor tenzor )
{
    typename init_list_tenzor::iterator tenz = tenzor.begin();
    typename init_list_matrix::iterator mtrx = tenz->begin();
    typename init_list_array::iterator arr = mtrx->begin();

    unsigned depth = tenzor.size();
    unsigned rows = tenz->size();
    unsigned columns = mtrx->size();


    Data::_rows = rows;
    Data::_columns = columns;
    Data::_depth = depth;
    Data::_data = new Type[ Data::size() ];

    for( unsigned i = 0; i < Data::_depth && tenz != tenzor.end(); i++, tenz++ )
    {
        mtrx = tenz->begin();
        for( unsigned j = 0; j < Data::_rows && mtrx != tenz->end(); j++, mtrx++ )
        {
            arr = mtrx->begin();
            for( unsigned k = 0; k < Data::_columns && arr != mtrx->end(); k++, arr++ )
            {
                Data::_data[ (Data::_rows * Data::_columns * i) + (Data::_columns * j) + k ] = *arr;
            }
        }
    }
}

template< typename Type >
AArray<Type, Matrix<Type> > Tenzor<Type>::operator[](unsigned depth) const
{
//    Type * p = &Data::_data[ Data::_rows * Data::_columns * depth ];
//    std::cout << "!!!debug print" << std::endl;
//    for( int i = 0; i < Data::_rows * Data::_columns; i++)
//        std::cout << p[i] << " ";

//    std::cout << std::endl;


    return AArray<Type, Matrix<Type> >( &Data::_data[ Data::_rows * Data::_columns * depth ], 1, Data::_rows, Data::_columns );
}

template< typename Type >
ASize Tenzor<Type>::size() const
{
    return ASize ( Data::_depth, Data::_rows, Data::_columns );
}
