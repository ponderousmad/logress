#include "Base/Top.h"

#include "Test/TestMethod.h"

#ifdef BUILD_TESTS

#include "UnitTest/UnitTestFramework.h"
#include "Test/TestEnvironment.h"

namespace
{
    using Test::Environment;
    using Test::InvokeContext;
    using Test::IMethod;
    using Test::buildMethod;

    class Foo
    {
    public:
        Foo( int value )
            : mValue( value )
        {
        }

        void foo()
        {
        }

        int bar( int a, double )
        {
            return a;
        }

        double goo( const char* wazoo ) const
        {
            if( wazoo && wazoo[0] == '"' )
            {
                return -0.1;
            }
            return 0.1;
        }

        int getValue()
        {
            return mValue;
        }

        int mValue;
    };


    typedef Memory::Shared< IMethod<Foo> > FooMethodH;

    class TestMethodTest : public UnitTest::Framework
    {
    public:
        void run()
        {
            RUN( simpleTest );
        }

        void simpleTest()
        {
            Environment env;
            Foo f( 110 );

            FooMethodH funcFoo( buildMethod( &Foo::foo ) );
            FooMethodH funcBar( buildMethod( &Foo::bar ) );
            FooMethodH funcGoo( buildMethod( &Foo::goo ) );
            FooMethodH funcGet( buildMethod( &Foo::getValue ) );


            InvokeContext c1( "", env );
            CHECK( funcFoo->invoke( f, c1 ).check( "", env ) );

            InvokeContext c2( "5, 2", env );
            CHECK( funcBar->invoke( f, c2 ).check( "5", env ) );

            InvokeContext c3( "\"hello\"", env );
            CHECK( funcGoo->invoke( f, c3 ).check( "-0.1", env ) );

            InvokeContext c4( "", env );
            CHECK( funcGet->invoke( f, c4 ).check( "110", env ) );

            f.mValue = 1;
            InvokeContext c5( "", env );
            CHECK( funcGet->invoke( f, c5 ).check( "1", env ) );
        }
    };
}

DECLARE_TEST( TestMethodTest );

#endif

