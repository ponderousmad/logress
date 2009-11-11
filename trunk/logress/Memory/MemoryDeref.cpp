/* ---------------------------------------------------------------
 * Copyright (c) Adrian Smith.
 * Licensed under the MIT license. See license.txt at project root.
 * --------------------------------------------------------------- */
#include "Base/Top.h"

#include "Memory/MemoryDeref.h"

#ifdef BUILD_TESTS

#include "UnitTest/UnitTestFramework.h"
#include "Memory/MemoryShared.h"
#include "Memory/MemoryCounted.h"

namespace
{
    class Foo : public Memory::Counted
    {
    public:
        bool func() { return true; }
    };
    typedef Memory::Shared<Foo> Foo_H;
    typedef Memory::Deref<Foo,Foo_H> FooDeref;

    class MemoryDerefTest : public UnitTest::Framework
    {
    public:
        void run()
        {
            RUN( simpleTest );
        }

        FooDeref bar( Foo_H handle )
        {
            return handle;
        }

        void simpleTest()
        {
            Foo_H h( new Foo() );
            Foo& foo = bar( h );
            CHECK( foo.func() );
        }
    };
}

DECLARE_TEST( MemoryDerefTest );

#endif
