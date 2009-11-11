#include "Base/Top.h"

#include "MetaBase/MetaBaseRemoveConst.h"

#include "MetaBase/MetaBaseTestSwitch.h"

#ifdef COMPILE_METABASE_TESTS

#include "MetaBase/MetaBaseAssert.h"
#include "MetaBase/MetaBaseSame.h"

using namespace MetaBase;

namespace {
    class Foo {};
}

namespace MetaBaseTests {
    void testRemoveConst()
    {
        CompileAssert< Same< int, RemoveConst<int>::Type >::Value >();
        CompileAssert< Same< int, RemoveConst<const int>::Type >::Value >();
        CompileAssert< Same< int&, RemoveConst<int&>::Type >::Value >();
        CompileAssert< Same< const int&, RemoveConst<const int&>::Type >::Value >();
        CompileAssert< Same< int*, RemoveConst<int*>::Type >::Value >();
        CompileAssert< Same< const int*, RemoveConst<const int*>::Type >::Value >();
        CompileAssert< Same< const int*, RemoveConst<const int* const>::Type >::Value >();

        CompileAssert< Same< Foo, RemoveConst<Foo>::Type >::Value >();
        CompileAssert< Same< Foo, RemoveConst<const Foo>::Type >::Value >();
    }
}

#endif // COMPILE_METABASE_TESTS
