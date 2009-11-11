#include "Base/Top.h"

#include "Gen/GenLinearHierarchy.h"

#include "Gen/GenTestSwitch.h"

#ifdef COMPILE_GEN_TESTS

#include <iostream>

namespace {
    template <typename T>
    struct Storage {
        T value;
    };

    template <typename T, class Base>
    struct StoreLinear : public Base, public Storage<T>
    {
    };
}

namespace GenTests {
    void testLinearHierarchy()
    {
        typedef Gen::LinearHierarchy< StoreLinear, TYPELIST_2( int, double ) > StoreIntDouble;

        StoreIntDouble store;
        Storage<int>& storeInt = store;
        Storage<double>& storeDouble = store;

        storeInt.value = 5;
        storeDouble.value = 5.5;
    }
}

#endif // COMPILE_GEN_TESTS
