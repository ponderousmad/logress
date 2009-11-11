#ifndef TEST_METHOD_H__INCLUDED
#define TEST_METHOD_H__INCLUDED

#include "Test/TestBase.h"
#include "Test/TestArgumentList.h"
#include "Test/TestArgumentTraits.h"
#include "Test/TestArgumentsParser.h"
#include "Test/TestBuildCheck.h"
#include "Test/TestIgnoreValue.h"
#include "Reflector/ReflectorMethod.h"
#include "Reflector/ReflectorConstMethod.h"
#include "MetaBase/MetaBaseTypeListLength.h"
#include "Memory/MemoryShared.h"

namespace Test {
    template <typename F, typename ClassType >
    class Method;

    namespace InvokeMethod
    {
        template <typename C, typename F, typename ArgList, typename ReturnType, int N>
        struct Invoker
        {
            static ReturnType invoke( C* obj, F& func, const ArgList& )
            {
                return (obj->*func)();
            }
        };

        template <typename C, typename F, typename ArgList, typename ReturnType>
        struct Invoker<C, F, ArgList, ReturnType, 1>
        {
            static ReturnType invoke( C* obj, F& func, const ArgList& a )
            {
                return (obj->*func)(
                    a.getItem( Test::ArgumentNumber<0>() )
                );
            }
        };

        template <typename C, typename F, typename ArgList, typename ReturnType>
        struct Invoker<C, F, ArgList, ReturnType, 2>
        {
            static ReturnType invoke( C* obj, F& func, const ArgList& a )
            {
                return (obj->*func)(
                    a.getItem( Test::ArgumentNumber<0>() ),
                    a.getItem( Test::ArgumentNumber<1>() )
                );
            }
        };

        template <typename C, typename F, typename ArgList, typename ReturnType>
        struct Invoker<C, F, ArgList, ReturnType, 3>
        {
            static ReturnType invoke( C* obj, F& func, const ArgList& a )
            {
                return (obj->*func)(
                    a.getItem( Test::ArgumentNumber<0>() ),
                    a.getItem( Test::ArgumentNumber<1>() ),
                    a.getItem( Test::ArgumentNumber<2>() )
                );
            }
        };

        template <typename C, typename F, typename ArgList, typename ReturnType>
        struct Invoker<C, F, ArgList, ReturnType, 4>
        {
            static ReturnType invoke( C* obj, F& func, const ArgList& a )
            {
                return (obj->*func)(
                    a.getItem( Test::ArgumentNumber<0>() ),
                    a.getItem( Test::ArgumentNumber<1>() ),
                    a.getItem( Test::ArgumentNumber<2>() ),
                    a.getItem( Test::ArgumentNumber<3>() )
                );
            }
        };

        template <typename C, typename F, typename ArgList, typename ReturnType>
        struct Invoker<C, F, ArgList, ReturnType, 5>
        {
            static ReturnType invoke( C* obj, F& func, const ArgList& a )
            {
                return (obj->*func)(
                    a.getItem( Test::ArgumentNumber<0>() ),
                    a.getItem( Test::ArgumentNumber<1>() ),
                    a.getItem( Test::ArgumentNumber<2>() ),
                    a.getItem( Test::ArgumentNumber<3>() ),
                    a.getItem( Test::ArgumentNumber<4>() )
                );
            }
        };

        template <typename C, typename F, typename ArgList, typename ReturnType>
        struct Invoker<C, F, ArgList, ReturnType, 6>
        {
            static ReturnType invoke( C* obj, F& func, const ArgList& a )
            {
                return (obj->*func)(
                    a.getItem( Test::ArgumentNumber<0>() ),
                    a.getItem( Test::ArgumentNumber<1>() ),
                    a.getItem( Test::ArgumentNumber<2>() ),
                    a.getItem( Test::ArgumentNumber<3>() ),
                    a.getItem( Test::ArgumentNumber<4>() ),
                    a.getItem( Test::ArgumentNumber<5>() )
                );
            }
        };

        template <typename C, typename F, typename ArgList, typename ReturnType>
        struct Invoker<C, F, ArgList, ReturnType, 7>
        {
            static ReturnType invoke( C* obj, F& func, const ArgList& a )
            {
                return (obj->*func)(
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

        template <typename C, typename F, typename ArgList, typename ReturnType>
        struct Invoker<C, F, ArgList, ReturnType, 8>
        {
            static ReturnType invoke( C* obj, F& func, const ArgList& a )
            {
                return (obj->*func)(
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

        template <typename C, typename F, typename ArgList, typename ReturnType>
        struct Invoker<C, F, ArgList, ReturnType, 9>
        {
            static ReturnType invoke( C* obj, F& func, const ArgList& a )
            {
                return (obj->*func)(
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

        template <typename C, typename F, typename ArgList, typename ReturnType>
        struct Invoker<C, F, ArgList, ReturnType, 10>
        {
            static ReturnType invoke( C* obj, F& func, const ArgList& a )
            {
                return (obj->*func)(
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

        template <typename C, typename F, typename ArgList, typename ReturnType>
        struct Invoker<C, F, ArgList, ReturnType, 11>
        {
            static ReturnType invoke( C* obj, F& func, const ArgList& a )
            {
                return (obj->*func)(
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

        template <typename C, typename F, typename ArgList, typename ReturnType>
        struct Invoker<C, F, ArgList, ReturnType, 12>
        {
            static ReturnType invoke( C* obj, F& func, const ArgList& a )
            {
                return (obj->*func)(
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

        template <typename C, typename F, typename ArgList, typename ReturnType>
        struct Invoker<C, F, ArgList, ReturnType, 13>
        {
            static ReturnType invoke( C* obj, F& func, const ArgList& a )
            {
                return (obj->*func)(
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

        template <typename C, typename F, typename ArgList, typename ReturnType>
        struct Invoker<C, F, ArgList, ReturnType, 14>
        {
            static ReturnType invoke( C* obj, F& func, const ArgList& a )
            {
                return (obj->*func)(
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

        template <typename C, typename F, typename ArgList, typename ReturnType>
        struct Invoker<C, F, ArgList, ReturnType, 15>
        {
            static ReturnType invoke( C* obj, F& func, const ArgList& a )
            {
                return (obj->*func)(
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

        template <typename C, typename F, typename ArgList, int kArgCount, typename ReturnType>
        struct CheckedInvoker
        {
            static Test::ValueCheck* invoke( C& obj, F func, const Test::InvokeContext& context )
            {
                Test::ArgumentsParser<ArgList> args( context );
                Test::CheckBuilder<ReturnType> builder;
                return builder.build( Invoker<C, F, ArgList, ReturnType, kArgCount>::invoke( &obj, func, args.parse() ) );
            }
        };

        template <typename C, typename F, typename ArgList, int kArgCount>
        struct CheckedInvoker<C, F, ArgList, kArgCount, void>
        {
            static Test::ValueCheck* invoke( C& obj, F func, const Test::InvokeContext& context )
            {
                Test::ArgumentsParser<ArgList> args( context );
                Invoker<C, F, ArgList, void, kArgCount>::invoke( &obj, func, args.parse() );
                return new Test::IgnoreValue();
            }
        };
    }
}

template <typename F, typename C >
class Test::Method : public IMethod< C >
{
private:
    F mFunc;
    typedef Reflector::Function< F > FInfo;
    typedef typename FInfo::ArgumentTypes ArgTypes;
    enum { kArgCount = MetaBase::ListLength< ArgTypes >::Value };
    typedef Test::ArgumentList< ArgTypes, Test::ArgumentTraitsBaseType > ArgList;

public:
    Method( F func )
        : mFunc( func )
    {
    }

    virtual ~Method()
    {
    }

    virtual Test::InvokeResult invoke( C& obj, const Test::InvokeContext& context ) const
    {
        typedef typename Test::InvokeMethod::CheckedInvoker<C, F, ArgList, kArgCount, typename FInfo::ReturnType> Invoker;
        return Test::InvokeResult( Invoker::invoke( obj, mFunc, context ) );
    }
};

namespace Test {
    template <typename M>
    Memory::Shared< IMethod< typename Reflector::Function< M >::ClassType > > buildMethod( M method )
    {
        return Memory::Shared< IMethod< typename Reflector::Function< M >::ClassType > >( new Method< M, typename Reflector::Function< M >::ClassType >( method ) );
    }

    template <typename C>
    struct MethodBuilder
    {
        template <typename M>
        static Memory::Shared< IMethod<C> > build( M method )
        {
            return Memory::Shared< IMethod<C> >( new Method<M, C>( method ) );
        }
    };
}

#endif // TEST_METHOD_H__INCLUDED
