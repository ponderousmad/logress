#ifndef GEN_LINEARHIERARCHYSEQUENCED_H__INCLUDED
#define GEN_LINEARHIERARCHYSEQUENCED_H__INCLUDED
/* ---------------------------------------------------------------
 * Copyright (c) Adrian Smith.
 * Licensed under the MIT license. See license.txt at project root.
 * --------------------------------------------------------------- */

#include "MetaBase/MetaBaseTypeList.h"

/*
 * Gen::LinearHierarchySequenced is an extension of Gen::LinearHierarchy
 * that makes explicit the corresponding index in the typelist from which
 * the hierarchy was instantiated.
 *
 * So, the template argument will look something like:
 * template <class Item, int N, class Base>
 * ExampleTemplate : public Base
 * {
 *   < some code/definitions involving the template parameters Item and N >
 * };
 *
 * Otherwise, everything else is the same.
 */

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
