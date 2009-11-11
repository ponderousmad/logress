#ifndef METABASE_BOOLTYPE_H__INCLUDED
#define METABASE_BOOLTYPE_H__INCLUDED
/* ---------------------------------------------------------------
 * Copyright (c) Adrian Smith.
 * Licensed under the MIT license. See license.txt at project root.
 * --------------------------------------------------------------- */

/*
 * Define true and false to simplify/clarify the implementation of
 * certain metaprograms.
 */
namespace MetaBase {
    struct TrueType {
        enum { Value = true };
        typedef TrueType Type;
    };

    struct FalseType {
        enum { Value = false};
        typedef FalseType Type;
    };

    // This template and its specialization will logically negate the
    // 'value' of its template argument.
    // For example, the following would have the value false:
    // MetaBase::Negate< MetaBase::TrueType >::Value;
    // And this would have the type 'TrueType':
    // MetaBase::Negate< MetaBase::FalseType >::Type;

    template <typename T>
    struct Negate : public FalseType {};

    template <>
    struct Negate<FalseType> : public TrueType {};
}

#endif //METABASE_BOOLTYPE_H__INCLUDED
