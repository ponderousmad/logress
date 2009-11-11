#ifndef BASE_EXCEPTION_H__INCLUDED
#define BASE_EXCEPTION_H__INCLUDED
/* ---------------------------------------------------------------
 * Copyright (c) Adrian Smith.
 * Licensed under the MIT license. See license.txt at project root.
 * --------------------------------------------------------------- */

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
