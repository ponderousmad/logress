#include "Base/Top.h"

#include "Test/TestArgumentList.h"

#ifdef BUILD_TESTS

#include "UnitTest/UnitTestFramework.h"
#include "Test/TestArgumentTraits.h"
#include "Test/TestArgumentNumber.h"
#include "MetaBase/MetaBaseTypeList.h"

#include <string>

using Test::ArgumentList;
using Test::ArgumentNumber;
using Test::ArgumentTraitsBaseType;

namespace
{
    class TestArgumentListTest : public UnitTest::Framework
    {
    public:
        void run()
        {
            RUN( oneArgTest );
            RUN( twoArgTest );
            RUN( threeArgTest );
        }

        void oneArgTest()
        {
            ArgumentList< TYPELIST_1( std::string ), ArgumentTraitsBaseType > list;
            list.getItem( ArgumentNumber<0>() ) = "Hello";
            const ArgumentList< TYPELIST_1( std::string ), ArgumentTraitsBaseType >& constList( list );
            CHECK( constList.getItem( ArgumentNumber<0>() ) == "Hello" );
        }

        void twoArgTest()
        {
            ArgumentList< TYPELIST_2( int, std::string ), ArgumentTraitsBaseType > list;
            list.getItem( ArgumentNumber<0>() ) = 42;
            list.getItem( ArgumentNumber<1>() ) = "Hello";
            const ArgumentList< TYPELIST_2( int, std::string ), ArgumentTraitsBaseType >& constList( list );
            CHECK( constList.getItem( ArgumentNumber<0>() ) == 42 );
            CHECK( constList.getItem( ArgumentNumber<1>() ) == "Hello" );
        }

        void threeArgTest()
        {
            ArgumentList< TYPELIST_3( int, double, std::string ), ArgumentTraitsBaseType > list;
            list.getItem( ArgumentNumber<0>() ) = 42;
            list.getItem( ArgumentNumber<1>() ) = .5;
            list.getItem( ArgumentNumber<2>() ) = "Hello";
            const ArgumentList< TYPELIST_3( int, double, std::string ), ArgumentTraitsBaseType >& constList( list );
            CHECK( constList.getItem( ArgumentNumber<0>() ) == 42 );
            CHECK( constList.getItem( ArgumentNumber<1>() ) == .5 );
            CHECK( constList.getItem( ArgumentNumber<2>() ) == "Hello" );
        }
    };
}

DECLARE_TEST( TestArgumentListTest );

#endif
