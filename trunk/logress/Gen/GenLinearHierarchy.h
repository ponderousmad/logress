#ifndef GEN_LINEARHIERARCHY_H__INCLUDED
#define GEN_LINEARHIERARCHY_H__INCLUDED
/* ---------------------------------------------------------------
 * Copyright (c) Adrian Smith.
 * Licensed under the MIT license. See license.txt at project root.
 * --------------------------------------------------------------- */

#include "MetaBase/MetaBaseTypeList.h"

/*
 * This follows the design from "Modern C++ Design" and provides a way
 * of instantiating a template for each element in a type list, such that
 * the instantiations are all parents of the instantiations for the types later
 * in the list.
 *
 * The requirements on the Item template are more stringent than that for
 * Gen::ScatterHierarchy, as the template implementation must have the following
 * structure:
 * template <class Item, class Base>
 * ExampleTemplate : public Base
 * {
 *   < some code/definitions involving the Item template parameter >
 * };
 *
 * So, Gen::LinearHierarchy< ExampleTemplate, TYPELIST_2( int, double ) >
 * would derive from instatiations of ExampleTemplate with int and double
 * as the first argument, and some instatiations of LinearHierarchy as the
 * second template argument.
 */

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
