#ifndef TESTPARSER_H__INCLUDED
#define TESTPARSER_H__INCLUDED

#ifdef OLD_PARSER

namespace Test {
    class TestParser;
}

// This can take the result of a log and invoke the same sequence of method calls
// so that we can repeat what happend from a client session and debug it.

// The output of a logging should be usable without modification - the
// parts of the log that identify method calls and arguments will be
// exected, and the rest ignored.
class Test::TestParser
{
    PREVENT_COPY_AND_ASSIGNMENT( TestParser );
public:
    TestParser( const char* testFileName );
    ~TestParser();

    bool runTest();

private:
    class TestSequence;

    TestSequence* mTestSequence;
};

#endif // OLD_PARSER

#endif // TESTPARSER_H__INCLUDED
