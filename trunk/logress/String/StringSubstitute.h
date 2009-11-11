#ifndef STRING_SUBSTITUTE_H__INCLUDED
#define STRING_SUBSTITUTE_H__INCLUDED
/* ---------------------------------------------------------------
 * Copyright (c) Adrian Smith.
 * Licensed under the MIT license. See license.txt at project root.
 * --------------------------------------------------------------- */

#include <string>

namespace String
{
    // Produce a new string with all occurences of the string 'replace' replaced by the string 'with'.
    std::string substitute( const std::string& replace, const std::string& with, const std::string& inString );
}

#endif // STRING_SUBSTITUTE_H__INCLUDED
