#ifndef TESTLOGFORMAT_H__INCLUDED
#define TESTLOGFORMAT_H__INCLUDED

/* ---------------------------------------------------------------
 * Copyright (c) Adrian Smith.
 * Licensed under the MIT license. See license.txt at project root.
 * --------------------------------------------------------------- */

namespace Test
{
    struct LogFormat
    {
        static const char kConstructorSymbol;
        static const char kMethodCallSymbol;
        static const char kFunctionCallSymbol;
        static const char kResultSymbol;
        static const char kObjectIDSymbol;
        static const char kMethodIndexSymbol;
        static const char kOpenArgumentListSymbol;
        static const char kCloseArgumentListSymbol;
    };
}

#endif /* TESTLOGFORMAT_H__INCLUDED */
