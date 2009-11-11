#ifndef TEST_ARGUMENTTRAITS_H__INCLUDED
#define TEST_ARGUMENTTRAITS_H__INCLUDED

#include "MetaBase/MetaBaseRemoveReference.h"
#include "MetaBase/MetaBaseRemoveConst.h"

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
    };

    template <typename T>
    class ArgumentTraitsBaseType : public ArgumentTraits< typename MetaBase::RemoveConst< typename MetaBase::RemoveReference<T>::Type >::Type >
    {
    };
}

#endif // TEST_ARGUMENTTRAITS_H__INCLUDED
