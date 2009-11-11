#include "Base/Top.h"

#include "Memory/MemoryCounted.h"
#include "Base/BaseAssert.h"

using Memory::Counted;

Counted::~Counted()
{
    ASSERT( mCount == 0 );
}

#ifdef BUILD_TESTS

#include "UnitTest/UnitTestFramework.h"

namespace
{
    class MemoryCountedTest : public UnitTest::Framework
    {
    public:
        void run()
        {
            RUN( countTest );
            RUN( copyTest );
            RUN( assignTest );
        }

        void countTest()
        {
            Counted c;
            c.ref();
            c.ref();
            c.ref();
            CHECK( c.unref() == 2 );
            CHECK( c.unref() == 1 );
            CHECK( c.unref() == 0 );
        }

        void copyTest()
        {
            Counted c;
            c.ref();
            c.ref();

            Counted d( c );
            d.ref();
            d.ref();

            CHECK( c.unref() == 1 );
            CHECK( c.unref() == 0 );

            CHECK( d.unref() == 1 );
            CHECK( d.unref() == 0 );
        }

        void assignTest()
        {
            Counted c;
            Counted d;

            c.ref();
            c.ref();

            d.ref();

            d = c;

            CHECK( c.unref() == 1 );
            CHECK( c.unref() == 0 );

            CHECK( d.unref() == 0 );
        }
    };
}

DECLARE_TEST( MemoryCountedTest );

#endif
