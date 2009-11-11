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
