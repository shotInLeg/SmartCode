#ifndef ACL
#define ACL

#include <iostream>
#include <aarray.h>
#include <aarray.cpp>
#include <aexception.h>
#include <aiterator.h>
#include <asize.h>


typedef  AArray<int, Array<int> > int_$;
typedef  AArray<double, Array<double> > double_$;
typedef  AArray<char, Array<char> > char_$;
typedef  AArray<bool, Array<bool> > bool_$;
typedef  AArray<char*, Array<int> > string_$;

typedef  AArray<int, Matrix<int> > int_$$;
typedef  AArray<double, Matrix<double> > double_$$;
typedef  AArray<char, Matrix<char> > char_$$;
typedef  AArray<bool, Matrix<bool> > bool_$$;
typedef  AArray<char*, Matrix<char*> > string_$$;

typedef  AArray<int, Tenzor<int> > int_$$$;
typedef  AArray<double, Tenzor<double> > double_$$$;
typedef  AArray<char, Tenzor<char> > char_$$$;
typedef  AArray<bool, Tenzor<bool> > bool_$$$;
typedef  AArray<char*, Tenzor<char*> > string_$$$;

typedef AIterator<int> itr_int;
typedef AIterator<double> itr_double;
typedef AIterator<float> itr_float;
typedef AIterator<char> itr_char;
typedef AIterator<bool> itr_bool;


typedef ASize asize;
typedef ARows rows;
typedef AColumns cols;
typedef ADepth depth;


#endif // ACL

