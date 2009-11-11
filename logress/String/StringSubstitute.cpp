/* ---------------------------------------------------------------
 * Copyright (c) Adrian Smith.
 * Licensed under the MIT license. See license.txt at project root.
 * --------------------------------------------------------------- */
#include "Base/Top.h"

#include "String/StringSubstitute.h"

std::string String::substitute( const std::string& replace, const std::string& with, const std::string& inString )
{
    if( replace.empty() || inString.find( replace ) == std::string::npos )
    {
        return inString;
    }
    std::string result;
    std::string::size_type pos = 0;

    do
    {
        std::string::size_type next = inString.find( replace, pos );
        if( next < std::string::npos )
        {
            result += inString.substr( pos, next - pos );
            result += with;
            next += replace.size();
        }
        else
        {
            result += inString.substr( pos );
        }
        pos = next;
    } while( pos < std::string::npos );
    return result;
}

#ifdef BUILD_TESTS

#include "UnitTest/UnitTestFramework.h"

namespace
{
    using String::substitute;

    class StringSubstituteTest : public UnitTest::Framework
    {
    public:
        void run()
        {
            RUN( basicTest );
            RUN( atStartTest );
            RUN( atEndTest );
            RUN( wholeStringTest );
            RUN( emptyTest );
            RUN( multiTest );
        }

        void basicTest()
        {
            CHECK( substitute( "foo", "bar", "there is a foo in this string" ) == "there is a bar in this string" );
        }

        void atStartTest()
        {
            CHECK( substitute( "foo", "bar", "foo is in this string" ) ==  "bar is in this string" );
        }

        void atEndTest()
        {
            CHECK( substitute( "foo", "bar", "this string ends with foo" ) == "this string ends with bar" );
        }

        void wholeStringTest()
        {
            CHECK( substitute( "foo", "bar", "foo" ) ==  "bar" );
        }

        void emptyTest()
        {
            CHECK( substitute( "", "foo", "bar" ) ==  "bar" );
            CHECK( substitute( "foo", "", "bar" ) ==  "bar" );
            CHECK( substitute( "foo", "", "a foo." ) ==  "a ." );
        }

        void multiTest()
        {
            CHECK( substitute( "foo", "bar", "foo is at the start, the foo and the foo" ) == "bar is at the start, the bar and the bar" );
        }
    };
}

DECLARE_TEST( StringSubstituteTest );

#endif

