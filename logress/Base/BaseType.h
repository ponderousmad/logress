#ifndef BASE_TYPE_H__INCLUDED
#define BASE_TYPE_H__INCLUDED
/* ---------------------------------------------------------------
 * Copyright (c) Adrian Smith.
 * Licensed under the MIT license. See license.txt at project root.
 * --------------------------------------------------------------- */

#include <typeinfo>

/*
 * Wrap the runtime type identification information to allow for
 * type comparison and inclusion in std container classes.
 */

namespace Base
{
    class Type;
}

class Base::Type
{
public:
    typedef const std::type_info TypeID;
    Type();
    Type( const TypeID& id );
    Type( const Type& other );
    Type& operator=( const Type& other );

    bool operator==( const Type& other ) const;

    // For use in standard containers.
    bool operator<( const Type& other ) const;
private:
    TypeID* mID;
};

#endif // BASE_TYPE_H__INCLUDED
