#ifndef GEN_SCATTERHIERARCHY_H__INCLUDED
#define GEN_SCATTERHIERARCHY_H__INCLUDED
/* ---------------------------------------------------------------
 * Copyright (c) Adrian Smith.
 * Licensed under the MIT license. See license.txt at project root.
 * --------------------------------------------------------------- */

#include "MetaBase/MetaBaseTypeList.h"

namespace Gen {
    template <
        template <typename Item> class ItemTemplate,
        typename Typelist
    >
    struct ScatterHierarchy
        : public ItemTemplate< typename Typelist::Type >
        , public ScatterHierarchy< ItemTemplate, typename Typelist::Tail >
    {};

    template < template <typename Item> class ItemTemplate >
    struct ScatterHierarchy< ItemTemplate, MetaBase::EmptyTypeList> {};
}

#endif // GEN_SCATTERHIERARCHY_H__INCLUDED
