/* ---------------------------------------------------------------
 * Copyright (c) Adrian Smith.
 * Licensed under the MIT license. See license.txt at project root.
 * --------------------------------------------------------------- */
#include "Base/Top.h"

#include "Test/TestObjectFactory.h"

#ifdef BUILD_TESTS

#include "UnitTest/UnitTestFramework.h"
#include "Test/TestEnvironment.h"

namespace
{
    using Test::Environment;
    using Test::InvokeContext;
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
            mValue *= 2;
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

    class TestObjectFactoryTest : public UnitTest::Framework
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

            Test::Object<Foo>::VTableH vTable( new Test::Object<Foo>::VTable() );
            vTable->add( "foo", buildMethod( &Foo::foo ) );
            vTable->add( "bar", buildMethod( &Foo::bar ) );
            vTable->add( "goo", buildMethod( &Foo::goo ) );
            vTable->add( "getValue", buildMethod( &Foo::getValue ) );

            Test::ConstObjectFactoryH factory( Test::ObjectFactory<Foo>::buildFactory< TYPELIST_1( int ) >( vTable ) );
            InvokeContext c1( "1", env );
            Test::IObjectFactory::Result result( factory->construct( c1 ) );
            CHECK_ASSERT( result.first == Test::InvokeResult::kSuccess );

            Test::ObjectH obj( result.second );

            InvokeContext c2( "", env );
            CHECK( obj->invoke( "foo", c2 ).check( "", env ) );

            InvokeContext c3( "5, 2", env );
            CHECK( obj->invoke( "bar", c3 ).check( "5", env ) );

            InvokeContext c4( "\"hello\"", env );
            CHECK( obj->invoke( "goo", c4 ).check( "-0.1", env ) );

            InvokeContext c5( "", env );
            CHECK( obj->invoke( "getValue", c5 ).check( "2", env ) );
        }
    };
}

DECLARE_TEST( TestObjectFactoryTest );

#endif
