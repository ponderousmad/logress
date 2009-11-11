#include "Base/Top.h"

#include "Memory/MemoryShared.h"


#ifdef BUILD_TESTS

#include "UnitTest/UnitTestFramework.h"
#include "Memory/MemoryCounted.h"

namespace
{
    class CountInstances : public Memory::Counted
    {
    public:
        CountInstances()
        {
            ++sCount;
        }

        CountInstances( const CountInstances& )
        {
            ++sCount;
        }

        virtual ~CountInstances()
        {
            --sCount;
        }

        bool func() { return true; }

        static int count() { return sCount; };
        static int sCount;
    };

    int CountInstances::sCount = 0;
    typedef Memory::Shared<CountInstances> Handle;

    class CountInstancesChild : public CountInstances
    {
    };

    typedef Memory::Shared<CountInstancesChild> ChildHandle;

    class MemorySharedTest : public UnitTest::Framework
    {
    public:
        void run()
        {
            RUN( simpleTest );
            RUN( parameterTest );
            RUN( derivedTest );
        }

        void simpleTest()
        {
            Handle h( new CountInstances() );
            CHECK( CountInstances::count() == 1 );

            CHECK( h->func() );
            CountInstances& thing = *h;
            CHECK( thing.func() );

            h = 0;
            CHECK( CountInstances::count() == 0 );
        }

        void foo( Handle handle )
        {
            CHECK( handle->func() );
        }

        void parameterTest()
        {
            Handle h( new CountInstances() );
            CHECK( CountInstances::count() == 1 );
            foo( h );
            h = 0;
            CHECK( CountInstances::count() == 0 );
        }

        void derivedTest()
        {
            Handle h;

            ChildHandle c( new CountInstancesChild() );
            CHECK( CountInstances::count() == 1 );
            h = c;
            CHECK( CountInstances::count() == 1 );
            c = 0;
            CHECK( CountInstances::count() == 1 );
            h = 0;
            CHECK( CountInstances::count() == 0 );
        }
    };
}

DECLARE_TEST( MemorySharedTest );

#endif
