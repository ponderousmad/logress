#include "Base/Top.h"

#include "Test/TestBase.h"

#include <map>
#include "assert.h"

using Test::InvokeResult;

Test::IFunction::~IFunction()
{
}

Test::IObject::~IObject()
{
}

Test::IObjectFactory::~IObjectFactory()
{
}

InvokeResult::InvokeResult( Status status )
    : mStatus( status )
    , mValue( 0 )
{
}

InvokeResult::InvokeResult( Test::ValueCheck* value )
    : mStatus( kSuccess )
    , mValue( value )
{
}

InvokeResult::~InvokeResult()
{
}

InvokeResult::InvokeResult( Return other )
    : mStatus( other.mStatus )
    , mValue( other.mValue )
{
}

bool InvokeResult::check( const std::string& target, Test::Environment& environment )
{
    if( mStatus != kSuccess )
    {
        return false;
    }
    if( mValue.get() )
    {
        return mValue->check( target, environment );
    }
    return true;
}

