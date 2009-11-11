#include "Base/Top.h"

#include "MetaBase/MetaBaseAddConst.h"

#include "MetaBase/MetaBaseTestSwitch.h"

#ifdef COMPILE_METABASE_TESTS

#include "MetaBase/MetaBaseAssert.h"
#include "MetaBase/MetaBaseSame.h"

using namespace MetaBase;

namespace {
    class Foo {};
}

namespace MetaBaseTests {
    void testAddConst()
    {
        CompileAssert< Same< const int, AddConst<int>::Type >::Value >();
        CompileAssert< Same< const int, AddConst<const int>::Type >::Value >();
        CompileAssert< Same< const int&, AddConst<int&>::Type >::Value >();
        CompileAssert< Same< const int&, AddConst<const int&>::Type >::Value >();
        CompileAssert< Same< int* const, AddConst<int*>::Type >::Value >();
        CompileAssert< Same< const int* const, AddConst<const int*>::Type >::Value >();

        CompileAssert< Same< const Foo, AddConst<Foo>::Type >::Value >();
        CompileAssert< Same< const Foo, AddConst<const Foo>::Type >::Value >();
    }
}

#endif // COMPILE_METABASE_TESTS
