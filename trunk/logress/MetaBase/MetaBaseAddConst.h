#ifndef METABASE_ADDCONST_H__INCLUDED
#define METABASE_ADDCONST_H__INCLUDED
/* ---------------------------------------------------------------
 * Copyright (c) Adrian Smith.
 * Licensed under the MIT license. See license.txt at project root.
 * --------------------------------------------------------------- */

#include "MetaBase/MetaBaseBoolType.h"
#include "MetaBase/MetaBaseTypeTraits.h"
#include "MetaBase/MetaBaseAddReference.h"
#include "MetaBase/MetaBaseRemoveReference.h"

/*
 * Given a type, produce a new const type, if the type was not already const.
 * Note that this will only add constness at the outer most level, so
 * you may have to first deconstruct the type to add the appropriate const.
 * For example, the following will produce a constant pointer to int, not
 * a pointer to a const int:
 *
 * Metabase::AddConst< int* >::Type
 *
 * However, since adding constness to references is not useful, this will
 * add constness through reference types.
 */
namespace MetaBase {
    template <typename T,bool IsConst, bool isRef>
    struct AddConstImpl { typedef const T Type; };

    template <typename T>
    struct AddConstImpl<T, true, true> { typedef T Type; };

    template <typename T>
    struct AddConstImpl<T, true, false> { typedef T Type; };

    template <typename T>
    struct AddConstImpl<T, false, true> {
        typedef MetaBase::RemoveReference<T> Remover;
        typedef typename Remover::Type NoRef;
        typedef typename MetaBase::AddReference< const NoRef >::Type Type;
    };

    template <typename T>
    struct AddConst
    {
        typedef typename AddConstImpl< T, IsConst<T>::Value, IsReference<T>::Value >::Type Type;
    };
}

#endif // METABASE_ADDCONST_H__INCLUDED
