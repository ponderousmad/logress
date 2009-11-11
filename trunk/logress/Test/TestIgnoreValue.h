#ifndef TEST_IGNOREVALUE_H__INCLUDED
#define TEST_IGNOREVALUE_H__INCLUDED
/* ---------------------------------------------------------------
 * Copyright (c) Adrian Smith.
 * Licensed under the MIT license. See license.txt at project root.
 * --------------------------------------------------------------- */

#include "Test/TestBase.h"

namespace Test {
    class IgnoreValue;
}

class Test::IgnoreValue : public Test::ValueCheck
{
    PREVENT_COPY_AND_ASSIGNMENT( IgnoreValue );
public:
    IgnoreValue();
    ~IgnoreValue();

    virtual bool check( const std::string&, Test::Environment& );
};

#endif // TEST_IGNOREVALUE_H__INCLUDED
