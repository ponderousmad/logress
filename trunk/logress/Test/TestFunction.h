#ifndef TEST_FUNCTION_H__INCLUDED
#define TEST_FUNCTION_H__INCLUDED

#include "Test/TestBase.h"
#include "Test/TestArgumentList.h"
#include "Test/TestArgumentTraits.h"
#include "Test/TestArgumentsParser.h"
#include "Test/TestBuildCheck.h"
#include "Test/TestIgnoreValue.h"
#include "Reflector/ReflectorFunction.h"
#include "MetaBase/MetaBaseTypeListLength.h"
#include "Memory/MemoryShared.h"

namespace Test {
    template <typename F>
    class Function;

    namespace InvokeFunction
    {
        template <typename F, typename ArgList, typename ReturnType, int N>
        struct Invoker
        {
            static ReturnType invoke(F& func, const ArgList&)
            {
                return func();
            }
        };

        template <typename F, typename ArgList, typename ReturnType>
        struct Invoker<F, ArgList, ReturnType, 1>
        {
            static ReturnType invoke(F& func, const ArgList& a)
            {
                return func(
                    a.getItem( Test::ArgumentNumber<0>() )
                );
            }
        };

        template <typename F, typename ArgList, typename ReturnType>
        struct Invoker<F, ArgList, ReturnType, 2>
        {
            static ReturnType invoke(F& func, const ArgList& a)
            {
                return func(
                    a.getItem( Test::ArgumentNumber<0>() ),
                    a.getItem( Test::ArgumentNumber<1>() )
                );
            }
        };

        template <typename F, typename ArgList, typename ReturnType>
        struct Invoker<F, ArgList, ReturnType, 3>
        {
            static ReturnType invoke(F& func, const ArgList& a)
            {
                return func(
                    a.getItem( Test::ArgumentNumber<0>() ),
                    a.getItem( Test::ArgumentNumber<1>() ),
                    a.getItem( Test::ArgumentNumber<2>() )
                );
            }
        };

        template <typename F, typename ArgList, typename ReturnType>
        struct Invoker<F, ArgList, ReturnType, 4>
        {
            static ReturnType invoke(F& func, const ArgList& a)
            {
                return func(
                    a.getItem( Test::ArgumentNumber<0>() ),
                    a.getItem( Test::ArgumentNumber<1>() ),
                    a.getItem( Test::ArgumentNumber<2>() ),
                    a.getItem( Test::ArgumentNumber<3>() )
                );
            }
        };

        template <typename F, typename ArgList, typename ReturnType>
        struct Invoker<F, ArgList, ReturnType, 5>
        {
            static ReturnType invoke(F& func, const ArgList& a)
            {
                return func(
                    a.getItem( Test::ArgumentNumber<0>() ),
                    a.getItem( Test::ArgumentNumber<1>() ),
                    a.getItem( Test::ArgumentNumber<2>() ),
                    a.getItem( Test::ArgumentNumber<3>() ),
                    a.getItem( Test::ArgumentNumber<4>() )
                );
            }
        };

        template <typename F, typename ArgList, typename ReturnType>
        struct Invoker<F, ArgList, ReturnType, 6>
        {
            static ReturnType invoke(F& func, const ArgList& a)
            {
                return func(
                    a.getItem( Test::ArgumentNumber<0>() ),
                    a.getItem( Test::ArgumentNumber<1>() ),
                    a.getItem( Test::ArgumentNumber<2>() ),
                    a.getItem( Test::ArgumentNumber<3>() ),
                    a.getItem( Test::ArgumentNumber<4>() ),
                    a.getItem( Test::ArgumentNumber<5>() )
                );
            }
        };

        template <typename F, typename ArgList, typename ReturnType>
        struct Invoker<F, ArgList, ReturnType, 7>
        {
            static ReturnType invoke(F& func, const ArgList& a)
            {
                return func(
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

        template <typename F, typename ArgList, typename ReturnType>
        struct Invoker<F, ArgList, ReturnType, 8>
        {
            static ReturnType invoke(F& func, const ArgList& a)
            {
                return func(
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

        template <typename F, typename ArgList, typename ReturnType>
        struct Invoker<F, ArgList, ReturnType, 9>
        {
            static ReturnType invoke(F& func, const ArgList& a)
            {
                return func(
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

        template <typename F, typename ArgList, typename ReturnType>
        struct Invoker<F, ArgList, ReturnType, 10>
        {
            static ReturnType invoke(F& func, const ArgList& a)
            {
                return func(
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

        template <typename F, typename ArgList, typename ReturnType>
        struct Invoker<F, ArgList, ReturnType, 11>
        {
            static ReturnType invoke(F& func, const ArgList& a)
            {
                return func(
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

        template <typename F, typename ArgList, typename ReturnType>
        struct Invoker<F, ArgList, ReturnType, 12>
        {
            static ReturnType invoke(F& func, const ArgList& a)
            {
                return func(
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

        template <typename F, typename ArgList, typename ReturnType>
        struct Invoker<F, ArgList, ReturnType, 13>
        {
            static ReturnType invoke(F& func, const ArgList& a)
            {
                return func(
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

        template <typename F, typename ArgList, typename ReturnType>
        struct Invoker<F, ArgList, ReturnType, 14>
        {
            static ReturnType invoke(F& func, const ArgList& a)
            {
                return func(
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

        template <typename F, typename ArgList, typename ReturnType>
        struct Invoker<F, ArgList, ReturnType, 15>
        {
            static ReturnType invoke(F& func, const ArgList& a)
            {
                return func(
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

        template <typename F, typename ArgList, int kArgCount, typename ReturnType>
        struct CheckedInvoker
        {
            static Test::ValueCheck* invoke( F func, const Test::InvokeContext& context )
            {
                Test::ArgumentsParser<ArgList> args( context );
                Test::CheckBuilder<ReturnType> builder;
                return builder.build( Invoker<F, ArgList, ReturnType, kArgCount>::invoke( func, args.parse() ) );
            }
        };

        template <typename F, typename ArgList, int kArgCount>
        struct CheckedInvoker<F, ArgList, kArgCount, void>
        {
            static Test::ValueCheck* invoke( F func, const Test::InvokeContext& context )
            {
                Test::ArgumentsParser<ArgList> args( context );
                Invoker<F, ArgList, void, kArgCount>::invoke( func, args.parse() );
                return new Test::IgnoreValue();
            }
        };
    }
}

template <typename F>
class Test::Function : public Test::IFunction
{
private:
    F mFunc;
    typedef Reflector::Function< F > FInfo;
    typedef typename FInfo::ArgumentTypes ArgTypes;
    enum { kArgCount = MetaBase::ListLength< ArgTypes >::Value };
    typedef Test::ArgumentList< ArgTypes, Test::ArgumentTraitsBaseType > ArgList;

public:
    Function( F func )
        : mFunc( func )
    {
    }

    virtual ~Function()
    {
    }

    virtual Test::InvokeResult invoke( const Test::InvokeContext& context ) const
    {
        typedef typename Test::InvokeFunction::CheckedInvoker<F, ArgList, kArgCount, typename FInfo::ReturnType> Invoker;
        return Test::InvokeResult( Invoker::invoke( mFunc, context ) );
    }
};

namespace Test {
    template <typename F>
    ConstFunctionH buildFunction( F function )
    {
        return ConstFunctionH( new Function<F>( function ) );
    }
}

#endif // TEST_FUNCTION_H__INCLUDED
