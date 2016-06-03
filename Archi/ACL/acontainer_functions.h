#ifndef ACONTAINER_FUNCTION
#define ACONTAINER_FUNCTION

#include <cstdlib>
#include <ctime>
#include <acl.h>



template< template <typename, typename, typename> class Container, typename Type, typename State, typename Parent >
Type& head( const Container<Type, State, Parent>& a )
{
    AIterator<Type> cont = getAItr(a);

    return cont.get();
}

template< template <typename, typename, typename> class Container, typename Type, typename State, typename Parent >
Container<Type, State, Parent> tail( const Container<Type, State, Parent>& a )  throw ( AException )
{
    Container<Type, State, Parent> temp( a.size()-1 );
    try
    {
        AIterator<Type> cont = getAItr(a)+1;
        AIterator<Type> itr = getAItr(temp);

        for( ; !outof(cont); ++cont, ++itr )
            itr.get() = cont.get();

    }
    catch( const AException& ex )
    {
        throw ex;
    }

    return temp;
}

template< template <typename, typename, typename> class Container, typename Type, typename State, typename Parent >
Container<Type, State, Parent> applique( const Container<Type, State, Parent>& a, void(*applicator)( Type& elm )  )  throw ( AException )
{
    Container<Type, State, Parent> temp;
    try
    {
        temp = a;

        AIterator<Type> itr = getAItr(temp);

        for( ; !outof(itr); ++itr )
            applicator( itr.get() );
    }
    catch( const AException& ex )
    {
        throw ex;
    }

    return temp;
}

template< template <typename, typename, typename> class Container, typename Type, typename State, typename Parent >
Type conv( const Container<Type, State, Parent>& a, Type(*sv)( Type elm1, Type elm2 )  )  throw ( AException )
{
    if( a.size() == 1 ) return head( a );

    return sv( head( a ), conv( tail( a ), sv )  );
}


template< template <typename, typename, typename> class Container, typename Type, typename State, typename Parent >
Container<Type, State, Parent> add( Container<Type, State, Parent>& a, const Type& b )
{
    Container<Type, State, Parent> temp(a.size() + 1);

    AIterator<Type> itr = getAItr(temp);
    AIterator<Type> cont = getAItr(a);

    for( ; !outof(cont); ++cont, ++itr )
        itr.get() = cont.get();

    itr.get() = b;

    return temp;
}

template< template <typename, typename, typename> class Container, typename Type, typename State, typename Parent >
ASize size( Container<Type, State, Parent>& a )
{
    return a.size();
}

// операции

template< typename Type >
void input( Type& a )
{
    std::cin >> a;
}

template< typename Type >
void output( Type& a )
{
    std::cout << a << " ";
}

template< typename Type >
Type sum( Type a, Type b )
{
    return a + b;
}

template< typename Type >
Type sub( Type a, Type b )
{
    return a - b;
}

template< typename Type >
Type div( Type a, Type b )
{
    return a / b;
}

template< typename Type >
Type mul( Type a, Type b )
{
    return a * b;
}



#define input &input
#define output &output
#define sum &sum
#define sub &sub
#define mul &mul
#define div &div

#endif // ACONTAINER_FUNCTION

