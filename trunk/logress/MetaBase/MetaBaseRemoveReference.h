#ifndef METABASE_REMOVEREFERENCE_H__INCLUDED
#define METABASE_REMOVEREFERENCE_H__INCLUDED
/* ---------------------------------------------------------------
 * Copyright (c) Adrian Smith.
 * Licensed under the MIT license. See license.txt at project root.
 * --------------------------------------------------------------- */


/*
 * Given some type, produce the non-reference version of the type,
 * or do nothing if the type was not a reference type.
 *
 * For example, the following will result in type type const int
 * Metabase::RemoveConst< const int& >::Type
 */

namespace MetaBase {

    template <typename T>
    struct RemoveReference
    {
        typedef T Type;
    };

    template <typename T>
    struct RemoveReference<T&>
    {
        typedef T Type;
    };
}

#endif // METABASE_REMOVEREFERENCE_H__INCLUDED
