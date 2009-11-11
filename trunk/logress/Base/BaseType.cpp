/* ---------------------------------------------------------------
 * Copyright (c) Adrian Smith.
 * Licensed under the MIT license. See license.txt at project root.
 * --------------------------------------------------------------- */
#include "Base/Top.h"

#include "Base/BaseType.h"

using Base::Type;

Type::Type()
    : mID( 0 )
{
}

Type::Type( const TypeID& id )
    : mID( &id )
{
}

Type::Type( const Type& other )
    : mID( other.mID )
{
}

Type& Type::operator=( const Type& other )
{
    mID = other.mID;
    return *this;
}

bool Type::operator==( const Type& other ) const
{
    return ( mID != 0 && other.mID != 0 && *mID == *other.mID ) ||
           ( mID == 0 && other.mID == 0 );
}

bool Type::operator<( const Type& other ) const
{
    if( mID == 0 || other.mID == 0 )
    {
        return other.mID != 0;
    }
    return mID->before( *other.mID ) != 0;
}

