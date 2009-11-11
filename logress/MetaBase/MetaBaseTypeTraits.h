#ifndef METABASE_TYPETRAITS_H__INCLUDED
#define METABASE_TYPETRAITS_H__INCLUDED

#include "MetaBase/MetaBaseBoolType.h"
#include "MetaBase/MetaBaseNullType.h"

namespace MetaBase {
    template <typename T>
    struct IsConst : public FalseType {};

    template <typename T>
    struct IsConst<const T> : public TrueType {};

    template <typename T>
    struct IsConst<const T*> : public FalseType {};

    template <typename T>
    struct IsConst<T* const> : public TrueType {};

    template <typename T>
    struct IsConst<const T&> : public TrueType {};

    template <typename T>
    struct IsReference : public FalseType {};

    template <typename T>
    struct IsReference<T&> : public TrueType {};

    template <typename T>
    struct IsNull : public FalseType {};

    template <>
    struct IsNull<NullType> : public TrueType {};

    template <>
    struct IsNull<const NullType> : public TrueType {};
}

#endif // METABASE_TYPETRAITS_H__INCLUDED
