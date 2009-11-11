#ifndef MEMORY_EXCEPTION_H__INCLUDED
#define MEMORY_EXCEPTION_H__INCLUDED

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
