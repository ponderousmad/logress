#ifndef GEN_SCATTERHIERARCHYSEQUENCED_H__INCLUDED
#define GEN_SCATTERHIERARCHYSEQUENCED_H__INCLUDED
/* ---------------------------------------------------------------
 * Copyright (c) Adrian Smith.
 * Licensed under the MIT license. See license.txt at project root.
 * --------------------------------------------------------------- */

#include "MetaBase/MetaBaseTypeList.h"

/*
 * Gen::ScatterHierarchySequenced is an extension of Gen::ScatterHierarchy
 * that makes explicit the corresponding index in the typelist from which
 * the hierarchy was instantiated.
 *
 * So, the template argument will look something like:
 * template <class Item, int N>
 * ExampleTemplate
 * {
 *   < some code/definitions involving the template parameters Item and N >
 * };
 *
 * Otherwise, everything else is the same.
 */

namespace Gen {
    template <
        template <typename Item, int N> class ItemTemplate,
        int SequenceNumber,
        typename Typelist
    >
    struct ScatterHierarchySeqImpl
        : public ItemTemplate< typename Typelist::Type, SequenceNumber >
        , public ScatterHierarchySeqImpl< ItemTemplate, SequenceNumber + 1, typename Typelist::Tail >
    {};

    template <
        template <typename Item, int N> class ItemTemplate,
        int SequenceNumber
    >
    struct ScatterHierarchySeqImpl< ItemTemplate, SequenceNumber, MetaBase::EmptyTypeList> {};

    template <
        template <typename Item, int N> class ItemTemplate,
        typename Typelist
    >
    struct ScatterHierarchySequenced
        : public ScatterHierarchySeqImpl< ItemTemplate, 0, Typelist >
    {
    };
}

#endif // GEN_SCATTERHIERARCHYSEQUENCED_H__INCLUDED
