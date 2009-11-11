#ifndef BASE_EXCEPTION_H__INCLUDED
#define BASE_EXCEPTION_H__INCLUDED

namespace Base
{
    class Exception;
}

class Base::Exception
{
public:
    Exception( const char* message = 0 )
        : mMessage( message )
    {
    }

    const char* mMessage;
};

#endif // BASE_EXCEPTION_H__INCLUDED
