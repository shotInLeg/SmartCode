#ifndef CONTAINER_DATA
#define CONTAINER_DATA


template< typename Type, unsigned N>
class ContainerData
{
protected:
    Type* _data;
    unsigned _rows;
    unsigned _columns;
    unsigned _depth;
    //unsigned sizes[N];

    ContainerData()
    {
        _rows = 0;
        _columns = 0;
        _depth = 0;
        _data = new Type[0];
    }

    ContainerData( Type * data, unsigned depth,  unsigned rows, unsigned columns)
    {
        _data = data;
        _depth = depth;
        _rows = rows;
        _columns = columns;
    }

    unsigned size() const
    {
        return _depth * _rows * _columns;
    }
};


#endif // CONTAINER_DATA

