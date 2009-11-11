#include "Base/Top.h"

#include "MetaBase/MetaBaseRemoveReference.h"

#include "MetaBase/MetaBaseTestSwitch.h"

#ifdef COMPILE_METABASE_TESTS

#include "MetaBase/MetaBaseAssert.h"
#include "MetaBase/MetaBaseSame.h"

using namespace MetaBase;

namespace {
    class Foo {};
}

namespace MetaBaseTests {
    void testRemoveReference()
    {
        CompileAssert< Same< int, RemoveReference<int>::Type >::Value >();
        CompileAssert< Same< int, RemoveReference<int&>::Type >::Value >();
        CompileAssert< Same< const int, RemoveReference<const int>::Type >::Value >();
        CompileAssert< Same< const int, RemoveReference<const int&>::Type >::Value >();
        CompileAssert< Same< int*, RemoveReference<int*>::Type >::Value >();
        CompileAssert< Same< int*, RemoveReference<int*&>::Type >::Value >();

        CompileAssert< Same< Foo, RemoveReference<Foo>::Type >::Value >();
        CompileAssert< Same< Foo, RemoveReference<Foo&>::Type >::Value >();
    }
}

#endif // COMPILE_METABASE_TESTS
