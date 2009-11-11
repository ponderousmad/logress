#ifndef STRING_CASTS_H__INCLUDED
#define STRING_CASTS_H__INCLUDED
/* ---------------------------------------------------------------
 * Copyright (c) Adrian Smith.
 * Licensed under the MIT license. See license.txt at project root.
 * --------------------------------------------------------------- */

#include <string>

/*
 * Define a template friendly set of conversions to and from std::string
 */

namespace String {
    // String <-> Number Conversion Functions
    int strToInt( const std::string& inStr );
    float strToFloat( const std::string& inStr );
    double strToDouble( const std::string& inStr );

    template <typename T>
    inline T as( const std::string& s )
    {
        return s;
    }

    template <>
    inline int as<int>( const std::string& s )
    {
        return strToInt( s );
    }

    template <>
    inline float as<float>( const std::string& s)
    {
        return strToFloat( s );
    }

    template <>
    inline double as<double>( const std::string& s )
    {
        return strToDouble( s );
    }

    inline std::string str( const char* value )
    {
        return std::string( value ? value : "" );
    }
    std::string make( int value );
    std::string make( unsigned int value );
    std::string make( double value, bool fixed = true, int precision = 4 );
}

#endif // STRING_CASTS_H__INCLUDED
