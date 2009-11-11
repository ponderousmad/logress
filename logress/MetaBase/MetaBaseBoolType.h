#ifndef METABASE_BOOLTYPE_H__INCLUDED
#define METABASE_BOOLTYPE_H__INCLUDED

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
