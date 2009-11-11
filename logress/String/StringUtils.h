#ifndef STRING_UTILS_H__INCLUDED
#define STRING_UTILS_H__INCLUDED

#include <iostream>
#include <string>
#include <vector>

#define STR( string ) ( string ).c_str()

namespace String {
    typedef std::vector<std::string> StringVector;

    // Adds the items of the <delimiter> delimited list stored in <list> to the end of <vectorList>.
    void splitDelimitedList( const std::string& list, const std::string& delimiter, StringVector& vectorList );

    // Returns a vector of strings representing the items of the <delimiter> delimited list stored in <list>.
    StringVector splitDelimitedList( const std::string& list, const std::string& delimiter );

    // Returns the offset of the first comma that is not escaped, that is, the first comma preceeded by an even
    // number of slashes
    std::string::size_type findFirstUnescapedComma( const std::string& searchStr, std::string::size_type offset );

    // Returns a vector of strings representing the (possibly) escaped items of the comma-delimited list stored
    // in <list>.  Each item that begins with a quote will be unescaped.
    StringVector splitEscapedCommaList( const std::string& list );

    // Remove whitespace from beginning and ends of the string.
    std::string trim( const std::string& str, const char* trimChars = " \t\n\r" );

    // Inserts a slash before parentheses and each comma, quote, slash.  Each carriage return, line feed, and tab
    // are translated to \r \n and \t respectively.  Finally, the entire string is enclosed in quotes.
    std::string escape( const char* toEscape );
    inline std::string escape( const std::string& toEscape )
    {
        return escape( toEscape.c_str() );
    }

    // Inverse of escape().  That is, unEscape( escape( originalString ) ) == originalString.  Calling unEscape on
    // a string that is not enclosed in quotes causes an exception.
    std::string unEscape( const char* toUnEscape );
    inline std::string unEscape( const std::string& toUnEscape )
    {
        return unEscape( toUnEscape.c_str() );
    }

    // Returns true if str1 == str2 in a case-insensitive comparison
    bool compareStringsI( const std::string& str1, const std::string& str2 );

    char randomizeStringMask();
    void clearStringMask();
    void setStringMask( char mask );

    // Reads string data (with length) from a stream
    std::string readStr( std::istream& inF );

    // Writes string data (with length) to a stream
    void writeStr( std::string inStr, std::ostream& outF );

    std::string toLower( const std::string& inStr );
}

#endif // STRING_UTILS_H__INCLUDED
