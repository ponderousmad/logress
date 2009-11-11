#ifndef METABASE_SAME_H__INCLUDED
#define METABASE_SAME_H__INCLUDED
/* ---------------------------------------------------------------
 * Copyright (c) Adrian Smith.
 * Licensed under the MIT license. See license.txt at project root.
 * --------------------------------------------------------------- */

#include "MetaBase/MetaBaseBoolType.h"

namespace MetaBase {
    template <typename T, typename U>
    struct Same : public FalseType {};

    template <typename T>
    struct Same<T,T> : public TrueType {};
}

#endif // METABASE_SAME_H__INCLUDED
