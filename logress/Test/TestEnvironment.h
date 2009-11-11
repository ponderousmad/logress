#ifndef TEST_ENVIRONMENT_H__INCLUDED
#define TEST_ENVIRONMENT_H__INCLUDED

#include "Test/TestFwd.h"
#include <string>
#include <map>

class Test::Environment
{
public:
    typedef std::map< std::string, Test::ConstFunctionH > Functions;
    typedef std::map< std::string, Test::ObjectH > Objects;
    typedef std::map< std::string, Test::ConstObjectFactoryH > Factories;

    Environment();
    ~Environment();

    bool add( Test::ConstObjectFactoryH objectFactory, const std::string& typeName );
    bool add( Test::ConstFunctionH function, const std::string& functionName );
    bool add( Test::ObjectH object, const std::string& objectName );

    template <typename T>
    T lookup( const std::string& name )
    {
        return T();
    }

    Test::ConstObjectFactoryH findFactory( const std::string& name ) const;
    Test::ConstFunctionH findFunction( const std::string& name ) const;
    Test::ObjectH findObject( const std::string& name ) const;

private:
    Functions mFunctions;
    Objects mObjects;
    Factories mFactories;
};

#endif // TEST_ENVIRONMENT_H__INCLUDED
