#ifndef GEN_LINEARHIERARCHYSEQUENCED_H__INCLUDED
#define GEN_LINEARHIERARCHYSEQUENCED_H__INCLUDED
/* ---------------------------------------------------------------
 * Copyright (c) Adrian Smith.
 * Licensed under the MIT license. See license.txt at project root.
 * --------------------------------------------------------------- */

#include "MetaBase/MetaBaseTypeList.h"

namespace Gen {
    template <
        template <class Item, int N, class Base> class ItemTemplate,
        int SequenceNumber,
        typename Typelist
    >
    struct LinearHierarchySeqImpl
        : public ItemTemplate<
            typename Typelist::Type,
            SequenceNumber,
            LinearHierarchySeqImpl< ItemTemplate, SequenceNumber+1, typename Typelist::Tail >
        >
    {};

    template <
        template <class Item, int N, class Base> class ItemTemplate,
        int SequenceNumber
    >
    struct LinearHierarchySeqImpl< ItemTemplate, SequenceNumber, MetaBase::EmptyTypeList >
    {};

    template <
        template <class Item, int N, class Base> class ItemTemplate,
        typename Typelist
    >
    struct LinearHierarchySequenced
        : public LinearHierarchySeqImpl< ItemTemplate, 0, Typelist >
    {};
}

#endif // GEN_LINEARHIERARCHYSEQUENCED_H__INCLUDED
