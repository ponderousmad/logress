#ifndef TESTLOGWRITER_H__INCLUDED
#define TESTLOGWRITER_H__INCLUDED

/* ---------------------------------------------------------------
 * Copyright (c) Adrian Smith.
 * Licensed under the MIT license. See license.txt at project root.
 * --------------------------------------------------------------- */

#ifdef LOGGING

#include "Test/TestLogFormat.h"
#include "Test/TestArgumentTraits.h"
#include <string>
#include <ostream>
#include <memory>
#include <map>

namespace Test
{
    class LogWriter;
}

class Test::LogWriter
{
    PREVENT_COPY_AND_ASSIGNMENT( LogWriter );
public:
    enum EntryType
    {
        Constructor,
        Function,
        Method
    };

    LogWriter( std::ostream& stream );
    LogWriter( std::auto_ptr<std::ostream> stream );
    ~LogWriter();

    void logFunction( const std::string& name )
    {
        logFunctionHelper( name );
        logArguments();
    }

    template <typename A1>
    void logFunction( const std::string& name, const A1& arg1 )
    {
         logFunctionHelper( name );
         logArguments(
             Test::ArgumentTraitsBaseType<A1>::forLogOutput( arg1 )
         );
    }

    template <typename A1, typename A2>
    void logFunction( const std::string& name, const A1& arg1, const A2& arg2 )
    {
        logFunctionHelper( name );
        logArguments(
            Test::ArgumentTraitsBaseType<A1>::forLogOutput( arg1 ),
            Test::ArgumentTraitsBaseType<A2>::forLogOutput( arg2 )
        );
    }

    template <typename A1, typename A2, typename A3>
    void logFunction( const std::string& name, const A1& arg1, const A2& arg2, const A3& arg3 )
    {
        logFunctionHelper( name );
        logArguments(
            Test::ArgumentTraitsBaseType<A1>::forLogOutput( arg1 ),
            Test::ArgumentTraitsBaseType<A2>::forLogOutput( arg2 ),
            Test::ArgumentTraitsBaseType<A3>::forLogOutput( arg3 )
        );
    }

    template <typename A1, typename A2, typename A3, typename A4>
    void logFunction( const std::string& name, const A1& arg1, const A2& arg2, const A3& arg3, const A4& arg4 )
    {
        logFunctionHelper( name );
        logArguments(
            Test::ArgumentTraitsBaseType<A1>::forLogOutput( arg1 ),
            Test::ArgumentTraitsBaseType<A2>::forLogOutput( arg2 ),
            Test::ArgumentTraitsBaseType<A3>::forLogOutput( arg3 ),
            Test::ArgumentTraitsBaseType<A4>::forLogOutput( arg4 )
        );
    }

    template <typename A1, typename A2, typename A3, typename A4, typename A5>
    void logFunction( const std::string& name, const A1& arg1, const A2& arg2, const A3& arg3, const A4& arg4, const A5& arg5 )
    {
        logFunctionHelper( name );
        logArguments(
            Test::ArgumentTraitsBaseType<A1>::forLogOutput( arg1 ),
            Test::ArgumentTraitsBaseType<A2>::forLogOutput( arg2 ),
            Test::ArgumentTraitsBaseType<A3>::forLogOutput( arg3 ),
            Test::ArgumentTraitsBaseType<A4>::forLogOutput( arg4 ),
            Test::ArgumentTraitsBaseType<A5>::forLogOutput( arg5 )
        );
    }

    template <typename A1, typename A2, typename A3, typename A4, typename A5, typename A6>
    void logFunction( const std::string& name, const A1& arg1, const A2& arg2, const A3& arg3, const A4& arg4, const A5& arg5, const A6& arg6 )
    {
        logFunctionHelper( name );
        logArguments(
            Test::ArgumentTraitsBaseType<A1>::forLogOutput( arg1 ),
            Test::ArgumentTraitsBaseType<A2>::forLogOutput( arg2 ),
            Test::ArgumentTraitsBaseType<A3>::forLogOutput( arg3 ),
            Test::ArgumentTraitsBaseType<A4>::forLogOutput( arg4 ),
            Test::ArgumentTraitsBaseType<A5>::forLogOutput( arg5 ),
            Test::ArgumentTraitsBaseType<A6>::forLogOutput( arg6 )
        );
    }

    template <typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7>
    void logFunction( const std::string& name, const A1& arg1, const A2& arg2, const A3& arg3, const A4& arg4, const A5& arg5, const A6& arg6, const A7& arg7 )
    {
        logFunctionHelper( name );
        logArguments(
            Test::ArgumentTraitsBaseType<A1>::forLogOutput( arg1 ),
            Test::ArgumentTraitsBaseType<A2>::forLogOutput( arg2 ),
            Test::ArgumentTraitsBaseType<A3>::forLogOutput( arg3 ),
            Test::ArgumentTraitsBaseType<A4>::forLogOutput( arg4 ),
            Test::ArgumentTraitsBaseType<A5>::forLogOutput( arg5 ),
            Test::ArgumentTraitsBaseType<A6>::forLogOutput( arg6 ),
            Test::ArgumentTraitsBaseType<A7>::forLogOutput( arg7 )
        );
    }

    template <typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8>
    void logFunction( const std::string& name, const A1& arg1, const A2& arg2, const A3& arg3, const A4& arg4, const A5& arg5, const A6& arg6, const A7& arg7, const A8& arg8 )
    {
        logFunctionHelper( name );
        logArguments(
            Test::ArgumentTraitsBaseType<A1>::forLogOutput( arg1 ),
            Test::ArgumentTraitsBaseType<A2>::forLogOutput( arg2 ),
            Test::ArgumentTraitsBaseType<A3>::forLogOutput( arg3 ),
            Test::ArgumentTraitsBaseType<A4>::forLogOutput( arg4 ),
            Test::ArgumentTraitsBaseType<A5>::forLogOutput( arg5 ),
            Test::ArgumentTraitsBaseType<A6>::forLogOutput( arg6 ),
            Test::ArgumentTraitsBaseType<A7>::forLogOutput( arg7 ),
            Test::ArgumentTraitsBaseType<A8>::forLogOutput( arg8 )
        );
    }

    template <typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9>
    void logFunction( const std::string& name, const A1& arg1, const A2& arg2, const A3& arg3, const A4& arg4, const A5& arg5, const A6& arg6, const A7& arg7, const A8& arg8, const A9& arg9 )
    {
        logFunctionHelper( name );
        logArguments(
            Test::ArgumentTraitsBaseType<A1>::forLogOutput( arg1 ),
            Test::ArgumentTraitsBaseType<A2>::forLogOutput( arg2 ),
            Test::ArgumentTraitsBaseType<A3>::forLogOutput( arg3 ),
            Test::ArgumentTraitsBaseType<A4>::forLogOutput( arg4 ),
            Test::ArgumentTraitsBaseType<A5>::forLogOutput( arg5 ),
            Test::ArgumentTraitsBaseType<A6>::forLogOutput( arg6 ),
            Test::ArgumentTraitsBaseType<A7>::forLogOutput( arg7 ),
            Test::ArgumentTraitsBaseType<A8>::forLogOutput( arg8 ),
            Test::ArgumentTraitsBaseType<A9>::forLogOutput( arg9 )
        );
    }

    template <typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10>
    void logFunction( const std::string& name, const A1& arg1, const A2& arg2, const A3& arg3, const A4& arg4, const A5& arg5, const A6& arg6, const A7& arg7, const A8& arg8, const A9& arg9, const A10& arg10 )
    {
        logFunctionHelper( name );
        logArguments(
            Test::ArgumentTraitsBaseType<A1>::forLogOutput( arg1 ),
            Test::ArgumentTraitsBaseType<A2>::forLogOutput( arg2 ),
            Test::ArgumentTraitsBaseType<A3>::forLogOutput( arg3 ),
            Test::ArgumentTraitsBaseType<A4>::forLogOutput( arg4 ),
            Test::ArgumentTraitsBaseType<A5>::forLogOutput( arg5 ),
            Test::ArgumentTraitsBaseType<A6>::forLogOutput( arg6 ),
            Test::ArgumentTraitsBaseType<A7>::forLogOutput( arg7 ),
            Test::ArgumentTraitsBaseType<A8>::forLogOutput( arg8 ),
            Test::ArgumentTraitsBaseType<A9>::forLogOutput( arg9 ),
            Test::ArgumentTraitsBaseType<A10>::forLogOutput( arg10 )
        );
    }

    template <typename C>
    void logMethod( const C* instance, const std::string& method)
    {
        logMethodHelper( instanceName( instance ), method );
        logArguments();
    }

    template <typename C, typename A1>
    void logMethod( const C* instance, const std::string& method, const A1& arg1)
    {
        logMethodHelper( instanceName( instance ), method );
        logArguments(
            Test::ArgumentTraitsBaseType<A1>::forLogOutput( arg1 )
        );
    }

    template <typename C, typename A1, typename A2>
    void logMethod( const C* instance, const std::string& method, const A1& arg1, const A2& arg2 )
    {
        logMethodHelper( instanceName( instance ), method );
        logArguments(
            Test::ArgumentTraitsBaseType<A1>::forLogOutput( arg1 ),
            Test::ArgumentTraitsBaseType<A2>::forLogOutput( arg2 )
        );
    }

    template <typename C, typename A1, typename A2, typename A3>
    void logMethod( const C* instance, const std::string& method, const A1& arg1, const A2& arg2, const A3& arg3 )
    {
        logMethodHelper( instanceName( instance ), method );
        logArguments(
            Test::ArgumentTraitsBaseType<A1>::forLogOutput( arg1 ),
            Test::ArgumentTraitsBaseType<A2>::forLogOutput( arg2 ),
            Test::ArgumentTraitsBaseType<A3>::forLogOutput( arg3 )
        );
    }

    template <typename C, typename A1, typename A2, typename A3, typename A4>
    void logMethod( const C* instance, const std::string& method, const A1& arg1, const A2& arg2, const A3& arg3, const A4& arg4 )
    {
        logMethodHelper( instanceName( instance ), method );
        logArguments(
            Test::ArgumentTraitsBaseType<A1>::forLogOutput( arg1 ),
            Test::ArgumentTraitsBaseType<A2>::forLogOutput( arg2 ),
            Test::ArgumentTraitsBaseType<A3>::forLogOutput( arg3 ),
            Test::ArgumentTraitsBaseType<A4>::forLogOutput( arg4 )
        );
    }

    template <typename C, typename A1, typename A2, typename A3, typename A4, typename A5>
    void logMethod( const C* instance, const std::string& method, const A1& arg1, const A2& arg2, const A3& arg3, const A4& arg4, const A5& arg5 )
    {
        logMethodHelper( instanceName( instance ), method );
        logArguments(
            Test::ArgumentTraitsBaseType<A1>::forLogOutput( arg1 ),
            Test::ArgumentTraitsBaseType<A2>::forLogOutput( arg2 ),
            Test::ArgumentTraitsBaseType<A3>::forLogOutput( arg3 ),
            Test::ArgumentTraitsBaseType<A4>::forLogOutput( arg4 ),
            Test::ArgumentTraitsBaseType<A5>::forLogOutput( arg5 )
        );
    }

    template <typename C, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6>
    void logMethod( const C* instance, const std::string& method, const A1& arg1, const A2& arg2, const A3& arg3, const A4& arg4, const A5& arg5, const A6& arg6 )
    {
        logMethodHelper( instanceName( instance ), method );
        logArguments(
            Test::ArgumentTraitsBaseType<A1>::forLogOutput( arg1 ),
            Test::ArgumentTraitsBaseType<A2>::forLogOutput( arg2 ),
            Test::ArgumentTraitsBaseType<A3>::forLogOutput( arg3 ),
            Test::ArgumentTraitsBaseType<A4>::forLogOutput( arg4 ),
            Test::ArgumentTraitsBaseType<A5>::forLogOutput( arg5 ),
            Test::ArgumentTraitsBaseType<A6>::forLogOutput( arg6 )
        );
    }

    template <typename C, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7>
    void logMethod( const C* instance, const std::string& method, const A1& arg1, const A2& arg2, const A3& arg3, const A4& arg4, const A5& arg5, const A6& arg6, const A7& arg7 )
    {
        logMethodHelper( instanceName( instance ), method );
        logArguments(
            Test::ArgumentTraitsBaseType<A1>::forLogOutput( arg1 ),
            Test::ArgumentTraitsBaseType<A2>::forLogOutput( arg2 ),
            Test::ArgumentTraitsBaseType<A3>::forLogOutput( arg3 ),
            Test::ArgumentTraitsBaseType<A4>::forLogOutput( arg4 ),
            Test::ArgumentTraitsBaseType<A5>::forLogOutput( arg5 ),
            Test::ArgumentTraitsBaseType<A6>::forLogOutput( arg6 ),
            Test::ArgumentTraitsBaseType<A7>::forLogOutput( arg7 )
        );
    }

    template <typename C, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8>
    void logMethod( const C* instance, const std::string& method, const A1& arg1, const A2& arg2, const A3& arg3, const A4& arg4, const A5& arg5, const A6& arg6, const A7& arg7, const A8& arg8 )
    {
        logMethodHelper( instanceName( instance ), method );
        logArguments(
            Test::ArgumentTraitsBaseType<A1>::forLogOutput( arg1 ),
            Test::ArgumentTraitsBaseType<A2>::forLogOutput( arg2 ),
            Test::ArgumentTraitsBaseType<A3>::forLogOutput( arg3 ),
            Test::ArgumentTraitsBaseType<A4>::forLogOutput( arg4 ),
            Test::ArgumentTraitsBaseType<A5>::forLogOutput( arg5 ),
            Test::ArgumentTraitsBaseType<A6>::forLogOutput( arg6 ),
            Test::ArgumentTraitsBaseType<A7>::forLogOutput( arg7 ),
            Test::ArgumentTraitsBaseType<A8>::forLogOutput( arg8 )
        );
    }

    template <typename C, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9>
    void logMethod( const C* instance, const std::string& method, const A1& arg1, const A2& arg2, const A3& arg3, const A4& arg4, const A5& arg5, const A6& arg6, const A7& arg7, const A8& arg8, const A9& arg9 )
    {
        logMethodHelper( instanceName( instance ), method );
        logArguments(
            Test::ArgumentTraitsBaseType<A1>::forLogOutput( arg1 ),
            Test::ArgumentTraitsBaseType<A2>::forLogOutput( arg2 ),
            Test::ArgumentTraitsBaseType<A3>::forLogOutput( arg3 ),
            Test::ArgumentTraitsBaseType<A4>::forLogOutput( arg4 ),
            Test::ArgumentTraitsBaseType<A5>::forLogOutput( arg5 ),
            Test::ArgumentTraitsBaseType<A6>::forLogOutput( arg6 ),
            Test::ArgumentTraitsBaseType<A7>::forLogOutput( arg7 ),
            Test::ArgumentTraitsBaseType<A8>::forLogOutput( arg8 ),
            Test::ArgumentTraitsBaseType<A9>::forLogOutput( arg9 )
        );
    }

    template <typename C, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10>
    void logMethod( const C* instance, const std::string& method, const A1& arg1, const A2& arg2, const A3& arg3, const A4& arg4, const A5& arg5, const A6& arg6, const A7& arg7, const A8& arg8, const A9& arg9, const A10& arg10 )
    {
        logMethodHelper( instanceName( instance ), method );
        logArguments(
            Test::ArgumentTraitsBaseType<A1>::forLogOutput( arg1 ),
            Test::ArgumentTraitsBaseType<A2>::forLogOutput( arg2 ),
            Test::ArgumentTraitsBaseType<A3>::forLogOutput( arg3 ),
            Test::ArgumentTraitsBaseType<A4>::forLogOutput( arg4 ),
            Test::ArgumentTraitsBaseType<A5>::forLogOutput( arg5 ),
            Test::ArgumentTraitsBaseType<A6>::forLogOutput( arg6 ),
            Test::ArgumentTraitsBaseType<A7>::forLogOutput( arg7 ),
            Test::ArgumentTraitsBaseType<A8>::forLogOutput( arg8 ),
            Test::ArgumentTraitsBaseType<A9>::forLogOutput( arg9 ),
            Test::ArgumentTraitsBaseType<A10>::forLogOutput( arg10 )
        );
    }

    template <typename C>
    void logConstructor( const std::string& constructor, const C* instance )
    {
        logMethodHelper( constructor, addInstanceName( instance ) );
        logArguments();
    }

    template <typename C, typename A1>
    void logConstructor( const std::string& constructor, const C* instance, const A1& arg1 )
    {
        logMethodHelper( constructor, addInstanceName( instance ) );
        logArguments(
            Test::ArgumentTraitsBaseType<A1>::forLogOutput( arg1 )
        );
    }

    template <typename C, typename A1, typename A2>
    void logConstructor( const std::string& constructor, const C* instance, const A1& arg1, const A2& arg2 )
    {
        logMethodHelper( constructor, addInstanceName( instance ) );
        logArguments(
            Test::ArgumentTraitsBaseType<A1>::forLogOutput( arg1 ),
            Test::ArgumentTraitsBaseType<A2>::forLogOutput( arg2 )
        );
    }

    template <typename C, typename A1, typename A2, typename A3>
    void logConstructor( const std::string& constructor, const C* instance, const A1& arg1, const A2& arg2, const A3& arg3 )
    {
        logMethodHelper( constructor, addInstanceName( instance ) );
        logArguments(
            Test::ArgumentTraitsBaseType<A1>::forLogOutput( arg1 ),
            Test::ArgumentTraitsBaseType<A2>::forLogOutput( arg2 ),
            Test::ArgumentTraitsBaseType<A3>::forLogOutput( arg3 )
        );
    }

    template <typename C, typename A1, typename A2, typename A3, typename A4>
    void logConstructor( const std::string& constructor, const C* instance, const A1& arg1, const A2& arg2, const A3& arg3, const A4& arg4 )
    {
        logMethodHelper( constructor, addInstanceName( instance ) );
        logArguments(
            Test::ArgumentTraitsBaseType<A1>::forLogOutput( arg1 ),
            Test::ArgumentTraitsBaseType<A2>::forLogOutput( arg2 ),
            Test::ArgumentTraitsBaseType<A3>::forLogOutput( arg3 ),
            Test::ArgumentTraitsBaseType<A4>::forLogOutput( arg4 )
        );
    }

    template <typename C, typename A1, typename A2, typename A3, typename A4, typename A5>
    void logConstructor( const std::string& constructor, const C* instance, const A1& arg1, const A2& arg2, const A3& arg3, const A4& arg4, const A5& arg5 )
    {
        logMethodHelper( constructor, addInstanceName( instance ) );
        logArguments(
            Test::ArgumentTraitsBaseType<A1>::forLogOutput( arg1 ),
            Test::ArgumentTraitsBaseType<A2>::forLogOutput( arg2 ),
            Test::ArgumentTraitsBaseType<A3>::forLogOutput( arg3 ),
            Test::ArgumentTraitsBaseType<A4>::forLogOutput( arg4 ),
            Test::ArgumentTraitsBaseType<A5>::forLogOutput( arg5 )
        );
    }

    template <typename C, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6>
    void logConstructor( const std::string& constructor, const C* instance, const A1& arg1, const A2& arg2, const A3& arg3, const A4& arg4, const A5& arg5, const A6& arg6 )
    {
        logMethodHelper( constructor, addInstanceName( instance ) );
        logArguments(
            Test::ArgumentTraitsBaseType<A1>::forLogOutput( arg1 ),
            Test::ArgumentTraitsBaseType<A2>::forLogOutput( arg2 ),
            Test::ArgumentTraitsBaseType<A3>::forLogOutput( arg3 ),
            Test::ArgumentTraitsBaseType<A4>::forLogOutput( arg4 ),
            Test::ArgumentTraitsBaseType<A5>::forLogOutput( arg5 ),
            Test::ArgumentTraitsBaseType<A6>::forLogOutput( arg6 )
        );
    }

    template <typename C, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7>
    void logConstructor( const std::string& constructor, const C* instance, const A1& arg1, const A2& arg2, const A3& arg3, const A4& arg4, const A5& arg5, const A6& arg6, const A7& arg7 )
    {
        logMethodHelper( constructor, addInstanceName( instance ) );
        logArguments(
            Test::ArgumentTraitsBaseType<A1>::forLogOutput( arg1 ),
            Test::ArgumentTraitsBaseType<A2>::forLogOutput( arg2 ),
            Test::ArgumentTraitsBaseType<A3>::forLogOutput( arg3 ),
            Test::ArgumentTraitsBaseType<A4>::forLogOutput( arg4 ),
            Test::ArgumentTraitsBaseType<A5>::forLogOutput( arg5 ),
            Test::ArgumentTraitsBaseType<A6>::forLogOutput( arg6 ),
            Test::ArgumentTraitsBaseType<A7>::forLogOutput( arg7 )
        );
    }

    template <typename C, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8>
    void logConstructor( const std::string& constructor, const C* instance, const A1& arg1, const A2& arg2, const A3& arg3, const A4& arg4, const A5& arg5, const A6& arg6, const A7& arg7, const A8& arg8 )
    {
        logMethodHelper( constructor, addInstanceName( instance ) );
        logArguments(
            Test::ArgumentTraitsBaseType<A1>::forLogOutput( arg1 ),
            Test::ArgumentTraitsBaseType<A2>::forLogOutput( arg2 ),
            Test::ArgumentTraitsBaseType<A3>::forLogOutput( arg3 ),
            Test::ArgumentTraitsBaseType<A4>::forLogOutput( arg4 ),
            Test::ArgumentTraitsBaseType<A5>::forLogOutput( arg5 ),
            Test::ArgumentTraitsBaseType<A6>::forLogOutput( arg6 ),
            Test::ArgumentTraitsBaseType<A7>::forLogOutput( arg7 ),
            Test::ArgumentTraitsBaseType<A8>::forLogOutput( arg8 )
        );
    }

    template <typename C, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9>
    void logConstructor( const std::string& constructor, const C* instance, const A1& arg1, const A2& arg2, const A3& arg3, const A4& arg4, const A5& arg5, const A6& arg6, const A7& arg7, const A8& arg8, const A9& arg9 )
    {
        logMethodHelper( constructor, addInstanceName( instance ) );
        logArguments(
            Test::ArgumentTraitsBaseType<A1>::forLogOutput( arg1 ),
            Test::ArgumentTraitsBaseType<A2>::forLogOutput( arg2 ),
            Test::ArgumentTraitsBaseType<A3>::forLogOutput( arg3 ),
            Test::ArgumentTraitsBaseType<A4>::forLogOutput( arg4 ),
            Test::ArgumentTraitsBaseType<A5>::forLogOutput( arg5 ),
            Test::ArgumentTraitsBaseType<A6>::forLogOutput( arg6 ),
            Test::ArgumentTraitsBaseType<A7>::forLogOutput( arg7 ),
            Test::ArgumentTraitsBaseType<A8>::forLogOutput( arg8 ),
            Test::ArgumentTraitsBaseType<A9>::forLogOutput( arg9 )
        );
    }

    template <typename C, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10>
    void logConstructor( const std::string& constructor, const C* instance, const A1& arg1, const A2& arg2, const A3& arg3, const A4& arg4, const A5& arg5, const A6& arg6, const A7& arg7, const A8& arg8, const A9& arg9, const A10& arg10 )
    {
        logMethodHelper( constructor, addInstanceName( instance ) );
        logArguments(
            Test::ArgumentTraitsBaseType<A1>::forLogOutput( arg1 ),
            Test::ArgumentTraitsBaseType<A2>::forLogOutput( arg2 ),
            Test::ArgumentTraitsBaseType<A3>::forLogOutput( arg3 ),
            Test::ArgumentTraitsBaseType<A4>::forLogOutput( arg4 ),
            Test::ArgumentTraitsBaseType<A5>::forLogOutput( arg5 ),
            Test::ArgumentTraitsBaseType<A6>::forLogOutput( arg6 ),
            Test::ArgumentTraitsBaseType<A7>::forLogOutput( arg7 ),
            Test::ArgumentTraitsBaseType<A8>::forLogOutput( arg8 ),
            Test::ArgumentTraitsBaseType<A9>::forLogOutput( arg9 ),
            Test::ArgumentTraitsBaseType<A10>::forLogOutput( arg10 )
        );
    }

private:
    void logFunctionHelper( const std::string& name );
    void logMethodHelper( const std::string& instance, const std::string& method );
    void logConstructorHelper( const std::string& constructor, const std::string& instance );
    void logStartArguments();
    void logEndArguments();
    void logArguments();
    void logArguments( const std::string& arg1 );
    void logArguments( const std::string& arg1, const std::string& arg2 );
    void logArguments( const std::string& arg1, const std::string& arg2, const std::string& arg3 );
    void logArguments( const std::string& arg1, const std::string& arg2, const std::string& arg3, const std::string& arg4 );
    void logArguments( const std::string& arg1, const std::string& arg2, const std::string& arg3, const std::string& arg4, const std::string& arg5 );
    void logArguments( const std::string& arg1, const std::string& arg2, const std::string& arg3, const std::string& arg4, const std::string& arg5, const std::string& arg6 );
    void logArguments( const std::string& arg1, const std::string& arg2, const std::string& arg3, const std::string& arg4, const std::string& arg5, const std::string& arg6, const std::string& arg7 );
    void logArguments( const std::string& arg1, const std::string& arg2, const std::string& arg3, const std::string& arg4, const std::string& arg5, const std::string& arg6, const std::string& arg7, const std::string& arg8 );
    void logArguments( const std::string& arg1, const std::string& arg2, const std::string& arg3, const std::string& arg4, const std::string& arg5, const std::string& arg6, const std::string& arg7, const std::string& arg8, const std::string& arg9 );
    void logArguments( const std::string& arg1, const std::string& arg2, const std::string& arg3, const std::string& arg4, const std::string& arg5, const std::string& arg6, const std::string& arg7, const std::string& arg8, const std::string& arg9, const std::string& arg10 );

    const std::string& instanceName( const void* instance ) const;
    const std::string& addInstance( const void* instance );

    std::ostream& mStream;
    std::auto_ptr<std::ostream> mStreamOwnership;

    typedef std::map<const void*, std::string> InstanceNameMap;
    InstanceNameMap mInstanceMap;
};

#endif

#endif /* TESTLOGWRITER_H__INCLUDED */
