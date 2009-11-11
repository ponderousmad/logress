#include "Base/Top.h"

#include "Test/TestEnvironment.h"
#include "Test/TestBase.h"
#include "Memory/MemoryShared.h"

#include <map>
#include "assert.h"

using Test::Environment;
using Test::ConstFunctionH;
using Test::ObjectH;
using Test::ConstObjectFactoryH;

Test::Environment::Environment()
{
}

Test::Environment::~Environment()
{
}

bool Environment::add( ConstObjectFactoryH objectFactory, const std::string& typeName )
{
    if( mFactories.find( typeName ) != mFactories.end() )
    {
        return false;
    }
    mFactories[ typeName ] = objectFactory;
    return true;
}

bool Environment::add( ConstFunctionH function, const std::string& functionName )
{
    if( mFunctions.find( functionName ) != mFunctions.end() )
    {
        return false;
    }
    mFunctions[ functionName ] = function;
    return true;
}

bool Environment::add( ObjectH object, const std::string& objectName )
{
    if( mObjects.find( objectName ) != mObjects.end() )
    {
        return false;
    }
    mObjects[ objectName ] = object;
    return true;
}

ConstObjectFactoryH Environment::findFactory( const std::string& name ) const
{
    Factories::const_iterator item = mFactories.find( name );
    if( item != mFactories.end() )
    {
        return item->second;
    }
    return ConstObjectFactoryH();
}

ConstFunctionH Environment::findFunction( const std::string& name ) const
{
    Functions::const_iterator item = mFunctions.find( name );
    if( item != mFunctions.end() )
    {
        return item->second;
    }
    return ConstFunctionH();
}

ObjectH Environment::findObject( const std::string& name ) const
{
    Objects::const_iterator item = mObjects.find( name );
    if( item != mObjects.end() )
    {
        return item->second;
    }
    return ObjectH();
}
