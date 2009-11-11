/* ---------------------------------------------------------------
 * Copyright (c) Adrian Smith.
 * Licensed under the MIT license. See license.txt at project root.
 * --------------------------------------------------------------- */
#include "Base/Top.h"

#include "Test/TestIgnoreValue.h"

using Test::IgnoreValue;

IgnoreValue::IgnoreValue()
{
}

IgnoreValue::~IgnoreValue()
{
}

bool IgnoreValue::check( const std::string&, Test::Environment& )
{
    return true;
}
