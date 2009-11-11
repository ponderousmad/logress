/* ---------------------------------------------------------------
 * Copyright (c) Adrian Smith.
 * Licensed under the MIT license. See license.txt at project root.
 * --------------------------------------------------------------- */
#include "Base/Top.h"

#include "MetaBase/MetaBaseAddReference.h"

#include "MetaBase/MetaBaseTestSwitch.h"

#ifdef COMPILE_METABASE_TESTS

#include "MetaBase/MetaBaseAssert.h"
#include "MetaBase/MetaBaseSame.h"

using namespace MetaBase;

namespace {
    class Foo {};
}

namespace MetaBaseTests {
    void testAddReference()
    {
        CompileAssert< Same< int&, AddReference<int>::Type >::Value >();
        CompileAssert< Same< int&, AddReference<int&>::Type >::Value >();
        CompileAssert< Same< const int&, AddReference<const int>::Type >::Value >();
        CompileAssert< Same< const int&, AddReference<const int&>::Type >::Value >();
        CompileAssert< Same< int*&, AddReference<int*>::Type >::Value >();
        CompileAssert< Same< int*&, AddReference<int*&>::Type >::Value >();

        CompileAssert< Same< Foo&, AddReference<Foo>::Type >::Value >();
        CompileAssert< Same< Foo&, AddReference<Foo&>::Type >::Value >();
    }
}

#endif // COMPILE_METABASE_TESTS
