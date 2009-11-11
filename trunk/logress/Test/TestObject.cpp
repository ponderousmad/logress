#include "Base/Top.h"

#include "Test/TestObject.h"

#ifdef BUILD_TESTS

#include "UnitTest/UnitTestFramework.h"
#include "Test/TestEnvironment.h"

namespace
{
    using Test::Environment;
    using Test::InvokeContext;
    using Test::IObject;
    using Test::Object;
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

    class TestObjectTest : public UnitTest::Framework
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

            VTABLE_DECLARE( Foo, vTable );
            VTABLE_ADD( vTable, foo );
            VTABLE_ADD( vTable, bar );
            VTABLE_ADD( vTable, goo );
            VTABLE_ADD( vTable, getValue );

            Test::IObject* obj( new Object<Foo>( &f, vTable ) );

            InvokeContext c1( "", env );
            CHECK( obj->invoke( "foo", c1 ).check( "", env ) );

            InvokeContext c2( "5, 2", env );
            CHECK( obj->invoke( "bar", c2 ).check( "5", env ) );

            InvokeContext c3( "\"hello\"", env );
            CHECK( obj->invoke( "goo", c3 ).check( "-0.1", env ) );

            InvokeContext c4( "", env );
            CHECK( obj->invoke( "getValue", c4 ).check( "110", env ) );

            f.mValue = 1;
            InvokeContext c5( "", env );
            CHECK( obj->invoke( "getValue", c5 ).check( "1", env ) );
        }
    };
}

DECLARE_TEST( TestObjectTest );

#endif
