#ifndef METABASE_TYPELISTNTH_H__INCLUDED
#define METABASE_TYPELISTNTH_H__INCLUDED
/* ---------------------------------------------------------------
 * Copyright (c) Adrian Smith.
 * Licensed under the MIT license. See license.txt at project root.
 * --------------------------------------------------------------- */

/*
 * Given a type list and an integer N, this will access the Nth element of the list.
 * Note that the index is zero based.
 * For example, the following evaluates to the type double:
 * MetaBase::Nth< TYPELIST_3( int, double, float ), 1 > ::Type
 */

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
