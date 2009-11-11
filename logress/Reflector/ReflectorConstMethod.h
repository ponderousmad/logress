#ifndef REFLECTOR_CONSTMETHOD_H__INCLUDED
#define REFLECTOR_CONSTMETHOD_H__INCLUDED

#include "MetaBase/MetaBaseTypeList.h"

namespace Reflector {
    template <typename FunctionType>
    struct Function;

    template <typename R, typename C>
    struct Function< R (C::*)() const >
    {
        typedef C ClassType;
        typedef R ReturnType;
        typedef MetaBase::EmptyTypeList ArgumentTypes;
        typedef MetaBase::TrueType IsConst;
    };

    template <typename R, typename C, typename A1 >
    struct Function< R (C::*)( A1 ) const >
    {
        typedef C ClassType;
        typedef R ReturnType;
        typedef TYPELIST_1( A1 ) ArgumentTypes;
        typedef MetaBase::TrueType IsConst;
    };

    template <typename R, typename C, typename A1, typename A2 >
    struct Function< R (C::*)( A1, A2 ) const >
    {
        typedef C ClassType;
        typedef R ReturnType;
        typedef TYPELIST_2( A1, A2 ) ArgumentTypes;
        typedef MetaBase::TrueType IsConst;
    };

    template <typename R, typename C, typename A1, typename A2, typename A3 >
    struct Function< R (C::*)( A1, A2, A3 ) const >
    {
        typedef C ClassType;
        typedef R ReturnType;
        typedef TYPELIST_3( A1, A2, A3 ) ArgumentTypes;
        typedef MetaBase::TrueType IsConst;
    };

    template <typename R, typename C, typename A1, typename A2, typename A3, typename A4 >
    struct Function< R (C::*)( A1, A2, A3, A4 ) const >
    {
        typedef C ClassType;
        typedef R ReturnType;
        typedef TYPELIST_4( A1, A2, A3, A4 ) ArgumentTypes;
        typedef MetaBase::TrueType IsConst;
    };

    template <typename R, typename C, typename A1, typename A2, typename A3, typename A4, typename A5 >
    struct Function< R (C::*)( A1, A2, A3, A4, A5 ) const >
    {
        typedef C ClassType;
        typedef R ReturnType;
        typedef TYPELIST_5( A1, A2, A3, A4, A5 ) ArgumentTypes;
        typedef MetaBase::TrueType IsConst;
    };

    template <typename R, typename C, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6 >
    struct Function< R (C::*)( A1, A2, A3, A4, A5, A6 ) const >
    {
        typedef C ClassType;
        typedef R ReturnType;
        typedef TYPELIST_6( A1, A2, A3, A4, A5, A6 ) ArgumentTypes;
        typedef MetaBase::TrueType IsConst;
    };

    template <typename R, typename C, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7 >
    struct Function< R (C::*)( A1, A2, A3, A4, A5, A6, A7 ) const >
    {
        typedef C ClassType;
        typedef R ReturnType;
        typedef TYPELIST_7( A1, A2, A3, A4, A5, A6, A7 ) ArgumentTypes;
        typedef MetaBase::TrueType IsConst;
    };

    template <typename R, typename C, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8 >
    struct Function< R (C::*)( A1, A2, A3, A4, A5, A6, A7, A8 ) const >
    {
        typedef C ClassType;
        typedef R ReturnType;
        typedef TYPELIST_8( A1, A2, A3, A4, A5, A6, A7, A8 ) ArgumentTypes;
        typedef MetaBase::TrueType IsConst;
    };

    template <typename R, typename C, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9 >
    struct Function< R (C::*)( A1, A2, A3, A4, A5, A6, A7, A8, A9 ) const >
    {
        typedef C ClassType;
        typedef R ReturnType;
        typedef TYPELIST_9( A1, A2, A3, A4, A5, A6, A7, A8, A9 ) ArgumentTypes;
        typedef MetaBase::TrueType IsConst;
    };

    template <typename R, typename C, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10 >
    struct Function< R (C::*)( A1, A2, A3, A4, A5, A6, A7, A8, A9, A10 ) const >
    {
        typedef C ClassType;
        typedef R ReturnType;
        typedef TYPELIST_10( A1, A2, A3, A4, A5, A6, A7, A8, A9, A10 ) ArgumentTypes;
        typedef MetaBase::TrueType IsConst;
    };

    template <typename R, typename C, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11 >
    struct Function< R (C::*)( A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11 ) const >
    {
        typedef C ClassType;
        typedef R ReturnType;
        typedef TYPELIST_11( A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11 ) ArgumentTypes;
        typedef MetaBase::TrueType IsConst;
    };

    template <typename R, typename C, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12 >
    struct Function< R (C::*)( A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12 ) const >
    {
        typedef C ClassType;
        typedef R ReturnType;
        typedef TYPELIST_12( A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12 ) ArgumentTypes;
        typedef MetaBase::TrueType IsConst;
    };

    template <typename R, typename C, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12, typename A13 >
    struct Function< R (C::*)( A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13 ) const >
    {
        typedef C ClassType;
        typedef R ReturnType;
        typedef TYPELIST_13( A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13 ) ArgumentTypes;
        typedef MetaBase::TrueType IsConst;
    };

    template <typename R, typename C, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12, typename A13, typename A14 >
    struct Function< R (C::*)( A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14 ) const >
    {
        typedef C ClassType;
        typedef R ReturnType;
        typedef TYPELIST_14( A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14 ) ArgumentTypes;
        typedef MetaBase::TrueType IsConst;
    };

    template <typename R, typename C, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12, typename A13, typename A14, typename A15 >
    struct Function< R (C::*)( A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, A15 ) const >
    {
        typedef C ClassType;
        typedef R ReturnType;
        typedef TYPELIST_15( A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, A15 ) ArgumentTypes;
        typedef MetaBase::TrueType IsConst;
    };
}

#endif // REFLECTOR_CONSTMETHOD_H__INCLUDED
