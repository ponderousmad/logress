#ifndef MEMORY_EXCEPTION_H__INCLUDED
#define MEMORY_EXCEPTION_H__INCLUDED
/* ---------------------------------------------------------------
 * Copyright (c) Adrian Smith.
 * Licensed under the MIT license. See license.txt at project root.
 * --------------------------------------------------------------- */

#include "Memory/MemoryFwd.h"
#include "Base/BaseException.h"

class Memory::Exception : public Base::Exception
{
public:
    Exception( const char* message = 0 )
        : Base::Exception( message )
    {
    }
};

#endif // MEMORY_EXCEPTION_H__INCLUDED
