#ifndef SEXCEPTION
#define SEXCEPTION

#include <stdexcept>

class AException : public std::exception
{
private:
    unsigned _code;
    char* _message;
public:
    AException();
    AException(unsigned code);
    AException(unsigned code, std::exception &ex);

    unsigned code() const;
    char* message() const;
};


AException::AException()
{
    _code = 0x000000;
    _message = (char*)"Alright:)";
}

AException::AException(unsigned code)
{
    switch( code )
    {
    case 0x000000:
        _code = code;
        _message = (char*)"Alright:)";
        break;
    case 0x000001:
        _code = code;
        _message = (char*)"Out of range";
        break;
    case 0x000002:
        _code = code;
        _message = (char*)"IO Error";
        break;
    case 0x000003:
        _code = code;
        _message = (char*)"Invalid argument";
        break;
    case 0x000004:
        _code = code;
        _message = (char*)"Bad alloc";
        break;
    default:
        _code = code;
        _message = (char*)"Something error";
    }
}

AException::AException(unsigned code, std::exception &ex):std::exception( ex )
{
    switch( code )
    {
    case 0x000000:
        _code = code;
        _message = (char*)"Alright:)";
        break;
    case 0x000001:
        _code = code;
        _message = (char*)"Out of range";
        break;
    case 0x000002:
        _code = code;
        _message = (char*)"IO Error";
        break;
    case 0x000003:
        _code = code;
        _message = (char*)"Invalid argument";
        break;
    case 0x000004:
        _code = code;
        _message = (char*)"Bad alloc";
        break;
    default:
        _code = code;
        _message = (char*)"Something error";
    }
}

unsigned AException::code() const
{
    return _code;
}

char* AException::message() const
{
    return _message;
}


#define OUT_OF_RANGE 0x000001
#define IO_EXCEPTION 0x000002
#define INVALID_ARGUMENT 0x000003
#define BAD_ALLOC 0x000004


#endif // SEXCEPTION

/*
 * 0x000001 - Out of range
 * 0x000002 - IO Exception
 * 0x000003 - Invalid argument
 * 0x000004 - Bad alloc
*/



