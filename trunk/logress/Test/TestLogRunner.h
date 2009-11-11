/* ---------------------------------------------------------------
 * Copyright (c) Adrian Smith.
 * Licensed under the MIT license. See license.txt at project root.
 * --------------------------------------------------------------- */
#ifndef TEST_LOGRUNNER_H__INCLUDED
#define TEST_LOGRUNNER_H__INCLUDED

#include <iosfwd>

namespace Test {
    class Environment;
    class LogRunner;
}

class Test::LogRunner
{
    PREVENT_COPY_AND_ASSIGNMENT( LogRunner );
public:
    LogRunner();
    ~LogRunner();

    bool runTest( const char* testFile, Test::Environment& environment );
    bool runTest( std::istream& stream, Test::Environment& environment );
};

#endif // TEST_LOGRUNNER_H__INCLUDED
