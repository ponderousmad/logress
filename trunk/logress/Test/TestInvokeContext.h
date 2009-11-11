#ifndef TEST_INVOKECONTEXT_H__INCLUDED
#define TEST_INVOKECONTEXT_H__INCLUDED
/* ---------------------------------------------------------------
 * Copyright (c) Adrian Smith.
 * Licensed under the MIT license. See license.txt at project root.
 * --------------------------------------------------------------- */

#include <string>

namespace Test
{
    class InvokeContext;
    class Environment;
}

class Test::InvokeContext
{
    PREVENT_COPY_AND_ASSIGNMENT( InvokeContext );
public:
    InvokeContext( const std::string& arguments, const Test::Environment& environment );
    ~InvokeContext();

    const std::string& arguments() const { return mArguments; }
    const Environment& environment() const { return mEnvironment; }

private:
    std::string mArguments;
    const Environment& mEnvironment;
};

#endif // TEST_INVOKECONTEXT_H__INCLUDED
