#ifndef TEST_BUILDCHECK_H__INCLUDED
#define TEST_BUILDCHECK_H__INCLUDED
/* ---------------------------------------------------------------
 * Copyright (c) Adrian Smith.
 * Licensed under the MIT license. See license.txt at project root.
 * --------------------------------------------------------------- */

#include "Test/TestIgnoreValue.h"
#include "Test/TestEnvironment.h"
#include "Test/TestBase.h"
#include "String/StringCasts.h"
#include "MetaBase/MetaBaseAddReference.h"
#include "MetaBase/MetaBaseAddConst.h"
#include "MetaBase/MetaBaseAssert.h"
#include "MetaBase/MetaBaseSame.h"

namespace Test {

    template <typename T, typename S>
    struct Compare
    {
        static bool equal( const T& left, const S& right ) { return left == right; }
    };

    template <typename T>
    struct Compare<T, const std::string& >
    {
        static bool equal( T left, const std::string& right )
        {
            return left == String::as<T>( right );
        }
    };

    template <typename T>
    struct CheckTraits
    {
        typedef typename MetaBase::AddConst<T>::Type ConstType;
        typedef typename MetaBase::AddReference<ConstType>::Type ParameterType;
        typedef T StoreType;
        typedef Compare< T, const std::string& > Compare;

        enum { Lookup = false };
    };

    template <typename T, bool Lookup>
    bool doCheck(
            const std::string& target,
            Test::Environment&,
            typename CheckTraits<T>::StoreType &store
    )
    {
        return CheckTraits<T>::Compare::equal( store, target);
    }

    template <typename T, bool Lookup>
    struct DoChecking
    {
        static bool check(
            const std::string& target,
            Test::Environment& environment,
            typename MetaBase::AddReference< typename CheckTraits<T>::StoreType >::Type store
        )
        {
            return CheckTraits<T>::Compare::equal( store, target );
        }
    };

    template <typename T>
    struct DoChecking<T, true>
    {
         static bool check(
             const std::string& target,
             Test::Environment& environment,
             typename CheckTraits<T>::StoreType& store
         )
         {
             return CheckTraits<T>::Compare::equal( store, environment.lookup< CheckTraits<T>::LookupType >( target ) );
         }
    };

    template <typename T>
    class Checker : public ValueCheck
    {
        PREVENT_COPY_AND_ASSIGNMENT( Checker );
    public:
        typedef CheckTraits<T> Traits;
        typedef typename Traits::Compare Comp;
        Checker( typename Traits::ParameterType value )
            : mValue( value )
        {
        }

        virtual bool check( const std::string& target, Test::Environment& environment )
        {
            typedef Test::DoChecking<T, Traits::Lookup> Checker;
            return Checker::check( target, environment, mValue );
        }

    private:
        typename Traits::StoreType mValue;
    };

    template <typename T>
    struct CheckBuilder
    {
        typedef typename CheckTraits<T>::ParameterType ParameterType;

        Test::ValueCheck* build( ParameterType value )
        {
            return new Checker<T>( value );
        }
    };
}

#endif // TEST_BUILDCHECK_H__INCLUDED
