#ifndef MEMORY_COUNTED_H__INCLUDED
#define MEMORY_COUNTED_H__INCLUDED
/* ---------------------------------------------------------------
 * Copyright (c) Adrian Smith.
 * Licensed under the MIT license. See license.txt at project root.
 * --------------------------------------------------------------- */

#include "Memory/MemoryFwd.h"

/*
 * Implements the reference counting contract required by Memory::Shared.
 * Simply derive publicly from this class.
 */

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
