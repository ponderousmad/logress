/*
 * main.cpp
 *
 *  Created on: Apr 25, 2009
 *      Author: agnomen
 */

#include "Base/Top.h"
#include "Base/BaseLogger.h"
#include "UnitTest/UnitTestFramework.h"

int main(int argc, char** argv)
{
    const char* tests[] = {
      "MemoryCountedTest",
      "MemoryDerefTest",
      "MemorySharedTest",
      "StringCastsTest",
      "StringUtilsTest",
      "StringSubstituteTest",
      "TestArgumentListTest",
      "TestFunctionTest",
      "TestMethodTest",
      "TestObjectTest",
      "TestObjectFactoryTest",
      "TestLogRunnerTest",
      0
    };
    UnitTest::Framework::runTests( tests, "" );

    return 0;
}
