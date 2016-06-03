#ifndef ASIZE
#define ASIZE

struct ARows
{
    unsigned rows;
    ARows( unsigned countRows ){ rows = countRows; }
};
struct AColumns
{
    unsigned columns;
    AColumns( unsigned countColumns ){ columns = countColumns; }
};
struct ADepth
{
    unsigned depth;
    ADepth( unsigned countDepth ){ depth = countDepth; }
};

class ASize
{
    unsigned _rows;
    unsigned _columns;
    unsigned _depth;

public:
    ASize( unsigned depth, unsigned rows, unsigned columns )
    {
        _rows = rows;
        _columns = columns;
        _depth = depth;
    }

    unsigned rows() const
    {
        return _rows;
    }
    unsigned columns() const
    {
        return _columns;
    }
    unsigned depth() const
    {
        return _depth;
    }

    bool operator>( const ASize& b )
    {
        return _rows > b._rows &&
               _columns > b._columns &&
               _depth > b._depth;
    }
    bool operator<( const ASize& b )
    {
        return _rows < b._rows &&
               _columns < b._columns &&
               _depth < b._depth;
    }
    bool operator==( const ASize& b )
    {
        return _rows == b._rows &&
               _columns == b._columns &&
               _depth == b._depth;
    }
    bool operator>=( const ASize& b )
    {
        return _rows >= b._rows &&
               _columns >= b._columns &&
               _depth >= b._depth;
    }
    bool operator<=( const ASize& b )
    {
        return _rows <= b._rows &&
               _columns <= b._columns &&
               _depth <= b._depth;
    }
    bool operator!=( const ASize& b )
    {
        return _rows != b._rows &&
               _columns != b._columns &&
               _depth != b._depth;
    }


    bool operator>( const ARows& b )
    {
        return _rows > b.rows;
    }
    bool operator>( const AColumns& b )
    {
        return _columns > b.columns;
    }
    bool operator>( const ADepth& b )
    {
        return _depth > b.depth;
    }

    bool operator<( const ARows& b )
    {
        return _rows < b.rows;
    }
    bool operator<( const AColumns& b )
    {
        return _columns < b.columns;
    }
    bool operator<( const ADepth& b )
    {
        return _depth < b.depth;
    }

    bool operator==( const ARows& b )
    {
        return _rows == b.rows;
    }
    bool operator==( const AColumns& b )
    {
        return _columns == b.columns;
    }
    bool operator==( const ADepth& b )
    {
        return _depth == b.depth;
    }

    bool operator>=( const ARows& b )
    {
        return _rows >= b.rows;
    }
    bool operator>=( const AColumns& b )
    {
        return _columns >= b.columns;
    }
    bool operator>=( const ADepth& b )
    {
        return _depth >= b.depth;
    }

    bool operator<=( const ARows& b )
    {
        return _rows <= b.rows;
    }
    bool operator<=( const AColumns& b )
    {
        return _columns <= b.columns;
    }
    bool operator<=( const ADepth& b )
    {
        return _depth <= b.depth;
    }

    bool operator!=( const ARows& b )
    {
        return _rows != b.rows;
    }
    bool operator!=( const AColumns& b )
    {
        return _columns != b.columns;
    }
    bool operator!=( const ADepth& b )
    {
        return _depth != b.depth;
    }
};


#endif // ASIZE

