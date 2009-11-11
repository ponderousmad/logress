/* ---------------------------------------------------------------
 * Copyright (c) Adrian Smith.
 * Licensed under the MIT license. See license.txt at project root.
 * --------------------------------------------------------------- */
#include "Base/Top.h"

#include "Test/TestInvokeContext.h"

using Test::InvokeContext;

InvokeContext::InvokeContext( const std::string& arguments, const Test::Environment& environment )
    : mArguments( arguments )
    , mEnvironment( environment )
{
}

InvokeContext::~InvokeContext()
{
}
