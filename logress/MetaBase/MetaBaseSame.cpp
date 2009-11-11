/* ---------------------------------------------------------------
 * Copyright (c) Adrian Smith.
 * Licensed under the MIT license. See license.txt at project root.
 * --------------------------------------------------------------- */
#include "Base/Top.h"

#include "MetaBase/MetaBaseSame.h"

#include "MetaBase/MetaBaseTestSwitch.h"

#ifdef COMPILE_METABASE_TESTS

#include "MetaBase/MetaBaseAssert.h"

using namespace MetaBase;

namespace {
    class Foo {};
    class Bar {};

    class Derived : public Foo {};
}

namespace MetaBaseTests {
    void testSame()
    {
        CompileAssert< Same< int, int >::Value >();
        CompileAssert< Same< int*, int*>::Value >();

        typedef int AnInt;
        CompileAssert< Same< AnInt, int >::Value >();

        CompileAssert< Same< Foo, Foo >::Value >();
        CompileAssert< Same< const Foo&, const Foo& >::Value >();
        CompileAssert< Same< const Foo, Foo const >::Value >();

        CompileAssert< !Same< int, Foo >::Value >();
        CompileAssert< !Same< int, const int >::Value >();
        CompileAssert< !Same< int, int& >::Value >();

        CompileAssert< !Same< Foo, Bar >::Value >();
        CompileAssert< !Same< Foo, Derived >::Value >();
    }
}

#endif // COMPILE_METABASE_TESTS
