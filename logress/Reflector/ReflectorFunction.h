#ifndef REFLECTOR_FUNCTION_H__INCLUDED
#define REFLECTOR_FUNCTION_H__INCLUDED
/* ---------------------------------------------------------------
 * Copyright (c) Adrian Smith.
 * Licensed under the MIT license. See license.txt at project root.
 * --------------------------------------------------------------- */

#include "MetaBase/MetaBaseTypeList.h"
#include "MetaBase/MetaBaseBoolType.h"

/*
 * This template and its specializations are designed to provide compile time
 * introspection into function types. Note that this only supports functions of
 * up to 15 arguments.
 *
 * For example, with the following:
 * typedef int Func*(double x, double y);
 *
 * Reflector::Function<Func> would have the following members:
 * ClassType -> MetaBase::NullType
 * ReturnType -> int
 * ArgumentTypes -> TYPELIST_2( double, double )
 * IsConst -> MetaBase::FalseType
 *
 * The files ReflectorMethod.h and ReflectorConstMethod add additional
 * specializations for use with member functions and const member functions.
 */

namespace Reflector
{
    template <typename FunctionType>
    struct Function;

    template <typename R>
    struct Function< R (*)() >
    {
        typedef MetaBase::NullType ClassType;
        typedef R ReturnType;
        typedef MetaBase::EmptyTypeList ArgumentTypes;
        typedef MetaBase::FalseType IsConst;
    };

    template <typename R, typename A1 >
    struct Function< R (*)( A1 ) >
    {
        typedef MetaBase::NullType ClassType;
        typedef R ReturnType;
        typedef TYPELIST_1( A1 ) ArgumentTypes;
        typedef MetaBase::FalseType IsConst;
    };

    template <typename R, typename A1, typename A2 >
    struct Function< R (*)( A1, A2 ) >
    {
        typedef MetaBase::NullType ClassType;
        typedef R ReturnType;
        typedef TYPELIST_2( A1, A2 ) ArgumentTypes;
        typedef MetaBase::FalseType IsConst;
    };

    template <typename R, typename A1, typename A2, typename A3 >
    struct Function< R (*)( A1, A2, A3 ) >
    {
        typedef MetaBase::NullType ClassType;
        typedef R ReturnType;
        typedef TYPELIST_3( A1, A2, A3 ) ArgumentTypes;
        typedef MetaBase::FalseType IsConst;
    };

    template <typename R, typename A1, typename A2, typename A3, typename A4 >
    struct Function< R (*)( A1, A2, A3, A4 ) >
    {
        typedef MetaBase::NullType ClassType;
        typedef R ReturnType;
        typedef TYPELIST_4( A1, A2, A3, A4 ) ArgumentTypes;
        typedef MetaBase::FalseType IsConst;
    };

    template <typename R, typename A1, typename A2, typename A3, typename A4, typename A5 >
    struct Function< R (*)( A1, A2, A3, A4, A5 ) >
    {
        typedef MetaBase::NullType ClassType;
        typedef R ReturnType;
        typedef TYPELIST_5( A1, A2, A3, A4, A5 ) ArgumentTypes;
        typedef MetaBase::FalseType IsConst;
    };

    template <typename R, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6 >
    struct Function< R (*)( A1, A2, A3, A4, A5, A6 ) >
    {
        typedef MetaBase::NullType ClassType;
        typedef R ReturnType;
        typedef TYPELIST_6( A1, A2, A3, A4, A5, A6 ) ArgumentTypes;
        typedef MetaBase::FalseType IsConst;
    };

    template <typename R, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7 >
    struct Function< R (*)( A1, A2, A3, A4, A5, A6, A7 ) >
    {
        typedef MetaBase::NullType ClassType;
        typedef R ReturnType;
        typedef TYPELIST_7( A1, A2, A3, A4, A5, A6, A7 ) ArgumentTypes;
        typedef MetaBase::FalseType IsConst;
    };

    template <typename R, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8 >
    struct Function< R (*)( A1, A2, A3, A4, A5, A6, A7, A8 ) >
    {
        typedef MetaBase::NullType ClassType;
        typedef R ReturnType;
        typedef TYPELIST_8( A1, A2, A3, A4, A5, A6, A7, A8 ) ArgumentTypes;
        typedef MetaBase::FalseType IsConst;
    };

    template <typename R, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9 >
    struct Function< R (*)( A1, A2, A3, A4, A5, A6, A7, A8, A9 ) >
    {
        typedef MetaBase::NullType ClassType;
        typedef R ReturnType;
        typedef TYPELIST_9( A1, A2, A3, A4, A5, A6, A7, A8, A9 ) ArgumentTypes;
        typedef MetaBase::FalseType IsConst;
    };

    template <typename R, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10 >
    struct Function< R (*)( A1, A2, A3, A4, A5, A6, A7, A8, A9, A10 ) >
    {
        typedef MetaBase::NullType ClassType;
        typedef R ReturnType;
        typedef TYPELIST_10( A1, A2, A3, A4, A5, A6, A7, A8, A9, A10 ) ArgumentTypes;
        typedef MetaBase::FalseType IsConst;
    };

    template <typename R, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11 >
    struct Function< R (*)( A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11 ) >
    {
        typedef MetaBase::NullType ClassType;
        typedef R ReturnType;
        typedef TYPELIST_11( A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11 ) ArgumentTypes;
        typedef MetaBase::FalseType IsConst;
    };

    template <typename R, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12 >
    struct Function< R (*)( A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12 ) >
    {
        typedef MetaBase::NullType ClassType;
        typedef R ReturnType;
        typedef TYPELIST_12( A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12 ) ArgumentTypes;
        typedef MetaBase::FalseType IsConst;
    };

    template <typename R, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12, typename A13 >
    struct Function< R (*)( A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13 ) >
    {
        typedef MetaBase::NullType ClassType;
        typedef R ReturnType;
        typedef TYPELIST_13( A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13 ) ArgumentTypes;
        typedef MetaBase::FalseType IsConst;
    };

    template <typename R, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12, typename A13, typename A14 >
    struct Function< R (*)( A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14 ) >
    {
        typedef MetaBase::NullType ClassType;
        typedef R ReturnType;
        typedef TYPELIST_14( A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14 ) ArgumentTypes;
        typedef MetaBase::FalseType IsConst;
    };

    template <typename R, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12, typename A13, typename A14, typename A15 >
    struct Function< R (*)( A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, A15 ) >
    {
        typedef MetaBase::NullType ClassType;
        typedef R ReturnType;
        typedef TYPELIST_15( A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, A15 ) ArgumentTypes;
        typedef MetaBase::FalseType IsConst;
    };
}

#endif // REFLECTOR_FUNCTION_H__INCLUDED
