#include "Base/Top.h"

#ifdef OLD_PARSER

#include "Test/TestParser.h"
#include "FrontEnd/FrontEnd.h"
#include "String/StringUtils.h"
#include "Base/BaseLogger.h"
#include "Base/BaseStopwatch.h"
#include "Base/BaseTolerance.h"

#include <assert.h>
#include <map>
#include <string>
#include <list>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <stdio.h>

using Test::TestParser;

namespace {
    class Value
    {
        PREVENT_COPY_AND_ASSIGNMENT( Value );
    public:
        Value() {}
        virtual ~Value() {}
        virtual operator int() const { assert( !"No int cast" ); return 0; }
        virtual operator double() const { assert( !"No double cast" ); return 0.0; }
        virtual operator const char *() const { assert( !"No string cast" ); return 0; }

        virtual void set( const std::string & value ) = 0;
        virtual Value * clone() const = 0;
    };

    class IntValue : public Value
    {
        PREVENT_COPY_AND_ASSIGNMENT( IntValue );
    public:
        IntValue() : mValue( 0 ) {}
        IntValue( int value ) : mValue( value ) {}

        virtual operator int() const { return mValue; }
        virtual Value * clone() const { return new IntValue( mValue ); }
        virtual void set( const std::string & value ) {
            sscanf( value.c_str(), "%d", &mValue );
        }

    private:
        int mValue;
    };

    class DoubleValue : public Value
    {
        PREVENT_COPY_AND_ASSIGNMENT( DoubleValue );
    public:
        DoubleValue() : mValue( 0.0 ) {}
        DoubleValue( double value ) : mValue( value ) {}

        virtual operator double() const { return mValue; }
        virtual Value * clone() const { return new DoubleValue( mValue ); }
        virtual void set( const std::string & value ) {
            sscanf( value.c_str(), "%lf", &mValue );
        }

    private:
        double mValue;
    };

    class StringValue : public Value
    {
        PREVENT_COPY_AND_ASSIGNMENT( StringValue );
    public:
        StringValue() : mValue( "" ) {}
        StringValue( const std::string & value ) : mValue( value ) {}

        virtual operator const char *() const { return mValue.c_str(); }
        virtual Value * clone() const { return new StringValue( mValue ); }
        virtual void set( const std::string & value ) { mValue = value; }

    private:
        std::string mValue;
    };

    class Values
    {
    public:
        Values();
        Values( const Values & );
        Values& operator=( const Values & );
        ~Values();

        void swap( Values & other );

        void add( Value * arg );
        int size() const;
        bool empty() const;

        const Value & operator[]( int index ) const;
        Value & operator[]( int index );


    private:
        typedef std::vector<Value*> Container;
        Container mValues;
    };

    Values::Values()
    {
    }

    Values::Values( const Values & other )
    {
        Container::const_iterator it;
        for( it = other.mValues.begin(); it != other.mValues.end(); ++it ) {
            add( (**it).clone() );
        }
    }

    Values & Values::operator =( const Values & other )
    {
        Values temp( other );
        swap( temp );
        return *this;
    }

    Values::~Values()
    {
        for( Container::iterator it = mValues.begin(); it != mValues.end(); ++it ) {
            delete *it;
        }
        mValues.clear();
    }

    void Values::swap( Values & other )
    {
        mValues.swap( other.mValues );
    }

    void Values::add( Value * arg )
    {
        mValues.push_back( arg );
    }

    int Values::size() const {
        return static_cast<int>( mValues.size() );
    }

    bool Values::empty() const {
        return mValues.empty();
    }

    const Value & Values::operator[]( int index ) const
    {
        assert( 0 <= index && static_cast<Container::size_type>( index ) < mValues.size() );
        return *mValues[index];
    }

    Value & Values::operator[]( int index )
    {
        assert( 0 <= index && static_cast<Container::size_type>( index ) < mValues.size() );
        return *mValues[index];
    }

    class ResultChecker
    {
        PREVENT_COPY_AND_ASSIGNMENT( ResultChecker );
    public:
        ResultChecker() : mTarget( 0 ) {}

        virtual ~ResultChecker() { assert( mTarget == 0 ); }

        template < typename T >
        void operator << ( T value ) {
            if( mTarget ) {
                if( check( value, *mTarget ) ) {
                    onPass();
                } else {
                    onFail();
                }
            }
            mTarget = 0;
            log() << "={" << value << "}\n";
        }
        void setTarget( Value * target ) { mTarget = target; }

    private:
        virtual void onPass() = 0;
        virtual void onFail() = 0;

        bool check( int value, int target ) { return value == target; }
        bool check( const char * value, const char * target ) {
            return strcmp( value, target ) == 0;
        }

        bool check( const double & value, const double & target ) {
            return Base::equal( value, target, 0.0001 );
        }

        Value * mTarget;
    };

    void buildArguments( const Values & argumentsPrototype, const std::string & arguments, Values & result )
    {
        assert( arguments.find( '(' ) == 0 );
        assert( arguments.find_last_of( ')' ) == arguments.length() - 1 );
        assert( result.size() == 0 );

        if( argumentsPrototype.empty() ) {
            assert( arguments.size() == 2 );
            return;
        }

        int count = 0;
        String::StringVector argumentList = String::splitEscapedCommaList( arguments.substr( 1, arguments.length() - 2 ) );

        for ( String::StringVector::iterator i = argumentList.begin(); i != argumentList.end(); ++i ) {
            std::string::size_type begin = i->find_first_not_of( " \t\n" );
            std::string::size_type end = i->find_last_not_of( " \t\n" );

            std::string nextValue = i->substr( begin, end - begin + 1 );
            if ( !nextValue.empty() && nextValue[0] == '\"' ) {
                nextValue = String::unEscape( nextValue.c_str() );
            }

            Value * value = argumentsPrototype[ count++ ].clone();
            value->set( nextValue );
            result.add( value );
        }
        assert( argumentsPrototype.size() == result.size() );
    }

    enum ValueType {
        kInt, kDouble, kString,
        kLast // Not actually a type, used to mark the end of lists
    };

    Value * buildValue( ValueType type )
    {
        switch( type ) {
            case kInt:
                return new IntValue( 0 );
            case kDouble:
                return new DoubleValue( 0.0 );
            case kString:
                return new StringValue( "" );
            case kLast:
            default:
                assert( !"Invalid type" );
        }
        return 0;
    }

    class Method
    {
    public:
        typedef void (SimulatorFunction)( FrontEnd & frontEnd, const Values & arguments, ResultChecker & checker );

        class Invocation
        {
        public:
            Invocation( const Method & method )
                : mMethod( &method )
                , mResult( 0 )
            {}

            Invocation( const Invocation & other )
                : mMethod( other.mMethod )
                , mArguments( other.mArguments )
                , mResult( other.mResult ? other.mResult->clone() : 0 )
            {}

            Invocation & operator=( const Invocation & other )
            {
                Invocation temp( other );
                mMethod = other.mMethod;
                mArguments.swap( temp.mArguments );
                std::swap( mResult, temp.mResult );
            }

            void setArguments( const std::string & arguments ) {
                buildArguments( mMethod->argumentsPrototype(), arguments, mArguments );
            }

            void setResult( const std::string & result ) {
                mResult = mMethod->resultPrototype().clone();
                mResult->set( result );
            }

            void invoke( FrontEnd & frontEnd, ResultChecker & checker )
            {
                checker.setTarget( mResult );
                mMethod->invoke( frontEnd, *this, checker );
            }

            const Values & arguments() const { return mArguments; }

        private:
            const Method * mMethod;
            Values mArguments;
            Value * mResult;
        };

        class Function
        {
            PREVENT_ASSIGNMENT( Function );
        public:
            Function() {}
            virtual ~Function() {}

            virtual void invoke( FrontEnd & frontEnd, const Values & arguments, ResultChecker & checker ) = 0;

            virtual Function * clone() const = 0;

            const Values & argumentsPrototype() const { return mArgumentsPrototype; }
            const Value & resultPrototype() const { return mResultPrototype[ 0 ]; }

        protected:
            // Protected to prevent accidental slicing
            Function( const Function & other )
                : mArgumentsPrototype( other.mArgumentsPrototype )
                , mResultPrototype( other.mResultPrototype )
            {}

            Values mArgumentsPrototype;

            // This will only have one value in it, but it is easier to manage this way.
            Values mResultPrototype;
        };

        Method() : mFunction( 0 ) {}
        ~Method() { delete mFunction; mFunction = 0; }

        Method( const Method & other )
            : mFunction( other.mFunction ? other.mFunction->clone() : 0 )
        {
        }
        Method & operator=( const Method & method )
        {
            Method temp( method );
            swap( temp );
        }

        void setFunction( Function *function ) { mFunction = function; }

        bool valid() { return mFunction != 0; }

        const Values & argumentsPrototype() const {
            assert( mFunction );
            return mFunction->argumentsPrototype();
        }
        const Value & resultPrototype() const {
            assert( mFunction );
            return mFunction->resultPrototype();
        }

        void invoke( FrontEnd & frontEnd, const Invocation & invocation, ResultChecker & checker ) const {
            if( mFunction ) {
                mFunction->invoke( frontEnd, invocation.arguments(), checker );
            }
        }
    private:
        void swap( Method & other ) { std::swap( mFunction, other.mFunction ); }
        Function * mFunction;
    };

    struct NoValue{};
    template < typename T> struct ValueTrait {};
    template <>    struct ValueTrait<int> { typedef IntValue Type; enum { Valid = true }; };
    template <> struct ValueTrait<double> { typedef DoubleValue Type; enum { Valid = true }; };
    template <> struct ValueTrait<const char *> { typedef StringValue Type; enum { Valid = true }; };
    template <> struct ValueTrait<NoValue> { enum { Valid = false }; };

    template <
        bool IsConst,
        typename R,
        typename A1  = NoValue,
        typename A2  = NoValue,
        typename A3  = NoValue,
        typename A4  = NoValue,
        typename A5  = NoValue,
        typename A6  = NoValue,
        typename A7  = NoValue,
        typename A8  = NoValue,
        typename A9  = NoValue,
        typename A10 = NoValue,
        typename A11 = NoValue,
        typename A12 = NoValue
    >
    class FunctionImpl : public Method::Function
    {
        PREVENT_ASSIGNMENT( FunctionImpl );
    public:
        // Metafunction to select constness
        template <bool IsConstCall>
        struct FuncTypes {
            // Implement the IsConst==false case
            typedef R (FrontEnd::*Func0 )();
            typedef R (FrontEnd::*Func1 )( A1 );
            typedef R (FrontEnd::*Func2 )( A1, A2 );
            typedef R (FrontEnd::*Func3 )( A1, A2, A3 );
            typedef R (FrontEnd::*Func4 )( A1, A2, A3, A4 );
            typedef R (FrontEnd::*Func5 )( A1, A2, A3, A4, A5 );
            typedef R (FrontEnd::*Func6 )( A1, A2, A3, A4, A5, A6 );
            typedef R (FrontEnd::*Func7 )( A1, A2, A3, A4, A5, A6, A7 );
            typedef R (FrontEnd::*Func8 )( A1, A2, A3, A4, A5, A6, A7, A8 );
            typedef R (FrontEnd::*Func9 )( A1, A2, A3, A4, A5, A6, A7, A8, A9 );
            typedef R (FrontEnd::*Func10)( A1, A2, A3, A4, A5, A6, A7, A8, A9, A10 );
            typedef R (FrontEnd::*Func11)( A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11 );
            typedef R (FrontEnd::*Func12)( A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12 );
        };

        template<>
        struct FuncTypes<true> {
            typedef R (FrontEnd::*Func0 )() const;
            typedef R (FrontEnd::*Func1 )( A1 ) const;
            typedef R (FrontEnd::*Func2 )( A1, A2 ) const;
            typedef R (FrontEnd::*Func3 )( A1, A2, A3 ) const;
            typedef R (FrontEnd::*Func4 )( A1, A2, A3, A4 ) const;
            typedef R (FrontEnd::*Func5 )( A1, A2, A3, A4, A5 ) const;
            typedef R (FrontEnd::*Func6 )( A1, A2, A3, A4, A5, A6 ) const;
            typedef R (FrontEnd::*Func7 )( A1, A2, A3, A4, A5, A6, A7 ) const;
            typedef R (FrontEnd::*Func8 )( A1, A2, A3, A4, A5, A6, A7, A8 ) const;
            typedef R (FrontEnd::*Func9 )( A1, A2, A3, A4, A5, A6, A7, A8, A9 ) const;
            typedef R (FrontEnd::*Func10)( A1, A2, A3, A4, A5, A6, A7, A8, A9, A10 ) const;
            typedef R (FrontEnd::*Func11)( A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11 ) const;
            typedef R (FrontEnd::*Func12)( A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12 ) const;
        };

        typedef typename FuncTypes<IsConst>::Func0  Func0;
        typedef typename FuncTypes<IsConst>::Func1  Func1;
        typedef typename FuncTypes<IsConst>::Func2  Func2;
        typedef typename FuncTypes<IsConst>::Func3  Func3;
        typedef typename FuncTypes<IsConst>::Func4  Func4;
        typedef typename FuncTypes<IsConst>::Func5  Func5;
        typedef typename FuncTypes<IsConst>::Func6  Func6;
        typedef typename FuncTypes<IsConst>::Func7  Func7;
        typedef typename FuncTypes<IsConst>::Func8  Func8;
        typedef typename FuncTypes<IsConst>::Func9  Func9;
        typedef typename FuncTypes<IsConst>::Func10 Func10;
        typedef typename FuncTypes<IsConst>::Func11 Func11;
        typedef typename FuncTypes<IsConst>::Func12 Func12;

        // Metafunction which either invokes the function with the correct number of
        // arguments, or does nothing based on the value of 'skip'.
        template < typename Func, bool skip > struct Invoker {
            // Implement the do nothing case.
            static void invoke( Func, FrontEnd &, const Values &, ResultChecker &) {}
        };
        // Unfortunately since the number of arguments to the FrontEnd member varies, we
        // have to implement it for each number of parameters.
        template <> struct Invoker<Func0, true> { static void invoke( Func0 func, FrontEnd & frontEnd, const Values &, ResultChecker & checker) {
            checker << (frontEnd.*func)();
        } };
        template <> struct Invoker<Func1, true> { static void invoke( Func1 func, FrontEnd & frontEnd, const Values & arg, ResultChecker & checker) {
            checker << (frontEnd.*func)( arg[0] );
        } };
        template <> struct Invoker<Func2, true> { static void invoke( Func2 func, FrontEnd & frontEnd, const Values & arg, ResultChecker & checker) {
            checker << (frontEnd.*func)( arg[0], arg[1] );
        } };
        template <> struct Invoker<Func3, true> { static void invoke( Func3 func, FrontEnd & frontEnd, const Values & arg, ResultChecker & checker) {
            checker << (frontEnd.*func)( arg[0], arg[1], arg[2] );
        } };
        template <> struct Invoker<Func4, true> { static void invoke( Func4 func, FrontEnd & frontEnd, const Values & arg, ResultChecker & checker) {
            checker << (frontEnd.*func)( arg[0], arg[1], arg[2], arg[3] );
        } };
        template <> struct Invoker<Func5, true> { static void invoke( Func5 func, FrontEnd & frontEnd, const Values & arg, ResultChecker & checker) {
            checker << (frontEnd.*func)( arg[0], arg[1], arg[2], arg[3], arg[4] );
        } };
        template <> struct Invoker<Func6, true> { static void invoke( Func6 func, FrontEnd & frontEnd, const Values & arg, ResultChecker & checker) {
            checker << (frontEnd.*func)( arg[0], arg[1], arg[2], arg[3], arg[4], arg[5] );
        } };
        template <> struct Invoker<Func7, true> { static void invoke( Func7 func, FrontEnd & frontEnd, const Values & arg, ResultChecker & checker) {
            checker << (frontEnd.*func)( arg[0], arg[1], arg[2], arg[3], arg[4], arg[5], arg[6] );
        } };
        template <> struct Invoker<Func8, true> { static void invoke( Func8 func, FrontEnd & frontEnd, const Values & arg, ResultChecker & checker) {
            checker << (frontEnd.*func)( arg[0], arg[1], arg[2], arg[3], arg[4], arg[5], arg[6], arg[7] );
        } };
        template <> struct Invoker<Func9, true> { static void invoke( Func9 func, FrontEnd & frontEnd, const Values & arg, ResultChecker & checker) {
            checker << (frontEnd.*func)( arg[0], arg[1], arg[2], arg[3], arg[4], arg[5], arg[6], arg[7], arg[8] );
        } };
        template <> struct Invoker<Func10, true> { static void invoke( Func10 func, FrontEnd & frontEnd, const Values & arg, ResultChecker & checker) {
            checker << (frontEnd.*func)( arg[0], arg[1], arg[2], arg[3], arg[4], arg[5], arg[6], arg[7], arg[8], arg[9] );
        } };
        template <> struct Invoker<Func11, true> { static void invoke( Func11 func, FrontEnd & frontEnd, const Values & arg, ResultChecker & checker) {
            checker << (frontEnd.*func)( arg[0], arg[1], arg[2], arg[3], arg[4], arg[5], arg[6], arg[7], arg[8], arg[9], arg[10] );
        } };
        template <> struct Invoker<Func12, true> { static void invoke( Func12 func, FrontEnd & frontEnd, const Values & arg, ResultChecker & checker) {
            checker << (frontEnd.*func)( arg[0], arg[1], arg[2], arg[3], arg[4], arg[5], arg[6], arg[7], arg[8], arg[9], arg[10], arg[11] );
        } };

        // Metafunction which either adds the type to the values array, or does nothing
        // based on the value of 'skip'
        template < typename T, bool skip > struct Adder {
            // Implement the add case.
            static void add( Values & values ) { values.add( new ValueTrait<T>::Type() ); }
        };
        // Implement the do nothing case.
        template < typename T > struct Adder< T, false > { static void add( Values & ) {} };

        // Unfortunately the casting rules wouldn't let me implement this by passing some
        // bare function pointer, so implement all variants - the invocation will
        // only result in one actually getting used for a given instantiation.
        FunctionImpl( Func0 function )  { buildPrototypes(); mFuncs.f0  = function; }
        FunctionImpl( Func1 function )  { buildPrototypes(); mFuncs.f1  = function; }
        FunctionImpl( Func2 function )  { buildPrototypes(); mFuncs.f2  = function; }
        FunctionImpl( Func3 function )  { buildPrototypes(); mFuncs.f3  = function; }
        FunctionImpl( Func4 function )  { buildPrototypes(); mFuncs.f4  = function; }
        FunctionImpl( Func5 function )  { buildPrototypes(); mFuncs.f5  = function; }
        FunctionImpl( Func6 function )  { buildPrototypes(); mFuncs.f6  = function; }
        FunctionImpl( Func7 function )  { buildPrototypes(); mFuncs.f7  = function; }
        FunctionImpl( Func8 function )  { buildPrototypes(); mFuncs.f8  = function; }
        FunctionImpl( Func9 function )  { buildPrototypes(); mFuncs.f9  = function; }
        FunctionImpl( Func10 function ) { buildPrototypes(); mFuncs.f10 = function; }
        FunctionImpl( Func11 function ) { buildPrototypes(); mFuncs.f11 = function; }
        FunctionImpl( Func12 function ) { buildPrototypes(); mFuncs.f12 = function; }

        virtual void invoke( FrontEnd & frontEnd, const Values & arg, ResultChecker & checker )
        {
            // Use the Invoker metafunction to invoke the correct variant based on the
            // instantiation types.  As with the constructors, only one of these will
            // actually do anything for a given instantiation.
            Invoker< Func0,                            !ValueTrait<A1 >::Valid >::invoke( mFuncs.f0, frontEnd, arg, checker );
            Invoker< Func1,  ValueTrait<A1 >::Valid && !ValueTrait<A2 >::Valid >::invoke( mFuncs.f1, frontEnd, arg, checker );
            Invoker< Func2,  ValueTrait<A2 >::Valid && !ValueTrait<A3 >::Valid >::invoke( mFuncs.f2, frontEnd, arg, checker );
            Invoker< Func3,  ValueTrait<A3 >::Valid && !ValueTrait<A4 >::Valid >::invoke( mFuncs.f3, frontEnd, arg, checker );
            Invoker< Func4,  ValueTrait<A4 >::Valid && !ValueTrait<A5 >::Valid >::invoke( mFuncs.f4, frontEnd, arg, checker );
            Invoker< Func5,  ValueTrait<A5 >::Valid && !ValueTrait<A6 >::Valid >::invoke( mFuncs.f5, frontEnd, arg, checker );
            Invoker< Func6,  ValueTrait<A6 >::Valid && !ValueTrait<A7 >::Valid >::invoke( mFuncs.f6, frontEnd, arg, checker );
            Invoker< Func7,  ValueTrait<A7 >::Valid && !ValueTrait<A8 >::Valid >::invoke( mFuncs.f7, frontEnd, arg, checker );
            Invoker< Func8,  ValueTrait<A8 >::Valid && !ValueTrait<A9 >::Valid >::invoke( mFuncs.f8, frontEnd, arg, checker );
            Invoker< Func9,  ValueTrait<A9 >::Valid && !ValueTrait<A10>::Valid >::invoke( mFuncs.f9, frontEnd, arg, checker );
            Invoker< Func10, ValueTrait<A10>::Valid && !ValueTrait<A11>::Valid >::invoke( mFuncs.f10,frontEnd, arg, checker );
            Invoker< Func11, ValueTrait<A11>::Valid && !ValueTrait<A12>::Valid >::invoke( mFuncs.f11,frontEnd, arg, checker );
            Invoker< Func12, ValueTrait<A12>::Valid                            >::invoke( mFuncs.f12,frontEnd, arg, checker );
        }
        virtual Method::Function* clone() const { return new FunctionImpl( *this ); }
    private:
        void buildPrototypes() {
            Adder< A1,  ValueTrait<A1 >::Valid >::add( mArgumentsPrototype );
            Adder< A2,  ValueTrait<A2 >::Valid >::add( mArgumentsPrototype );
            Adder< A3,  ValueTrait<A3 >::Valid >::add( mArgumentsPrototype );
            Adder< A4,  ValueTrait<A4 >::Valid >::add( mArgumentsPrototype );
            Adder< A5,  ValueTrait<A5 >::Valid >::add( mArgumentsPrototype );
            Adder< A6,  ValueTrait<A6 >::Valid >::add( mArgumentsPrototype );
            Adder< A7,  ValueTrait<A7 >::Valid >::add( mArgumentsPrototype );
            Adder< A8,  ValueTrait<A8 >::Valid >::add( mArgumentsPrototype );
            Adder< A9,  ValueTrait<A9 >::Valid >::add( mArgumentsPrototype );
            Adder< A10, ValueTrait<A10>::Valid >::add( mArgumentsPrototype );
            Adder< A11, ValueTrait<A11>::Valid >::add( mArgumentsPrototype );
            Adder< A12, ValueTrait<A12>::Valid >::add( mArgumentsPrototype );
            mResultPrototype.add( new typename ValueTrait<R>::Type() );
        }

        FunctionImpl( const FunctionImpl & other )
            : Function( other )
            , mFuncs( other.mFuncs )
        {
        }

        // Rather then having a variable for each type, use a union to store the value.
        // Since by construction, any given instantiation will always refer to the same one.
        union Functions { Func0 f0; Func1 f1; Func2 f2; Func3 f3; Func4 f4; Func5 f5; Func6 f6; Func7 f7; Func8 f8; Func9 f9; Func10 f10; Func11 f11; Func12 f12; };
        Functions mFuncs;
    };
    // Use overloading to select the correct instantiation
    template < typename R >
    Method::Function * buildFunction( R (FrontEnd::*func)() ) { return new FunctionImpl< false, R >( func ); }
    template < typename R >
    Method::Function * buildFunction( R (FrontEnd::*func)() const ) { return new FunctionImpl< true, R >( func ); }
    template < typename R, typename A1 >
    Method::Function * buildFunction( R (FrontEnd::*func)( A1 ) ) { return new FunctionImpl< false, R, A1 >( func ); }
    template < typename R, typename A1 >
    Method::Function * buildFunction( R (FrontEnd::*func)( A1 ) const ) { return new FunctionImpl< true, R, A1 >( func ); }
    template < typename R, typename A1, typename A2 >
    Method::Function * buildFunction( R (FrontEnd::*func)( A1, A2 ) ) { return new FunctionImpl< false, R, A1, A2 >( func ); }
    template < typename R, typename A1, typename A2 >
    Method::Function * buildFunction( R (FrontEnd::*func)( A1, A2 ) const ) { return new FunctionImpl< true, R, A1, A2 >( func ); }
    template < typename R, typename A1, typename A2, typename A3 >
    Method::Function * buildFunction( R (FrontEnd::*func)( A1, A2, A3 ) ) { return new FunctionImpl< false, R, A1, A2, A3 >( func ); }
    template < typename R, typename A1, typename A2, typename A3 >
    Method::Function * buildFunction( R (FrontEnd::*func)( A1, A2, A3 ) const ) { return new FunctionImpl< true, R, A1, A2, A3 >( func ); }
    template < typename R, typename A1, typename A2, typename A3, typename A4 >
    Method::Function * buildFunction( R (FrontEnd::*func)( A1, A2, A3, A4 ) ) { return new FunctionImpl< false, R, A1, A2, A3, A4 >( func ); }
    template < typename R, typename A1, typename A2, typename A3, typename A4 >
    Method::Function * buildFunction( R (FrontEnd::*func)( A1, A2, A3, A4 ) const ) { return new FunctionImpl< true, R, A1, A2, A3, A4 >( func ); }
    template < typename R, typename A1, typename A2, typename A3, typename A4, typename A5 >
    Method::Function * buildFunction( R (FrontEnd::*func)( A1, A2, A3, A4, A5 ) ) { return new FunctionImpl< false, R, A1, A2, A3, A4, A5 >( func ); }
    template < typename R, typename A1, typename A2, typename A3, typename A4, typename A5 >
    Method::Function * buildFunction( R (FrontEnd::*func)( A1, A2, A3, A4, A5 ) const ) { return new FunctionImpl< true, R, A1, A2, A3, A4, A5 >( func ); }
    template < typename R, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6 >
    Method::Function * buildFunction( R (FrontEnd::*func)( A1, A2, A3, A4, A5, A6 ) ) { return new FunctionImpl< false, R, A1, A2, A3, A4, A5, A6 >( func ); }
    template < typename R, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6 >
    Method::Function * buildFunction( R (FrontEnd::*func)( A1, A2, A3, A4, A5, A6 ) const ) { return new FunctionImpl< true, R, A1, A2, A3, A4, A5, A6 >( func ); }
    template < typename R, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7 >
    Method::Function * buildFunction( R (FrontEnd::*func)( A1, A2, A3, A4, A5, A6, A7 ) ) { return new FunctionImpl< false, R, A1, A2, A3, A4, A5, A6, A7 >( func ); }
    template < typename R, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7 >
    Method::Function * buildFunction( R (FrontEnd::*func)( A1, A2, A3, A4, A5, A6, A7 ) const ) { return new FunctionImpl< true, R, A1, A2, A3, A4, A5, A6, A7 >( func ); }
    template < typename R, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8 >
    Method::Function * buildFunction( R (FrontEnd::*func)( A1, A2, A3, A4, A5, A6, A7, A8 ) ) { return new FunctionImpl< false, R, A1, A2, A3, A4, A5, A6, A7, A8 >( func ); }
    template < typename R, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8 >
    Method::Function * buildFunction( R (FrontEnd::*func)( A1, A2, A3, A4, A5, A6, A7, A8 ) const ) { return new FunctionImpl< true, R, A1, A2, A3, A4, A5, A6, A7, A8 >( func ); }
    template < typename R, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9 >
    Method::Function * buildFunction( R (FrontEnd::*func)( A1, A2, A3, A4, A5, A6, A7, A8, A9 ) ) { return new FunctionImpl< false, R, A1, A2, A3, A4, A5, A6, A7, A8, A9 >( func ); }
    template < typename R, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9 >
    Method::Function * buildFunction( R (FrontEnd::*func)( A1, A2, A3, A4, A5, A6, A7, A8, A9 ) const ) { return new FunctionImpl< true, R, A1, A2, A3, A4, A5, A6, A7, A8, A9 >( func ); }
    template < typename R, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10 >
    Method::Function * buildFunction( R (FrontEnd::*func)( A1, A2, A3, A4, A5, A6, A7, A8, A9, A10 ) ) { return new FunctionImpl< false, R, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10 >( func ); }
    template < typename R, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10 >
    Method::Function * buildFunction( R (FrontEnd::*func)( A1, A2, A3, A4, A5, A6, A7, A8, A9, A10 ) const ) { return new FunctionImpl< true, R, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10 >( func ); }
    template < typename R, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11 >
    Method::Function * buildFunction( R (FrontEnd::*func)( A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11 ) ) { return new FunctionImpl< false, R, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11 >( func ); }
    template < typename R, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11 >
    Method::Function * buildFunction( R (FrontEnd::*func)( A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11 ) const ) { return new FunctionImpl< true, R, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11 >( func ); }
    template < typename R, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12 >
    Method::Function * buildFunction( R (FrontEnd::*func)( A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12 ) ) { return new FunctionImpl< false, R, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12 >( func ); }
    template < typename R, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12 >
    Method::Function * buildFunction( R (FrontEnd::*func)( A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12 ) const ) { return new FunctionImpl< true, R, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12 >( func ); }
    // Invoke a method of the API.
    class MethodParser
    {
        PREVENT_COPY_AND_ASSIGNMENT( MethodParser );
    public:
        MethodParser() { init(); }

        Method::Invocation * buildInvocation( const std::string & methodWithArgs )
        {
            if( methodWithArgs.find( '!' ) != 0 ) {
                return 0;
            }
            std::string::size_type offset = methodWithArgs.find( '(' );
            // If there is no opening brace, assume this doesn't represent a method call
            // and skip it.
            if( offset == std::string::npos ) {
                return 0;
            }
            Method & method = determineMethod( methodWithArgs.substr( 1, offset - 1 ) );
            if( !method.valid() ) {
                return 0;
            }

            Method::Invocation * invocation = new Method::Invocation( method );
            invocation->setArguments( methodWithArgs.substr( offset ) );
            return invocation;
        }

    private:
        typedef std::map< std::string, Method > Methods;

        void addMethod( const char * name, Method::Function * function )
        {
            assert( mMethods.find( std::string( name ) ) == mMethods.end() );
            Method & method = mMethods[ name ];
            method.setFunction( function );
        }
        #define ADD_METHOD( name ) addMethod( #name, buildFunction( &FrontEnd:: name ) )

        void init()
        {
            ADD_METHOD( clearCircuit );
            ADD_METHOD( createComponent );
            ADD_METHOD( createWires );
            ADD_METHOD( createWire );
            ADD_METHOD( removeWire );
            ADD_METHOD( peekActionUpdates );
            ADD_METHOD( getActionUpdates );
            ADD_METHOD( runCircuitCycle );
            ADD_METHOD( triggerAction );
            ADD_METHOD( triggerFault );
            ADD_METHOD( repair );
            ADD_METHOD( componentStateVar );
            ADD_METHOD( createMeter );
            ADD_METHOD( removeMeter );
            ADD_METHOD( getErrorDescription );
            ADD_METHOD( loadDevices );
            ADD_METHOD( getDeviceNames );
            ADD_METHOD( getDeviceSpecNames );
            ADD_METHOD( getTerminalCount );
            ADD_METHOD( getShortableTerminals );
            ADD_METHOD( getFaultNames );
            ADD_METHOD( componentIsFaulty );
            ADD_METHOD( anyComponentIsFaulty );
        }

        // Map from method name to method ID
        Method & determineMethod( std::string methodName )
        {
            assert( mMethods.find( methodName ) != mMethods.end() );
            return mMethods[ methodName ];
        }

        Methods mMethods;
    };

    class ResultCounter : public ResultChecker
    {
    public:
        ResultCounter() : mPassCount( 0 ), mFailCount( 0 ) {}

        int passed() const { return mPassCount; }
        int failed() const { return mFailCount; }
    private:
        virtual void onPass() {
            ++mPassCount;
        }

        virtual void onFail() {
            log() << "Result did not match!" << std::endl;
            ++mFailCount;
        }

        int mPassCount;
        int mFailCount;
    };
}

class TestParser::TestSequence
{
public:
    typedef std::vector< Method::Invocation * > Invocations;
    TestSequence( const char * fileName )
    {
        const int kEolBufferSize = 5;
        char eolBuffer[kEolBufferSize];
        std::ifstream file( fileName );
        while( file.good() && !file.eof() ) {
            std::stringbuf stream;
            file.get( stream );
            file.getline( eolBuffer, kEolBufferSize - 1 );

            Method::Invocation * invocation = mParser.buildInvocation( stream.str() );

            if( invocation ) {
                mInvocations.push_back( invocation );
            } else {
                std::string result = stream.str();
                if( result[0] == '=' ) {
                    assert( result[1] == '{' );
                    while( resultContinues( result ) ) {
                        stream.sputc( '\r' );
                        stream.sputc( '\n' );
                        file.get( stream );
                        file.getline( eolBuffer, kEolBufferSize - 1 );
                        if( file.eof() ) {
                            return;
                        }
                        result = stream.str();
                    }
                    mInvocations.back()->setResult( result.substr( 2, result.length() - 3 ) );
                }
            }
        }
    }

    bool resultContinues( const std::string& result )
    {
        return result.length() > 2 && result[ result.length() - 1 ] != '}';
    }

    // Invoke each method in sequence
    void run( FrontEnd& frontEnd, ResultChecker & checker )
    {
        Invocations::iterator it;
        for( it = mInvocations.begin(); it != mInvocations.end(); ++it ) {
            Method::Invocation * invocation = *it;
            invocation->invoke( frontEnd, checker );
            delete invocation;
        }
        mInvocations.clear();
    }
private:
    Invocations mInvocations;
    MethodParser mParser;
};

TestParser::TestParser( const char * testFileName )
    : mTestSequence( new TestSequence( testFileName ) )
    , mFrontEnd( new FrontEnd() )
{
}

bool TestParser::runTest()
{
    Base::Stopwatch timer;
    assert( mTestSequence != 0 );
    ResultCounter resultCounter;
    mTestSequence->run( *mFrontEnd, resultCounter );

    std::cout <<  "Full test Ellapsed " << timer.ellapsed() / 1e3 << " seconds.\n";

    std::cout << "Processed: " << resultCounter.passed() << std::endl;
    return resultCounter.failed() == 0;
}

TestParser::~TestParser()
{
    delete mFrontEnd;
    mFrontEnd = 0;

    delete mTestSequence;
    mTestSequence = 0;
}

#endif // OLD_PARSER
