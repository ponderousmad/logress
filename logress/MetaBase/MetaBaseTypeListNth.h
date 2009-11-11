#ifndef METABASE_TYPELISTNTH_H__INCLUDED
#define METABASE_TYPELISTNTH_H__INCLUDED
/* ---------------------------------------------------------------
 * Copyright (c) Adrian Smith.
 * Licensed under the MIT license. See license.txt at project root.
 * --------------------------------------------------------------- */

namespace MetaBase {

    template <class List, int N>
    struct Nth
    {
        typedef typename Nth< typename List::Tail, N-1 >::Type Type;
    };

    template <class List>
    struct Nth<List, 0>
    {
        typedef typename List::Type Type;
    };
}

#endif //METABASE_TYPELISTNTH_H__INCLUDED
