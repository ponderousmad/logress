/* ---------------------------------------------------------------
 * Copyright (c) Adrian Smith.
 * Licensed under the MIT license. See license.txt at project root.
 * --------------------------------------------------------------- */
#include "Base/Top.h"

#include "String/StringCasts.h"
#include <sstream>
#include <iomanip>

namespace
{
    const int kBufferSize = 256;
    const int kUnlikelyInt = -152435;
    const float kUnlikelyFloat = -987.666;
    const double kUnlikelyDouble = -787.245;
}

// String <-> Number Conversion Functions
int String::strToInt( const std::string& inStr )
{
    int outVal = kUnlikelyInt;
    std::istringstream stream(inStr);
    stream >> outVal;
    return outVal;
}

float String::strToFloat( const std::string& inStr )
{
    float outVal = kUnlikelyDouble;
    std::istringstream stream(inStr);
    stream >> outVal;
    return outVal;
}

double String::strToDouble( const std::string& inStr )
{
    double outVal = kUnlikelyDouble;
    std::istringstream stream(inStr);
    stream >> outVal;
    return outVal;
}

std::string String::make( int value )
{
    std::ostringstream stream;
    stream << value;
    return stream.str();
}

std::string String::make( unsigned int value )
{
    std::ostringstream stream;
    stream << value;
    return stream.str();
}


std::string String::make( double value, bool fixed, int precision )
{
    std::ostringstream stream;
    stream << (fixed ? std::fixed : std::scientific) << std::setprecision(precision) << value;
    return stream.str();
}

#ifdef BUILD_TESTS

#include "UnitTest/UnitTestFramework.h"

namespace {
    class StringCastsTest : public UnitTest::Framework
    {
    public:
        void run()
        {
            RUN( strToIntTest );
            RUN( strToDoubleTest );
            RUN( makeIntTest );
            RUN( makeDoubleTest );
        }

        void strToIntTest()
        {
            CHECK( String::strToInt( "1" ) == 1 );
            CHECK( String::strToInt( "2 " ) == 2 );
            CHECK( String::strToInt( " -1" ) == -1 );
            CHECK( String::strToInt( " 100    " ) == 100 );
        }

        void strToDoubleTest()
        {
            CHECK( String::strToDouble( "1" ) == 1. );
            CHECK( String::strToDouble( "2 " ) == 2. );
            CHECK( String::strToDouble( " -1" ) == -1. );
            CHECK( String::strToDouble( " 100    " ) == 100. );
        }

        void makeIntTest()
        {
            CHECK( String::make( 802 ) == "802" );
        }

        void makeDoubleTest()
        {
            CHECK( String::make( 12.0 ) == "12.0000" );
            // CHECK( String::make( 12.0, "%.1f" ) == "12.0" );
        }

    };
}

DECLARE_TEST( StringCastsTest );

#endif

