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
