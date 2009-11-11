#ifndef TEST_ARGUMENTNUMBER_H__INCLUDED
#define TEST_ARGUMENTNUMBER_H__INCLUDED
/* ---------------------------------------------------------------
 * Copyright (c) Adrian Smith.
 * Licensed under the MIT license. See license.txt at project root.
 * --------------------------------------------------------------- */

namespace Test
{
    template < typename Types, template <typename> class StoreTraits >
    class ArgumentList;


    template <int N>
    struct ArgumentNumber
    {
        enum {
            Value = N
        };
    };
}

#endif // TEST_ARGUMENTNUMBER_H__INCLUDED
