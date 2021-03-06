#ifndef METABASE_ADDREFERENCE_H__INCLUDED
#define METABASE_ADDREFERENCE_H__INCLUDED
/* ---------------------------------------------------------------
 * Copyright (c) Adrian Smith.
 * Licensed under the MIT license. See license.txt at project root.
 * --------------------------------------------------------------- */

#include "MetaBase/MetaBaseBoolType.h"
#include "MetaBase/MetaBaseTypeTraits.h"

/*
 * Given a type, produce the reference version of that type, if not reference already.
 * For example, the following will evaluate to the type int&:
 * Metabase::AddReference< int >::Type
 */

namespace MetaBase {
    template <typename T,bool IsRef>
    struct AddReferenceImpl { typedef T& Type; };

    template <typename T>
    struct AddReferenceImpl<T,true> { typedef T Type; };

    template <typename T>
    struct AddReference
    {
        typedef typename AddReferenceImpl< T, IsReference<T>::Value >::Type Type;
    };
}

#endif // METABASE_ADDREFERENCE_H__INCLUDED
