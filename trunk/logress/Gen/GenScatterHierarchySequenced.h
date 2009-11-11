#ifndef GEN_SCATTERHIERARCHYSEQUENCED_H__INCLUDED
#define GEN_SCATTERHIERARCHYSEQUENCED_H__INCLUDED

#include "MetaBase/MetaBaseTypeList.h"

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
