/* ---------------------------------------------------------------
 * Copyright (c) Adrian Smith.
 * Licensed under the MIT license. See license.txt at project root.
 * --------------------------------------------------------------- */
#include "Base/Top.h"

#include "MetaBase/MetaBaseTypeTraits.h"

#include "MetaBase/MetaBaseTestSwitch.h"

#ifdef COMPILE_METABASE_TESTS

#include "MetaBase/MetaBaseAssert.h"

using namespace MetaBase;

namespace {
    class Foo {};
}

namespace MetaBaseTests {
    void testIsConst()
    {
        CompileAssert< !IsConst< int >::Value >();
        CompileAssert<  IsConst< const int>::Value >();

        CompileAssert<  IsConst< const Foo >::Value >();
        CompileAssert< !IsConst< const Foo* >::Value >();
        CompileAssert<  IsConst< Foo* const >::Value >();
        CompileAssert<  IsConst< const Foo* const > ::Value >();

        CompileAssert< !IsConst< Foo& >::Value >();
        CompileAssert<  IsConst< const Foo& >::Value >();
    }

    void testIsRef()
    {
        CompileAssert< !IsReference< int >::Value >();
        CompileAssert< !IsReference< const int>::Value >();

        CompileAssert< !IsReference< const Foo >::Value >();
        CompileAssert< !IsReference< const Foo* >::Value >();
        CompileAssert< !IsReference< Foo* const >::Value >();
        CompileAssert< !IsReference< const Foo* const > ::Value >();

        CompileAssert<  IsReference< Foo& >::Value >();
        CompileAssert<  IsReference< const Foo& >::Value >();

        CompileAssert<  IsReference< Foo*& >::Value >();
    }

    void testIsNull()
    {
        CompileAssert<  IsNull< NullType >::Value >();
        CompileAssert<  IsNull< const NullType >::Value >();
        CompileAssert< !IsNull< Foo >::Value >();
        CompileAssert< !IsNull< NullType& >::Value >();
        CompileAssert< !IsNull< NullType* >::Value >();
        CompileAssert< !IsNull< int >::Value >();
    }
}

#endif // COMPILE_METABASE_TESTS
