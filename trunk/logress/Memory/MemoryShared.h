#ifndef MEMORY_SHARED_H__INCLUDED
#define MEMORY_SHARED_H__INCLUDED

#include "Memory/MemoryFwd.h"
#include "Memory/MemoryException.h"

namespace Memory
{
    template <typename T>
    class Shared;
}

template <typename T>
class Memory::Shared
{
public:
    typedef T ValueType;
    typedef Shared< const T > Const;

    Shared( T* item = 0 )
        : mItem( item )
    {
        ref( item );
    }

    Shared( const Shared& other )
        : mItem( other.mItem )
    {
        ref( mItem );
    }

    template <typename U>
    Shared( const Shared<U>& other )
        : mItem( other.get() )
    {
        ref( mItem );
    }

    ~Shared()
    {
        unref( mItem );
        mItem = 0;
    }

    bool isNull() const
    {
        return mItem == 0;
    }

    // Must include this one as well as the next
    // otherwise we get the 'default' assign
    // which won't update refs correctly
    Shared& operator=( const Shared& other )
    {
        assign( other.get() );
        return *this;
    }

    template <typename U>
    Shared& operator=( const Shared<U>& other )
    {
        assign( other.get() );
        return *this;
    }

    template <typename U>
    Shared& operator=( U* other )
    {
        assign( other );
        return *this;
    }

    T& operator*() const
    {
        if( mItem == 0 )
        {
            throw Memory::Exception( "Attempt to dereference null pointer." );
        }
        return *mItem;
    }

    T* operator->() const
    {
        if( mItem == 0 )
        {
            throw Memory::Exception( "Attempt to dereference null pointer." );
        }
        return mItem;
    }

    T* get() const
    {
        return mItem;
    }

    template <typename U>
    bool operator==( const Shared<U>& other )
    {
        return other.mItem == mItem;
    }

private:
    Shared& assign( T* other )
    {
        ref( other );
        unref( mItem );
        mItem = other;
        return *this;
    }

    static void ref( T* item )
    {
        if( item )
        {
            item->ref();
        }
    }

    static void unref( T* item )
    {
        if( item )
        {
            int count = item->unref();
            if( count < 0 ) {
                throw Memory::Exception( "Unexpected: negative count." );
            }
            if( count == 0 )
            {
                delete item;
            }
        }
    }

    T* mItem;
};

namespace
{
    template <typename T, typename U>
    bool operator==( const Memory::Shared<T>& shared, const U* ptr )
    {
        return shared.get() == ptr;
    }

    template <typename T, typename U>
    bool operator==( const T* ptr, const Memory::Shared<T>& shared )
    {
        return shared.get() == ptr;
    }

}

#endif // MEMORY_SHARED_H__INCLUDED
