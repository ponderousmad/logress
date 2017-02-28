/* ---------------------------------------------------------------
 * Copyright (c) Adrian Smith.
 * Licensed under the MIT license. See license.txt at project root.
 * --------------------------------------------------------------- */
#include "Base/Top.h"

#include "Test/TestLogWriter.h"
#include "Base/BaseAssert.h"

using Test::LogWriter;

LogWriter::LogWriter( std::ostream& stream )
    : mStream( stream )
{
}

LogWriter::LogWriter( std::auto_ptr<std::ostream> stream )
    : mStream( *stream )
    , mStreamOwnership( stream )
{
}

LogWriter::~LogWriter()
{
}


void LogWriter::logFunctionHelper( const std::string& name )
{
    mStream << Test::LogFormat::kFunctionCallSymbol << name;
}

void LogWriter::logMethodHelper( const std::string& instance, const std::string& method )
{
    mStream << Test::LogFormat::kMethodCallSymbol << instance << Test::LogFormat::kMethodIndexSymbol << method;
}

void LogWriter::logConstructorHelper( const std::string& constructor, const std::string& instance )
{
    mStream << Test::LogFormat::kConstructorSymbol << constructor << Test::LogFormat::kObjectIDSymbol << instance;
}

void LogWriter::logStartArguments()
{
    mStream << Test::LogFormat::kOpenArgumentListSymbol;
}

void LogWriter::logEndArguments()
{
    mStream << Test::LogFormat::kCloseArgumentListSymbol << std::endl;
}

void LogWriter::logArguments()
{
    logStartArguments();
    logEndArguments();
}

void LogWriter::logArguments( const std::string& arg1 )
{
    logStartArguments();
    mStream << " " << arg1 << " ";
}

void LogWriter::logArguments( const std::string& arg1, const std::string& arg2 )
{
    logStartArguments();
    mStream << " " << arg1 << ", " << arg2 << " ";
}

void LogWriter::logArguments( const std::string& arg1, const std::string& arg2, const std::string& arg3 )
{
    logStartArguments();
    mStream << " " << arg1 << ", " << arg2 << ", " << arg3 << " ";
}

void LogWriter::logArguments( const std::string& arg1, const std::string& arg2, const std::string& arg3, const std::string& arg4 )
{
    logStartArguments();
    mStream << " " << arg1 << ", " << arg2 << ", " << arg3 << ", " << arg4 << " ";
}

void LogWriter::logArguments( const std::string& arg1, const std::string& arg2, const std::string& arg3, const std::string& arg4, const std::string& arg5 )
{
    logStartArguments();
    mStream << " " << arg1 << ", " << arg2 << ", " << arg3 << ", " << arg4 << ", " << arg5 << " ";
}

void LogWriter::logArguments( const std::string& arg1, const std::string& arg2, const std::string& arg3, const std::string& arg4, const std::string& arg5, const std::string& arg6 )
{
    logStartArguments();
    mStream << " " << arg1 << ", " << arg2 << ", " << arg3 << ", " << arg4 << ", " << arg5 << ", " << arg6 << " ";
}

void LogWriter::logArguments( const std::string& arg1, const std::string& arg2, const std::string& arg3, const std::string& arg4, const std::string& arg5, const std::string& arg6, const std::string& arg7 )
{
    logStartArguments();
    mStream << " " << arg1 << ", " << arg2 << ", " << arg3 << ", " << arg4 << ", " << arg5 << ", " << arg6 << ", " << arg7 << " ";
}

void LogWriter::logArguments( const std::string& arg1, const std::string& arg2, const std::string& arg3, const std::string& arg4, const std::string& arg5, const std::string& arg6, const std::string& arg7, const std::string& arg8 )
{
    logStartArguments();
    mStream << " " << arg1 << ", " << arg2 << ", " << arg3 << ", " << arg4 << ", " << arg5 << ", " << arg6 << ", " << arg7 << ", " << arg8 << " ";
}

void LogWriter::logArguments( const std::string& arg1, const std::string& arg2, const std::string& arg3, const std::string& arg4, const std::string& arg5, const std::string& arg6, const std::string& arg7, const std::string& arg8, const std::string& arg9 )
{
    logStartArguments();
    mStream << " " << arg1 << ", " << arg2 << ", " << arg3 << ", " << arg4 << ", " << arg5 << ", " << arg6 << ", " << arg7 << ", " << arg8 << ", " << arg9 << " ";
}

void LogWriter::logArguments( const std::string& arg1, const std::string& arg2, const std::string& arg3, const std::string& arg4, const std::string& arg5, const std::string& arg6, const std::string& arg7, const std::string& arg8, const std::string& arg9, const std::string& arg10 )
{
    logStartArguments();
    mStream << " " << arg1 << ", " << arg2 << ", " << arg3 << ", " << arg4 << ", " << arg5 << ", " << arg6 << ", " << arg7 << ", " << arg8 << ", " << arg9 << ", " << arg10 << " ";
}

const std::string& LogWriter::instanceName( const void* instance ) const
{
    InstanceNameMap::const_iterator it = mInstanceMap.find( instance );
    ASSERT( it != mInstanceMap.end() );
    return it->second;
}

const std::string& LogWriter::addInstance( const void* instance )
{
    std::string name = "p" + String::make( static_cast<int>(reinterpret_cast<intptr_t>(instance)) );
    InstanceNameMap::iterator it = mInstanceMap.find( instance );
    if( it != mInstanceMap.end() )
    {
        name = it->second + "N";
    }

    std::string& value = mInstanceMap[instance];
    value = name;
    return value;
}
