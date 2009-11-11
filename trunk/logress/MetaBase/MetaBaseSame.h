#ifndef METABASE_SAME_H__INCLUDED
#define METABASE_SAME_H__INCLUDED
/* ---------------------------------------------------------------
 * Copyright (c) Adrian Smith.
 * Licensed under the MIT license. See license.txt at project root.
 * --------------------------------------------------------------- */

#include "MetaBase/MetaBaseBoolType.h"

/*
 * Given two types, determine if the types match exactly.
 *
 * For example, the following has the value false:
 * MetaBase::Same<int&, int>::Value
 */

namespace MetaBase {
    template <typename T, typename U>
    struct Same : public FalseType {};

    template <typename T>
    struct Same<T,T> : public TrueType {};
}

#endif // METABASE_SAME_H__INCLUDED
