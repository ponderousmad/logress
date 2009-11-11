#ifndef METABASE_TYPELISTLENGTH_H__INCLUDED
#define METABASE_TYPELISTLENGTH_H__INCLUDED

#include "MetaBase/MetaBaseTypeList.h"

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
