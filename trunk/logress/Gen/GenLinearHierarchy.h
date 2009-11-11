#ifndef GEN_LINEARHIERARCHY_H__INCLUDED
#define GEN_LINEARHIERARCHY_H__INCLUDED
/* ---------------------------------------------------------------
 * Copyright (c) Adrian Smith.
 * Licensed under the MIT license. See license.txt at project root.
 * --------------------------------------------------------------- */

#include "MetaBase/MetaBaseTypeList.h"

namespace Gen {
    template <
        template <class Item, class Base> class ItemTemplate,
        typename Typelist
    >
    struct LinearHierarchy
        : public ItemTemplate<
            typename Typelist::Type,
            LinearHierarchy< ItemTemplate, typename Typelist::Tail >
        >
    {};

    template < template <class Item, class Base> class ItemTemplate >
    struct LinearHierarchy< ItemTemplate, MetaBase::EmptyTypeList >
    {};
}

#endif // GEN_LINEARHIERARCHY_H__INCLUDED
