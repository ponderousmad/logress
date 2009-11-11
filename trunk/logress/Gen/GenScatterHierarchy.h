#ifndef GEN_SCATTERHIERARCHY_H__INCLUDED
#define GEN_SCATTERHIERARCHY_H__INCLUDED
/* ---------------------------------------------------------------
 * Copyright (c) Adrian Smith.
 * Licensed under the MIT license. See license.txt at project root.
 * --------------------------------------------------------------- */

#include "MetaBase/MetaBaseTypeList.h"

/*
 * This follows the design from "Modern C++ Design" and provides a way
 * of instantiating a template for each element in a type list. Unlike
 * Gen::LinearHierarchy, the instatiations of the Item template are
 * not in a linear chain, but are scattered over a complex inheritance hierarchy.
 *
 * The ItemTemplate argument does not have any requirements as to the structure
 * of its implementation.
 */

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
