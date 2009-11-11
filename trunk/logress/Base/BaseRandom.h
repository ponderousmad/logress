#ifndef BASE_RANDOM_H__INCLUDED
#define BASE_RANDOM_H__INCLUDED
/* ---------------------------------------------------------------
 * Copyright (c) Adrian Smith.
 * Licensed under the MIT license. See license.txt at project root.
 * --------------------------------------------------------------- */

namespace Base
{
    // Produce an integer at random.
    // Mostly this is just to allow the random number source to
    // be changed at a later date without disrupting clients.
    int random();
}

#endif // BASE_RANDOM_H__INCLUDED
