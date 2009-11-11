#ifndef METABASE_REMOVEREFERENCE_H__INCLUDED
#define METABASE_REMOVEREFERENCE_H__INCLUDED
/* ---------------------------------------------------------------
 * Copyright (c) Adrian Smith.
 * Licensed under the MIT license. See license.txt at project root.
 * --------------------------------------------------------------- */

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
