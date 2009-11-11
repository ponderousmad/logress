#ifndef METABASE_REMOVECONST_H__INCLUDED
#define METABASE_REMOVECONST_H__INCLUDED
/* ---------------------------------------------------------------
 * Copyright (c) Adrian Smith.
 * Licensed under the MIT license. See license.txt at project root.
 * --------------------------------------------------------------- */

/*
 * Given some type, removes the outermost const (if present).
 *
 * For example, the following will result in type type const int*
 * Metabase::RemoveConst< const int* const >::Type
 *
 * To remove other constness may require deconstrucing the type first.
 */

namespace MetaBase {

    template <typename T>
    struct RemoveConst
    {
        typedef T Type;
    };

    template <typename T>
    struct RemoveConst<const T>
    {
        typedef T Type;
    };
}

#endif // METABASE_REMOVECONST_H__INCLUDED
