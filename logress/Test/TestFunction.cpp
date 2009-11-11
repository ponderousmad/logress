#include "Base/Top.h"

#include "Test/TestFunction.h"

#ifdef BUILD_TESTS

#include "UnitTest/UnitTestFramework.h"
#include "Test/TestEnvironment.h"
#include "Memory/MemoryShared.h"

namespace
{
    using Test::Environment;
    using Test::InvokeContext;
    using Test::ConstFunctionH;
    using Test::buildFunction;

    void foo()
    {
    }

    int bar( int a, double )
    {
        return a;
    }

    double goo( const char* wazoo )
    {
        if( wazoo && wazoo[0] == '"' )
        {
            return -0.1;
        }
        return 0.1;
    }

    class TestFunctionTest : public UnitTest::Framework
    {
    public:
        void run()
        {
            RUN( simpleTest );
        }

        void simpleTest()
        {
            Environment env;


            ConstFunctionH funcFoo( buildFunction( &foo ) );
            ConstFunctionH funcBar( buildFunction( &bar ) );
            ConstFunctionH funcGoo( buildFunction( &goo ) );

            InvokeContext c1( "", env );
            CHECK( funcFoo->invoke( c1 ).check( "", env ) );

            InvokeContext c2( "5, 2", env );
            CHECK( funcBar->invoke( c2 ).check( "5", env ) );

            InvokeContext c3( "\"hello\"", env );
            CHECK( funcGoo->invoke( c3 ).check( "-0.1", env ) );
        }
    };
}

DECLARE_TEST( TestFunctionTest );

#endif

