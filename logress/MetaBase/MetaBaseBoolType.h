#ifndef METABASE_BOOLTYPE_H__INCLUDED
#define METABASE_BOOLTYPE_H__INCLUDED
/* ---------------------------------------------------------------
 * Copyright (c) Adrian Smith.
 * Licensed under the MIT license. See license.txt at project root.
 * --------------------------------------------------------------- */

namespace MetaBase {
    struct TrueType {
        enum { Value = true };
        typedef TrueType Type;
    };

    struct FalseType {
        enum { Value = false};
        typedef FalseType Type;
    };

    template <typename T>
    struct Negate : public FalseType {};

    template <>
    struct Negate<FalseType> : public TrueType {};
}

#endif //METABASE_BOOLTYPE_H__INCLUDED
