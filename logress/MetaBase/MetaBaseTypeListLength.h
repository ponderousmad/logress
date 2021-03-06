#ifndef METABASE_TYPELISTLENGTH_H__INCLUDED
#define METABASE_TYPELISTLENGTH_H__INCLUDED
/* ---------------------------------------------------------------
 * Copyright (c) Adrian Smith.
 * Licensed under the MIT license. See license.txt at project root.
 * --------------------------------------------------------------- */

#include "MetaBase/MetaBaseTypeList.h"

/*
 * Given a type list, determine its length.
 *
 * For example, the following has the value 3:
 * MetaBase::ListLength< TYPELIST_3( int, int, int) >::Value
 */

namespace MetaBase {
    template <class List>
    struct ListLength
    {
        enum { Value = 1 + ListLength< typename List::Tail >::Value };
    };

    template <>
    struct ListLength<EmptyTypeList>
    {
        enum { Value = 0 };
    };
}

#endif //METABASE_TYPELISTLENGTH_H__INCLUDED
