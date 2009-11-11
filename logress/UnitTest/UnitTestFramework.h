#ifndef TEST_FRAMEWORK_H__INCLUDED
#define TEST_FRAMEWORK_H__INCLUDED
/* ---------------------------------------------------------------
 * Copyright (c) Adrian Smith.
 * Licensed under the MIT license. See license.txt at project root.
 * --------------------------------------------------------------- */

#ifdef BUILD_TESTS

#include <string>

/*
 * This is the basis of the very simple test framework.  It doesn't form any part of the
 * simulator code, it is only here to support development work.
 *
 * See TestSkeleton.txt for what's needed to put a test together.
 *
 * Basically you need a name, a run method, and an Initializer to register the test
 * to the framework.
 *
 * Most tests have several sub-tests called by the run method.
 *
 * This framework is generally used for testing specific functionality.
 * See TestParser for a system which can be used to playback the output of a log
 * for tracking down bugs and possibly as a regression test framework.
 */

#define RUN( test ) preSub( #test ); test(); postSub( #test )

#define CHECK( condition ) checkCondition( !!(condition), #condition, __FILE__, __LINE__ )
#define CHECK_ASSERT( condition ) CHECK( condition ); if( failing() ) return

#define DECLARE_TEST( test ) namespace { UnitTest::Initializer< test > initialze##test( #test ); }

namespace UnitTest {

    class Framework
    {
        PREVENT_COPY_AND_ASSIGNMENT( Framework );
    public:
        Framework();
        virtual ~Framework();

        virtual void run() = 0;

        void setName( const char* name );
        const char* name() const { return mName.c_str(); }

        void setFilesDir( const char* filesDir );
        std::string file( const std::string& filePath );

        void preSub( const char* subName );
        void postSub( const char* subName );

        void checkCondition( bool result, const char* condition, const char* fileName, int lineNumber );

        bool passed() { return mFailCount == 0; }
        bool failing() { return mFailCount > 0; }
        int subTestCount() { return mRunCount; }

        class Factory
        {
            PREVENT_COPY_AND_ASSIGNMENT( Factory );
        public:
            Factory();
            virtual ~Factory();
            virtual Framework* operator()() const = 0;
        };

        template <class T>
        class DefaultFactory : public Factory
        {
        public:
            Framework* operator()() const {
                return new T();
            }
        };

        static void registerTest( Factory*, const char* name );

        static int runTests( const char* tests[], const char* testFilesDir );

        static bool compareFiles( const char* first, const char* second );

    private:
        std::string mName;
        std::string mFilesDir;
        int mRunCount;
        int mFailCount;
        bool mTestFailed;
    };

    template <class T >
    class Initializer
    {
        PREVENT_COPY_AND_ASSIGNMENT( Initializer );
    public:
        Initializer( const char* name )
        {
            Framework::registerTest(
                new Framework::DefaultFactory<T>(), name
            );
        }
    };
}

#endif // BUILD_TESTS

#endif // TEST_FRAMEWORK_H__INCLUDED
