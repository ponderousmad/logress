#ifndef METABASE_REMOVECONST_H__INCLUDED
#define METABASE_REMOVECONST_H__INCLUDED
/* ---------------------------------------------------------------
 * Copyright (c) Adrian Smith.
 * Licensed under the MIT license. See license.txt at project root.
 * --------------------------------------------------------------- */

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
