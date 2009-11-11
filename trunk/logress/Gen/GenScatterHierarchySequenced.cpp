/* ---------------------------------------------------------------
 * Copyright (c) Adrian Smith.
 * Licensed under the MIT license. See license.txt at project root.
 * --------------------------------------------------------------- */
#include "Base/Top.h"

#include "Gen/GenScatterHierarchySequenced.h"

#include "Gen/GenTestSwitch.h"

#ifdef COMPILE_GEN_TESTS

#include "MetaBase/MetaBaseTypeListNth.h"

namespace {
    template <typename Typelist>
    class StorageSequence
    {
    private:
        template <typename T, int N> struct Item {
            T value;
        };
        typedef Gen::ScatterHierarchySequenced< Item, Typelist > Store;

        Store mStore;

    public:

        template <int N>
        const typename MetaBase::Nth< Typelist, N >::Type& item() const
        {
            return ((const Item< typename MetaBase::Nth< Typelist, N >::Type, N >&)mStore).value;
        }

        template <int N>
        typename MetaBase::Nth< Typelist, N >::Type& item()
        {
            return ((Item< typename MetaBase::Nth< Typelist, N >::Type, N >&)mStore).value;
        }
    };
}

namespace GenTests {
    void testScatterHierarchySequence()
    {
        StorageSequence< TYPELIST_2( int, double ) > storeIntDouble;
        storeIntDouble.item<0>() = 5;
        storeIntDouble.item<1>() = 5.5;
    }
}

#endif // COMPILE_GEN_TESTS
