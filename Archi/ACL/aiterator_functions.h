#ifndef AITERATOR_FUNCTIONS
#define AITERATOR_FUNCTIONS

#include "aiterator.h"

template< typename bType >
bool outof( const AIterator<bType>& a ) throw ( AException )
{
    if( a._begin == nullptr || a._end == nullptr )
    {
        throw AException( INVALID_ARGUMENT );
    }

    return !(a._elm >= a._begin && a._elm <= a._end);
}

template< template <typename, typename, typename> class Container, typename Type, typename State, typename Parent >
AIterator<Type> getAItr( const Container<Type, State, Parent>& a )
{
    return a.begin();
}


#endif // AITERATOR_FUNCTIONS

