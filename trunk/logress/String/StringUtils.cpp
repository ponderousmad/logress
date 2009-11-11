/* ---------------------------------------------------------------
 * Copyright (c) Adrian Smith.
 * Licensed under the MIT license. See license.txt at project root.
 * --------------------------------------------------------------- */
#include "Base/Top.h"

#include "String/StringUtils.h"
#include "String/StringCasts.h"
#include "Base/BaseAssert.h"
#include "Base/BaseRandom.h"

#include <cctype>

namespace {
    char gStringMask = 0;
}

using String::StringVector;

// Adds the items of the <delimiter> delimited list stored in <list> to the end of <vectorList>.
void String::splitDelimitedList( const std::string& list, const std::string& delimiter, std::vector<std::string>& vectorList )
{
    size_t startPos = 0, delimiterPos;

    while ( startPos < list.length() ) {
        delimiterPos = list.find( delimiter, startPos );
        if ( delimiterPos == std::string::npos )
            delimiterPos = list.length();
        vectorList.push_back( list.substr( startPos, delimiterPos-startPos ) );
        startPos = delimiterPos + delimiter.size();
    }
}

// Returns a vector of strings representing the items of the <delimiter> delimited list stored in <list>.
StringVector String::splitDelimitedList( const std::string& list, const std::string& delimiter )
{
    StringVector vectorList;
    splitDelimitedList( list, delimiter, vectorList );
    return vectorList;
}

// Returns the offset of the first comma that is not escaped, that is, the first comma preceeded by an even
// number of slashes
std::string::size_type String::findFirstUnescapedComma( const std::string& searchStr, std::string::size_type offset )
{
    if ( offset >= searchStr.size() ) {
        offset = std::string::npos;
    } else {
        while ( offset != std::string::npos && searchStr[offset] != ',' ) {
            offset = searchStr.find(',', offset);

            if ( offset != std::string::npos ) {
                // Count the slashes preceeding the comma
                int slashCount = 0;
                std::string::size_type tmpOffset = offset-1;
                while ( tmpOffset >= 0 && searchStr[tmpOffset] == '\\' ) {
                    --tmpOffset;
                    ++slashCount;
                }

                // Escaped commas will be preceeded by an odd number of slashes
                if ( slashCount % 2 ) {
                    // It's escaped so skip it and search again
                    ++offset;
                }
            }
        }
    }
    return offset;
}

// Returns a vector of strings representing the (possibly) escaped items of the comma-delimited list stored
// in <list>.  Each item that begins with a quote will be unescaped.
StringVector String::splitEscapedCommaList( const std::string& list )
{
    StringVector vectorList;

    std::string::size_type startPos = 0;
    std::string::size_type delimPos = std::string::npos-1;

    while ( startPos < list.size() ) {

        delimPos = findFirstUnescapedComma( list, startPos );
        if ( delimPos == std::string::npos ) {
            delimPos = list.size();
        }

        std::string nextItem = list.substr( startPos, delimPos - startPos );

        if ( list[ startPos ] == '\"' ) {
            nextItem = unEscape( nextItem.c_str() );
        }

        vectorList.push_back( nextItem );

        startPos = delimPos + 1;
    }

    if ( delimPos == list.size() - 1 ) {
        vectorList.push_back( "" );
    }

    return vectorList;
}

std::string String::trim( const std::string& str, const char* trimChars )
{
    std::string::size_type start = str.find_first_not_of( trimChars );
    if( start == std::string::npos )
    {
        return "";
    }

    std::string::size_type end = str.find_last_not_of( trimChars );
    ASSERT( end != std::string::npos );
    ++end;
    ASSERT( start <= end )
    return str.substr( start, end - start );
}

// Inserts a slash before parentheses and each comma, quote, slash.  Each carriage return, line feed, and tab
// are translated to \r \n and \t respectively.  Finally, the entire string is enclosed in quotes.
std::string String::escape( const char* toEscape )
{
    std::string escaped( String::str( toEscape ) );

    std::string::size_type offset = 0;
    while( offset < escaped.length() ) {
        offset = escaped.find_first_of( "\\,()\"\t\r\n", offset );
        if( offset != std::string::npos ) {
            escaped.insert( offset, "\\" );
            switch (escaped[offset+1]) {
                case '\t': escaped[offset+1] = 't'; break;
                case '\r': escaped[offset+1] = 'r'; break;
                case '\n': escaped[offset+1] = 'n'; break;
            }
            offset += 2;
        }
    }

    return '\"' + escaped + '\"';

}

// Inverse of escape().  That is, unEscape( escape( originalString ) ) == originalString.  Calling unEscape on
// a string that is not enclosed in quotes causes an exception.
std::string String::unEscape( const char* toUnEscape )
{
    std::string unEscaped( String::str( toUnEscape ) );
    int x = 0;
    if ( unEscaped.size() >= 2 ) {
        x = 1;
    }
    if ( unEscaped[ 0 ] == '\"' ) {
        x = 2;
    }
    if ( unEscaped[ unEscaped.size() - 1 ] == '\"' ) {
        x = 3;
    }
    ASSERT_RTN( unEscaped.size() >= 2 && unEscaped[ 0 ] == '\"' && unEscaped[ unEscaped.length() - 1 ] == '\"',
                unEscaped, STR( "unEscape( " + unEscaped + " ): missing surrounding quotes." ) );

    unEscaped = unEscaped.substr( 1, unEscaped.size() - 2 );

    std::string::size_type offset = 0;
    while( offset < unEscaped.length() ) {
        offset = unEscaped.find( "\\", offset );
        if( offset != std::string::npos ) {
            unEscaped.erase( offset, 1 );
            switch (unEscaped[offset]) {
                case 't': unEscaped[offset] = '\t'; break;
                case 'r': unEscaped[offset] = '\r'; break;
                case 'n': unEscaped[offset] = '\n'; break;
            }
            ++offset;
        }
    }
    return unEscaped;
}

// Returns true if str1 == str2 in a case-insensitive comparison
bool String::compareStringsI( const std::string& str1, const std::string& str2 )
{
    std::string str1Cpy( str1 );
    std::string str2Cpy( str2 );
    std::transform( str1Cpy.begin(), str1Cpy.end(), str1Cpy.begin(), ::tolower );
    std::transform( str2Cpy.begin(), str2Cpy.end(), str2Cpy.begin(), ::tolower );
    return ( str1Cpy == str2Cpy );
}

char String::randomizeStringMask()
{
    char newMask;
    do {
        newMask = static_cast<char>( Base::random() % 256 );
    } while( newMask == 0 || newMask == 32 );
    setStringMask( newMask );
    return newMask;
}

void String::clearStringMask()
{
    setStringMask( 0 );
}

void String::setStringMask( char mask )
{
    gStringMask = mask;
}

// Reads a string (with length) from a file
std::string String::readStr( std::istream& inF )
{
    size_t strLength;
    std::string result;

    inF.read( (char *)&strLength, sizeof(strLength) );
    if ( strLength == 0 ) {
        return "";
    }
    result.resize( strLength );
    inF.read( &(result[0]), (std::streamsize)strLength );

    if( gStringMask ) {
        while (strLength > 0) {
            result[--strLength] ^= gStringMask;
        }
    }

    return result;
}

// Writes a string (with length) to a file
void String::writeStr( std::string inStr, std::ostream& outF )
{
    size_t strLength = inStr.size();

    if( gStringMask )
    {
        for( size_t i = 0; i < strLength; ++i )
        {
            inStr[i] ^= gStringMask;
        }
    }

    outF.write( (char *)&strLength, sizeof( strLength ) );
    if( strLength > 0 )
    {
        outF << inStr;
    }
}

std::string String::toLower( const std::string& inStr )
{
    std::string lower( inStr );
    for( size_t i = 0; i < lower.length(); ++i )
    {
        lower[i] = static_cast<std::string::value_type>( tolower( lower[i] ) );
    }
    return lower;
}

#ifdef BUILD_TESTS

#include "UnitTest/UnitTestFramework.h"
#include <iostream>

namespace {
    class StringUtilsTest : public UnitTest::Framework
    {
    public:
        void run()
        {
            RUN( trimTest );
            RUN( escapeTest );
            RUN( unEscapeTest );
            RUN( splitEscapedCommaListTest );
            RUN( splitDelimitedListTest );
            RUN( toLowerTest );
        }

        void trimTest()
        {
            CHECK( String::trim( "" ) == "" );
            CHECK( String::trim( " " ) == "" );
            CHECK( String::trim( "a" ) == "a" );
            CHECK( String::trim( " a" ) == "a" );
            CHECK( String::trim( "a\t" ) == "a" );
            CHECK( String::trim( " a\n" ) == "a" );
            CHECK( String::trim( "\ra a    " ) == "a a" );

            CHECK( String::trim( "bbbbabab", "b" ) == "aba" );
        }

        void escapeTest()
        {
            CHECK( String::escape( 0 ) == "\"\"" );
            CHECK( String::escape( "" ) == "\"\"" );
            CHECK( String::escape( "a" ) == "\"a\"" );

            const char * toParse = "test\t\"one\", test\\two,\r\ntest three";
            const char * expected = "\"test\\t\\\"one\\\"\\, test\\\\two\\,\\r\\ntest three\"";
            std::string parsedStr( String::escape( toParse ) );
            CHECK( !strcmp( parsedStr.c_str(), expected ) );
        }

        void unEscapeTest()
        {
            const char * toParse = "\"test\\t\\\"one\\\"\\, test\\\\two\\,\\r\\ntest three\"";
            const char * expected = "test\t\"one\", test\\two,\r\ntest three";
            std::string parsedStr( String::unEscape( toParse ) );
            CHECK( !strcmp( parsedStr.c_str(), expected ) );
        }

        void splitEscapedCommaListTest()
        {
            std::string toParse( "stringToParse,\" With \\\"Commas\\\"\\,In\\,It\",next test,\"Hey there!\",Quotes\"in the\"middle" );
            StringVector result( String::splitEscapedCommaList( toParse ) );
            CHECK( result.size() == 5 );
            CHECK( result[0] == "stringToParse" );
            CHECK( result[1] == " With \"Commas\",In,It" );
            CHECK( result[2] == "next test" );
            CHECK( result[3] == "Hey there!" );
            CHECK( result[4] == "Quotes\"in the\"middle" );
        }

        void splitDelimitedListTest()
        {
            std::string toParse( "stringToParse\r\n With \"Commas\",In,It\r\nnext test\r\n\"Hey there!\"\r\nQuotes\"in the\"middle" );
            StringVector result( String::splitDelimitedList( toParse, "\r\n" ) );
            CHECK( result.size() == 5 );
            CHECK( result[0] == "stringToParse" );
            CHECK( result[1] == " With \"Commas\",In,It" );
            CHECK( result[2] == "next test" );
            CHECK( result[3] == "\"Hey there!\"" );
            CHECK( result[4] == "Quotes\"in the\"middle" );
        }

        void toLowerTest()
        {
            std::string toConvert( "This is Some text in MIXed CaSe." );
            CHECK( String::toLower( toConvert ) == "this is some text in mixed case." );
        }
    };
}

DECLARE_TEST( StringUtilsTest );

#endif
