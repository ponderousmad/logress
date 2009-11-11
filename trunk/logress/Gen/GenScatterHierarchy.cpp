#include "Base/Top.h"

#include "Gen/GenScatterHierarchy.h"

#include "Gen/GenTestSwitch.h"

#ifdef COMPILE_GEN_TESTS

namespace {
    template <typename T>
    struct Storage {
        T value;
    };
}

namespace GenTests {
    void testScatterHierarchy()
    {
        typedef Gen::ScatterHierarchy< Storage, TYPELIST_2( int, double ) > StoreIntDouble;

        StoreIntDouble store;
        Storage<int>& storeInt = store;
        Storage<double>& storeDouble = store;

        storeInt.value = 5;
        storeDouble.value = 5.5;
    }
}

#endif // COMPILE_GEN_TESTS
