/* ---------------------------------------------------------------
 * Copyright (c) Adrian Smith.
 * Licensed under the MIT license. See license.txt at project root.
 * --------------------------------------------------------------- */
#ifndef TEST_ARGUMENTTRAITS_H__INCLUDED
#define TEST_ARGUMENTTRAITS_H__INCLUDED

#include "MetaBase/MetaBaseRemoveReference.h"
#include "MetaBase/MetaBaseRemoveConst.h"
#include "String/StringCasts.h"
#include "String/StringUtils.h"

#include <string>

namespace Test
{
    template <typename T>
    class ArgumentTraits
    {
    };

    template <>
    class ArgumentTraits< int >
    {
    public:
        typedef int StoreType;
        typedef int ConstReturnType;
        typedef int& RefReturnType;

        static ConstReturnType forConstReturn( const StoreType& value ) { return value; }
        static RefReturnType forRefReturn( StoreType& value ) { return value; }
        static std::string forLogOutput( int value ) { return String::make( value ); }
    };

    template <>
    class ArgumentTraits< float >
    {
    public:
        typedef float StoreType;
        typedef float ConstReturnType;
        typedef float& RefReturnType;

        static ConstReturnType forConstReturn( const StoreType& value ) { return value; }
        static RefReturnType forRefReturn( StoreType& value ) { return value; }
        static std::string forLogOutput( float value ) { return String::make( value, false, 12 ); }
    };

    template <>
    class ArgumentTraits< double >
    {
    public:
        typedef double StoreType;
        typedef double ConstReturnType;
        typedef double& RefReturnType;

        static ConstReturnType forConstReturn( const StoreType& value ) { return value; }
        static RefReturnType forRefReturn( StoreType& value ) { return value; }
        static std::string forLogOutput( double value ) { return String::make( value, false, 18 ); }
    };

    template <>
    class ArgumentTraits< const char* >
    {
    public:
        typedef std::string StoreType;
        typedef const char* ConstReturnType;
        typedef std::string& RefReturnType;

        static ConstReturnType forConstReturn( const StoreType& value ) { return value.c_str(); }
        static RefReturnType forRefReturn( StoreType& value ) { return value; }
        static std::string forLogOutput( const char* value ) { return String::quote( value ); }
    };

    template <>
    class ArgumentTraits< std::string >
    {
    public:
        typedef std::string StoreType;
        typedef const std::string& ConstReturnType;
        typedef std::string& RefReturnType;

        static ConstReturnType forConstReturn( const StoreType& value ) { return value; }
        static RefReturnType forRefReturn( StoreType& value ) { return value; }
        static std::string forLogOutput( const std::string& value ) { return String::quote( value ); }
    };

    template <typename T>
    class ArgumentTraitsBaseType : public ArgumentTraits< typename MetaBase::RemoveConst< typename MetaBase::RemoveReference<T>::Type >::Type >
    {
    };
}

#endif // TEST_ARGUMENTTRAITS_H__INCLUDED
