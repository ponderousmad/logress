#ifndef TEST_OBJECTFACTORY_H__INCLUDED
#define TEST_OBJECTFACTORY_H__INCLUDED
/* ---------------------------------------------------------------
 * Copyright (c) Adrian Smith.
 * Licensed under the MIT license. See license.txt at project root.
 * --------------------------------------------------------------- */

#include "Test/TestObject.h"
#include "Test/TestBase.h"
#include "Test/TestArgumentList.h"
#include "Test/TestArgumentTraits.h"
#include "Test/TestArgumentsParser.h"
#include "MetaBase/MetaBaseTypeListLength.h"

#include <memory>

namespace Test
{
    template <class C>
    class ObjectFactory;

    class IConstructor;

    namespace InvokeConstructor
    {
        template <typename C, typename ArgList, int N>
        struct Invoker
        {
            static C* invoke( const ArgList& )
            {
                return new C();
            }
        };

        template <typename C, typename ArgList>
        struct Invoker<C, ArgList, 1>
        {
            static C* invoke( const ArgList& a )
            {
                return new C(
                    a.getItem( Test::ArgumentNumber<0>() )
                );
            }
        };

        template <typename C, typename ArgList>
        struct Invoker<C, ArgList, 2>
        {
            static C* invoke( const ArgList& a )
            {
                return new C(
                    a.getItem( Test::ArgumentNumber<0>() ),
                    a.getItem( Test::ArgumentNumber<1>() )
                );
            }
        };

        template <typename C, typename ArgList>
        struct Invoker<C, ArgList, 3>
        {
            static C* invoke( const ArgList& a )
            {
                return new C(
                    a.getItem( Test::ArgumentNumber<0>() ),
                    a.getItem( Test::ArgumentNumber<1>() ),
                    a.getItem( Test::ArgumentNumber<2>() )
                );
            }
        };

        template <typename C, typename ArgList>
        struct Invoker<C, ArgList, 4>
        {
            static C* invoke( const ArgList& a )
            {
                return new C(
                    a.getItem( Test::ArgumentNumber<0>() ),
                    a.getItem( Test::ArgumentNumber<1>() ),
                    a.getItem( Test::ArgumentNumber<2>() ),
                    a.getItem( Test::ArgumentNumber<3>() )
                );
            }
        };

        template <typename C, typename ArgList>
        struct Invoker<C, ArgList, 5>
        {
            static C* invoke( const ArgList& a )
            {
                return new C(
                    a.getItem( Test::ArgumentNumber<0>() ),
                    a.getItem( Test::ArgumentNumber<1>() ),
                    a.getItem( Test::ArgumentNumber<2>() ),
                    a.getItem( Test::ArgumentNumber<3>() ),
                    a.getItem( Test::ArgumentNumber<4>() )
                );
            }
        };

        template <typename C, typename ArgList>
        struct Invoker<C, ArgList, 6>
        {
            static C* invoke( const ArgList& a )
            {
                return new C(
                    a.getItem( Test::ArgumentNumber<0>() ),
                    a.getItem( Test::ArgumentNumber<1>() ),
                    a.getItem( Test::ArgumentNumber<2>() ),
                    a.getItem( Test::ArgumentNumber<3>() ),
                    a.getItem( Test::ArgumentNumber<4>() ),
                    a.getItem( Test::ArgumentNumber<5>() )
                );
            }
        };

        template <typename C, typename ArgList>
        struct Invoker<C, ArgList, 7>
        {
            static C* invoke( const ArgList& a )
            {
                return new C(
                    a.getItem( Test::ArgumentNumber<0>() ),
                    a.getItem( Test::ArgumentNumber<1>() ),
                    a.getItem( Test::ArgumentNumber<2>() ),
                    a.getItem( Test::ArgumentNumber<3>() ),
                    a.getItem( Test::ArgumentNumber<4>() ),
                    a.getItem( Test::ArgumentNumber<5>() ),
                    a.getItem( Test::ArgumentNumber<6>() )
                );
            }
        };

        template <typename C, typename ArgList>
        struct Invoker<C, ArgList, 8>
        {
            static C* invoke( const ArgList& a )
            {
                return new C(
                    a.getItem( Test::ArgumentNumber<0>() ),
                    a.getItem( Test::ArgumentNumber<1>() ),
                    a.getItem( Test::ArgumentNumber<2>() ),
                    a.getItem( Test::ArgumentNumber<3>() ),
                    a.getItem( Test::ArgumentNumber<4>() ),
                    a.getItem( Test::ArgumentNumber<5>() ),
                    a.getItem( Test::ArgumentNumber<6>() ),
                    a.getItem( Test::ArgumentNumber<7>() )
                );
            }
        };

        template <typename C, typename ArgList>
        struct Invoker<C, ArgList, 9>
        {
            static C* invoke( const ArgList& a )
            {
                return new C(
                    a.getItem( Test::ArgumentNumber<0>() ),
                    a.getItem( Test::ArgumentNumber<1>() ),
                    a.getItem( Test::ArgumentNumber<2>() ),
                    a.getItem( Test::ArgumentNumber<3>() ),
                    a.getItem( Test::ArgumentNumber<4>() ),
                    a.getItem( Test::ArgumentNumber<5>() ),
                    a.getItem( Test::ArgumentNumber<6>() ),
                    a.getItem( Test::ArgumentNumber<7>() ),
                    a.getItem( Test::ArgumentNumber<8>() )
                );
            }
        };

        template <typename C, typename ArgList>
        struct Invoker<C, ArgList, 10>
        {
            static C* invoke( const ArgList& a )
            {
                return new C(
                    a.getItem( Test::ArgumentNumber<0>() ),
                    a.getItem( Test::ArgumentNumber<1>() ),
                    a.getItem( Test::ArgumentNumber<2>() ),
                    a.getItem( Test::ArgumentNumber<3>() ),
                    a.getItem( Test::ArgumentNumber<4>() ),
                    a.getItem( Test::ArgumentNumber<5>() ),
                    a.getItem( Test::ArgumentNumber<6>() ),
                    a.getItem( Test::ArgumentNumber<7>() ),
                    a.getItem( Test::ArgumentNumber<8>() ),
                    a.getItem( Test::ArgumentNumber<9>() )
                );
            }
        };

        template <typename C, typename ArgList>
        struct Invoker<C, ArgList, 11>
        {
            static C* invoke( const ArgList& a )
            {
                return new C(
                    a.getItem( Test::ArgumentNumber<0>() ),
                    a.getItem( Test::ArgumentNumber<1>() ),
                    a.getItem( Test::ArgumentNumber<2>() ),
                    a.getItem( Test::ArgumentNumber<3>() ),
                    a.getItem( Test::ArgumentNumber<4>() ),
                    a.getItem( Test::ArgumentNumber<5>() ),
                    a.getItem( Test::ArgumentNumber<6>() ),
                    a.getItem( Test::ArgumentNumber<7>() ),
                    a.getItem( Test::ArgumentNumber<8>() ),
                    a.getItem( Test::ArgumentNumber<9>() ),
                    a.getItem( Test::ArgumentNumber<10>() )
                );
            }
        };

        template <typename C, typename ArgList>
        struct Invoker<C, ArgList, 12>
        {
            static C* invoke( const ArgList& a )
            {
                return new C(
                    a.getItem( Test::ArgumentNumber<0>() ),
                    a.getItem( Test::ArgumentNumber<1>() ),
                    a.getItem( Test::ArgumentNumber<2>() ),
                    a.getItem( Test::ArgumentNumber<3>() ),
                    a.getItem( Test::ArgumentNumber<4>() ),
                    a.getItem( Test::ArgumentNumber<5>() ),
                    a.getItem( Test::ArgumentNumber<6>() ),
                    a.getItem( Test::ArgumentNumber<7>() ),
                    a.getItem( Test::ArgumentNumber<8>() ),
                    a.getItem( Test::ArgumentNumber<9>() ),
                    a.getItem( Test::ArgumentNumber<10>() ),
                    a.getItem( Test::ArgumentNumber<11>() )
                );
            }
        };

        template <typename C, typename ArgList>
        struct Invoker<C, ArgList, 13>
        {
            static C* invoke( const ArgList& a )
            {
                return new C(
                    a.getItem( Test::ArgumentNumber<0>() ),
                    a.getItem( Test::ArgumentNumber<1>() ),
                    a.getItem( Test::ArgumentNumber<2>() ),
                    a.getItem( Test::ArgumentNumber<3>() ),
                    a.getItem( Test::ArgumentNumber<4>() ),
                    a.getItem( Test::ArgumentNumber<5>() ),
                    a.getItem( Test::ArgumentNumber<6>() ),
                    a.getItem( Test::ArgumentNumber<7>() ),
                    a.getItem( Test::ArgumentNumber<8>() ),
                    a.getItem( Test::ArgumentNumber<9>() ),
                    a.getItem( Test::ArgumentNumber<10>() ),
                    a.getItem( Test::ArgumentNumber<11>() ),
                    a.getItem( Test::ArgumentNumber<12>() )
                );
            }
        };

        template <typename C, typename ArgList>
        struct Invoker<C, ArgList, 14>
        {
            static C* invoke( const ArgList& a )
            {
                return new C(
                    a.getItem( Test::ArgumentNumber<0>() ),
                    a.getItem( Test::ArgumentNumber<1>() ),
                    a.getItem( Test::ArgumentNumber<2>() ),
                    a.getItem( Test::ArgumentNumber<3>() ),
                    a.getItem( Test::ArgumentNumber<4>() ),
                    a.getItem( Test::ArgumentNumber<5>() ),
                    a.getItem( Test::ArgumentNumber<6>() ),
                    a.getItem( Test::ArgumentNumber<7>() ),
                    a.getItem( Test::ArgumentNumber<8>() ),
                    a.getItem( Test::ArgumentNumber<9>() ),
                    a.getItem( Test::ArgumentNumber<10>() ),
                    a.getItem( Test::ArgumentNumber<11>() ),
                    a.getItem( Test::ArgumentNumber<12>() ),
                    a.getItem( Test::ArgumentNumber<13>() )
                );
            }
        };

        template <typename C, typename ArgList>
        struct Invoker<C, ArgList, 15>
        {
            static C* invoke( const ArgList& a )
            {
                return new C(
                    a.getItem( Test::ArgumentNumber<0>() ),
                    a.getItem( Test::ArgumentNumber<1>() ),
                    a.getItem( Test::ArgumentNumber<2>() ),
                    a.getItem( Test::ArgumentNumber<3>() ),
                    a.getItem( Test::ArgumentNumber<4>() ),
                    a.getItem( Test::ArgumentNumber<5>() ),
                    a.getItem( Test::ArgumentNumber<6>() ),
                    a.getItem( Test::ArgumentNumber<7>() ),
                    a.getItem( Test::ArgumentNumber<8>() ),
                    a.getItem( Test::ArgumentNumber<9>() ),
                    a.getItem( Test::ArgumentNumber<10>() ),
                    a.getItem( Test::ArgumentNumber<11>() ),
                    a.getItem( Test::ArgumentNumber<12>() ),
                    a.getItem( Test::ArgumentNumber<13>() ),
                    a.getItem( Test::ArgumentNumber<14>() )
                );
            }
        };
    }
}

template <class C>
class Test::ObjectFactory : public Test::IObjectFactory
{
    PREVENT_COPY_AND_ASSIGNMENT( ObjectFactory );
public:
    class IConstructor
    {
        PREVENT_COPY_AND_ASSIGNMENT( IConstructor );
    public:
        IConstructor() {}
        virtual ~IConstructor() {}

        virtual C* construct( const Test::InvokeContext& context ) = 0;
    };

    template <typename ArgTypes>
    class Constructor : public IConstructor
    {
        PREVENT_COPY_AND_ASSIGNMENT( Constructor );
    private:
        typedef Test::ArgumentList< ArgTypes, Test::ArgumentTraitsBaseType > ArgList;
        enum { kArgCount = MetaBase::ListLength< ArgTypes >::Value };

    public:
        Constructor()
        {
        }

        virtual ~Constructor()
        {
        }

        virtual C* construct( const Test::InvokeContext& context )
        {
            Test::ArgumentsParser<ArgList> args( context );
            return Test::InvokeConstructor::Invoker<C, ArgList, kArgCount>::invoke( args.parse() );
        }
    };

    typedef typename Test::Object<C>::VTable VTable;
    typedef typename Memory::Shared<const VTable> ConstVTableH;

    ObjectFactory( ConstVTableH vTable, std::auto_ptr<IConstructor> constructor )
        : mVTable( vTable )
        , mConstructor( constructor )
    {
    }

    ~ObjectFactory()
    {
    }

    virtual Result construct( const Test::InvokeContext& context ) const
    {
        C* newObj = mConstructor->construct( context );
        if( !newObj )
        {
            return Result( Test::InvokeResult::kConstructorFailed, 0 );
        }
        return Result( Test::InvokeResult::kSuccess, new Test::Object<C>( newObj, mVTable ) );
    }

    template <typename ArgTypes>
    static Test::ConstObjectFactoryH buildFactory( ConstVTableH vTable )
    {
        std::auto_ptr<IConstructor> constructor( new Constructor<ArgTypes>() );
        return Test::ConstObjectFactoryH( new ObjectFactory( vTable, constructor ) );
    }

private:
    ConstVTableH mVTable;
    std::auto_ptr<IConstructor> mConstructor;
};

#endif // TEST_OBJECTFACTORY_H__INCLUDED
