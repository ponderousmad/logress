#ifndef MEMORY_COUNTED_H__INCLUDED
#define MEMORY_COUNTED_H__INCLUDED

#include "Memory/MemoryFwd.h"

class Memory::Counted
{
public:
    Counted()
        : mCount( 0 )
    {
    }

    Counted( const Counted& )
        : mCount( 0 )
    {
    }

    ~Counted();

    Counted& operator=( const Counted& )
    {
        return *this;
    }

    void ref() const { ++mCount; }
    int unref() const { --mCount; return mCount; }

private:
    mutable int mCount;
};

#endif // MEMORY_COUNTED_H__INCLUDED