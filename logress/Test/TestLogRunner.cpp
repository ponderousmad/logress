/* ---------------------------------------------------------------
 * Copyright (c) Adrian Smith.
 * Licensed under the MIT license. See license.txt at project root.
 * --------------------------------------------------------------- */
#include "Base/Top.h"

#include "Test/TestLogRunner.h"
#include "Test/TestInvokeContext.h"
#include "Test/TestEnvironment.h"
#include "Test/TestBase.h"
#include "Memory/MemoryShared.h"
#include "Base/BaseAssert.h"

#include <map>
#include <iostream>
#include <sstream>
#include <fstream>
#include <memory>
#include "assert.h"

using Test::LogRunner;
using std::string;

LogRunner::LogRunner()
{
}

LogRunner::~LogRunner()
{
}

namespace
{
    class Invocation
    {
    public:
        virtual Test::InvokeResult invoke( Test::Environment& environment ) = 0;
        virtual ~Invocation() {}
    };

    class FunctionInvocation : public Invocation
    {
    private:
        Test::ConstFunctionH mFunction;
        string mArguments;
    public:
        FunctionInvocation( Test::ConstFunctionH function, const string& arguments )
            : mFunction( function )
            , mArguments( arguments )
        {
        }

        ~FunctionInvocation() {}

        Test::InvokeResult invoke (Test::Environment& environment )
        {
            Test::InvokeContext context( mArguments, environment );
            return mFunction->invoke( context );
        }
    };

    class MethodInvocation : public Invocation
    {
    private:
        Test::ObjectH mObject;
        string mMethodName;
        string mArguments;
    public:
        MethodInvocation( Test::ObjectH object, const string& methodName, const string& arguments )
            : mObject( object )
            , mMethodName( methodName )
            , mArguments( arguments )
        {
        }

        ~MethodInvocation() {}

        Test::InvokeResult invoke( Test::Environment& environment )
        {
            Test::InvokeContext context( mArguments, environment );
            return mObject->invoke( mMethodName, context );
        }
    };

    class ConstructorInvocation : public Invocation
    {
    private:
        Test::ConstObjectFactoryH mFactory;
        string mArguments;
        string mID;
    public:
        ConstructorInvocation( Test::ConstObjectFactoryH factory, const string& arguments, const string& id )
            : mFactory( factory )
            , mArguments( arguments )
            , mID( id )
        {
        }

        ~ConstructorInvocation() {}

        Test::InvokeResult invoke( Test::Environment& environment )
        {
            Test::InvokeContext context( mArguments, environment );
            Test::IObjectFactory::Result result = mFactory->construct( context );
            if( result.first == Test::InvokeResult::kSuccess )
            {
                environment.add( result.second, mID );
            }
            return Test::InvokeResult( result.first );
        }
    };

    class ParsedLine
    {
        PREVENT_COPY_AND_ASSIGNMENT( ParsedLine );
    public:
        ParsedLine( const string& returnValue )
            : mIsInvocation( false )
            , mReturnValue( returnValue )
        {
        }

        ParsedLine( std::auto_ptr<Invocation> invocation )
            : mIsInvocation( true )
            , mInvocation( invocation )
        {
        }

        bool isInvocation() const
        {
            return mIsInvocation;
        }

        bool isReturnValue() const
        {
            return !mIsInvocation;
        }

        const string& returnValue() const
        {
            ASSERT( isReturnValue() );
            return mReturnValue;
        }

        bool execute( Test::Environment& environment, const string& returnValueTarget )
        {
            ASSERT( isInvocation() );
            ASSERT( mInvocation.get() );

            Test::InvokeResult result = mInvocation->invoke( environment );
            return result.check( returnValueTarget, environment );
        }

    private:
        bool mIsInvocation;
        std::auto_ptr<Invocation> mInvocation;
        string mReturnValue;
    };

    std::auto_ptr<ParsedLine> buildParsedLine( Invocation* invocation )
    {
        return std::auto_ptr<ParsedLine>( new ParsedLine( std::auto_ptr<Invocation>(invocation) ) );
    }

    string readLine( std::istream& stream )
    {
        std::ostringstream lineStream;
        const unsigned int kMaxLineLength = 4096;
        char line[ kMaxLineLength + 1 ];

        line[kMaxLineLength] = '\0';

        size_t read;
        do
        {
            stream.getline( line, kMaxLineLength );
            read = strlen( line );
            lineStream << line;
        } while( kMaxLineLength == read );
        return lineStream.str();
    }

    const char kConstructorSymbol = '#';
    const char kMethodCallSymbol = '^';
    const char kFunctionCallSymbol = '!';
    const char kResultSymbol = '=';
    const char kObjectIDSymbol = '~';
    const char kMethodIndexSymbol = '.';
    const char kOpenArgumentListSymbol = '(';
    const char kCloseArgumentListSymbol = ')';
    const string::size_type kSigilOffset = 1;
    const string::size_type kObjectIDOffset = 1;
    const string::size_type kMethodIndexOffset = 1;
    const string::size_type kArgumentListOffset = 1;

    std::auto_ptr<ParsedLine> parseFunction(const string& line, Test::Environment& environment)
    {
        string::size_type functionNameEnd = line.find( kOpenArgumentListSymbol, kSigilOffset );
        if( functionNameEnd != line.npos )
        {
            string functionName = line.substr( kSigilOffset, functionNameEnd - kSigilOffset );
            Test::ConstFunctionH function = environment.findFunction( functionName );
            if( !function.isNull() )
            {
                string::size_type argumentListEnd = line.find( kCloseArgumentListSymbol, functionNameEnd + kArgumentListOffset );
                if( argumentListEnd != line.npos )
                {
                    string arguments = line.substr( functionNameEnd + kArgumentListOffset, argumentListEnd - functionNameEnd - kArgumentListOffset );
                    return buildParsedLine( new FunctionInvocation( function, arguments ) );
                }
            }
        }
        return std::auto_ptr<ParsedLine>();
    }

    std::auto_ptr<ParsedLine> parseConstruction(const string& line, Test::Environment& environment)
    {
        string::size_type constructorNameEnd = line.find( kObjectIDSymbol, kSigilOffset );
        if( constructorNameEnd != line.npos )
        {
            string constructorName = line.substr( kSigilOffset, constructorNameEnd - kSigilOffset );
            Test::ConstObjectFactoryH factory = environment.findFactory( constructorName );
            if( !factory.isNull() )
            {
                string::size_type idEnd = line.find( kOpenArgumentListSymbol, constructorNameEnd + kObjectIDOffset );
                if( idEnd != line.npos )
                {
                    string id = line.substr( constructorNameEnd + kObjectIDOffset, idEnd - constructorNameEnd - kObjectIDOffset );
                    string::size_type argumentListEnd = line.find( kCloseArgumentListSymbol, idEnd + kArgumentListOffset );
                    if( argumentListEnd != line.npos )
                    {
                        string arguments = line.substr( idEnd + kArgumentListOffset, argumentListEnd - idEnd - kArgumentListOffset );
                        return buildParsedLine( new ConstructorInvocation( factory, arguments, id ) );
                    }
                }
            }
        }
        return std::auto_ptr<ParsedLine>();
    }

    std::auto_ptr<ParsedLine> parseMethodCall(const string& line, Test::Environment& environment)
    {
        string::size_type objectNameEnd = line.find( kMethodIndexSymbol, kSigilOffset );
        if( objectNameEnd != line.npos )
        {
            string name = line.substr( kSigilOffset, objectNameEnd - kSigilOffset );
            Test::ObjectH object = environment.findObject( name );

            string::size_type methodNameEnd = line.find( kOpenArgumentListSymbol, objectNameEnd + kMethodIndexOffset );
            if( methodNameEnd != line.npos )
            {
                string method = line.substr( objectNameEnd + kMethodIndexOffset, methodNameEnd - objectNameEnd - kMethodIndexOffset );
                if( object->hasMethod( method ) )
                {
                    string::size_type argumentListEnd = line.find( kCloseArgumentListSymbol, methodNameEnd + kArgumentListOffset );
                    if( argumentListEnd != line.npos )
                    {
                        string arguments = line.substr( methodNameEnd + kArgumentListOffset, argumentListEnd - methodNameEnd - kArgumentListOffset );
                        return buildParsedLine( new MethodInvocation( object, method, arguments ) );
                    }
                }
            }
        }
        return std::auto_ptr<ParsedLine>();
    }

    std::auto_ptr<ParsedLine> parseResult(const string& line)
    {
        return std::auto_ptr<ParsedLine>( new ParsedLine( line.substr(1) ) );
    }

    std::auto_ptr<ParsedLine> parseLine( const string& line, Test::Environment& environment )
    {
        if( !line.empty() )
        {
            switch( line[0] )
            {
            case kFunctionCallSymbol:
                return parseFunction( line, environment );
            case kConstructorSymbol:
                return parseConstruction( line, environment );
            case kMethodCallSymbol:
                return parseMethodCall( line, environment );
            case kResultSymbol:
                return parseResult( line );
            }
        }
        return std::auto_ptr<ParsedLine>();
    }


}

bool LogRunner::runTest( const char* testFile, Test::Environment& environment )
{

    std::ifstream file( testFile );
    return runTest( file, environment );
}

bool LogRunner::runTest( std::istream& file, Test::Environment& environment )
{
    std::auto_ptr<ParsedLine> lastLine;

    while( file.good() && !file.eof() )
    {
        string line( readLine( file ) );

        if( lastLine.get() && lastLine->isInvocation() && line.length() > 0 && line[0] != kResultSymbol )
        {
            if( !lastLine->execute( environment, "" ) )
            {
                return false;
            }
            lastLine.reset();
        }
        std::auto_ptr<ParsedLine> parse = parseLine( line, environment );

        if( parse.get() )
        {
            if( lastLine.get() && lastLine->isInvocation() )
            {
                if( !lastLine->execute( environment, parse->isReturnValue() ? parse->returnValue() : "" ) )
                {
                    return false;
                }
            }
            if( parse->isReturnValue() )
            {
                parse.reset();
            }
            lastLine = parse;
        }
    }
    if( lastLine.get() && lastLine->isInvocation() )
    {
        return lastLine->execute( environment, "" );
    }
    return !lastLine.get();
}

#ifdef BUILD_TESTS

#include "UnitTest/UnitTestFramework.h"
#include "Test/TestObjectFactory.h"
#include "Test/TestObject.h"
#include "Test/TestFunction.h"
#include "MetaBase/MetaBaseTypeList.h"

namespace
{
    bool sWasInFoo = false;

    void foo(int a, int b, int c)
    {
        sWasInFoo = true;
    }

    class Bar
    {
    public:
        Bar( int intVal, double doubleVal, const string& stringVal )
            : mIntVal( intVal )
            , mDoubleVal( doubleVal )
            , mStringVal( stringVal )
        {
        }

        virtual ~Bar()
        {
        }

        int getInt() const { return mIntVal; }
        double getDouble() const { return mDoubleVal; }
        const string& getString() const { return mStringVal; }

        virtual double value() const { return mIntVal * mDoubleVal; }

        void setInt( int value ) { mIntVal = value; }

    private:
        int mIntVal;
        double mDoubleVal;
        string mStringVal;
    };

    class Baz : public Bar
    {
    public:
        Baz( int intVal, double doubleVal, float floatVal )
            : Bar( intVal, doubleVal, String::make( intVal ) )
            , mFloatVal( floatVal )
        {
        }

        ~Baz()
        {
        }

        float getFloat() const { return mFloatVal; }

        double value() const { return Bar::value() + mFloatVal; }
    private:
        float mFloatVal;
    };

    Test::Object<Bar>::ConstVTableH barTable()
    {
        VTABLE_DECLARE( Bar, v );
        VTABLE_ADD( v, getInt );
        VTABLE_ADD( v, getDouble );
        VTABLE_ADD( v, getString );
        VTABLE_ADD( v, value );
        return v;
    }

    Test::Object<Baz>::ConstVTableH bazTable()
    {
        VTABLE_DECLARE( Baz, v );
        VTABLE_ADD( v, getInt );
        VTABLE_ADD( v, getDouble );
        VTABLE_ADD( v, getString );
        VTABLE_ADD( v, value );
        VTABLE_ADD( v, getFloat );
        return v;
    }

    void addFactories( Test::Environment& env )
    {
        env.add( Test::ObjectFactory<Bar>::buildFactory< TYPELIST_3(int, double, const string&) >( barTable() ), "Bar" );
        env.add( Test::ObjectFactory<Baz>::buildFactory< TYPELIST_3(int, double, float) >( bazTable() ), "Baz" );
    }

    class TestLogRunnerTest : public UnitTest::Framework
    {
    public:
        void run()
        {
            RUN( functionTest );
            RUN( factoryTest );
            RUN( methodTest );
        }

        void functionTest()
        {
            Test::Environment environment;
            environment.add( Test::buildFunction( foo ), "foo" );

            std::ostringstream testLog;
            testLog << "!foo(1,2,3)" << std::endl;

            std::istringstream test( testLog.str() );
            LogRunner runner;
            CHECK( runner.runTest( test, environment ) );

            CHECK( sWasInFoo );
        }

        void factoryTest()
        {
            Test::Environment environment;
            addFactories( environment );

            std::ostringstream testLog;
            testLog << "#Bar~a(1,2,\"3\")" << std::endl;
            testLog << "#Baz~b(1, 2.5, 3.5)" << std::endl;

            std::istringstream test( testLog.str() );
            LogRunner runner;
            CHECK( runner.runTest( test, environment ) );

            CHECK( !environment.findObject("a").isNull() );
            CHECK( !environment.findObject("b").isNull() );
        }

        void methodTest()
        {
            Test::Environment environment;
            addFactories( environment );

            std::ostringstream testLog;
            testLog << "#Bar~a(1,2,\"3\")" << std::endl;
            testLog << "^a.value()" << std::endl;
            testLog << "=2" << std::endl;

            std::istringstream test( testLog.str() );
            LogRunner runner;
            CHECK( runner.runTest( test, environment ) );

            CHECK( !environment.findObject("a").isNull() );
        }
    };
}

DECLARE_TEST( TestLogRunnerTest );

#endif

