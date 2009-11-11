#ifndef TEST_BASE_H__INCLUDED
#define TEST_BASE_H__INCLUDED
/* ---------------------------------------------------------------
 * Copyright (c) Adrian Smith.
 * Licensed under the MIT license. See license.txt at project root.
 * --------------------------------------------------------------- */

#include <string>
#include <memory>
#include "Memory/MemoryCounted.h"

namespace Test {
    class Environment;

    class ValueCheck;
    class InvokeResult;
    class InvokeContext;

    class IFunction;
    template <typename C> class IMethod;
    class IObject;
    class IObjectFactory;
}

class Test::ValueCheck
{
    PREVENT_COPY_AND_ASSIGNMENT( ValueCheck );
public:
    ValueCheck() {}
    virtual ~ValueCheck() {}
    virtual bool check( const std::string& target, Test::Environment& environment ) = 0;
};

class Test::InvokeResult
{
    PREVENT_ASSIGNMENT( InvokeResult );
public:
    enum Status {
        kMethodNotFound,
        kObjectNotFound,
        kConstructorNotFound,
        kConstructorFailed,
        kSuccess
    };

    InvokeResult( Status );
    InvokeResult( Test::ValueCheck* value );
    ~InvokeResult();

    bool check( const std::string& target, Test::Environment& environment );

private:
    typedef std::auto_ptr< Test::ValueCheck > Value;

    // Some uglyness to enable copy construction
    typedef std::auto_ptr_ref< Test::ValueCheck > ValueRef;
    struct Return
    {
        Return( Status status, ValueRef value ) : mStatus( status ), mValue( value ) {}
        Status mStatus;
        ValueRef mValue;
    };
public:
    // The combination of these two methods provides copy construction
    // The structure follows that of auto_ptr itself.
    operator Return() {
        return Return( mStatus, mValue );
    }
    InvokeResult( Return );

private:
    Status mStatus;
    Value mValue;
};

class Test::IFunction : public Memory::Counted
{
    PREVENT_COPY_AND_ASSIGNMENT( IFunction );
public:
    IFunction() {}
    virtual ~IFunction();
    virtual Test::InvokeResult invoke( const Test::InvokeContext& context ) const = 0;
};

template <typename C>
class Test::IMethod : public Memory::Counted
{
    PREVENT_COPY_AND_ASSIGNMENT( IMethod );
public:
    IMethod() {}
    virtual ~IMethod() {}
    virtual Test::InvokeResult invoke( C& obj, const Test::InvokeContext& context ) const = 0;
};

class Test::IObject : public Memory::Counted
{
    PREVENT_COPY_AND_ASSIGNMENT( IObject );
public:
    IObject() {}
    virtual ~IObject();
    virtual bool hasMethod( const std::string& methodName ) = 0;
    virtual Test::InvokeResult invoke( const std::string& methodName, const Test::InvokeContext& context ) = 0;
};

class Test::IObjectFactory : public Memory::Counted
{
    PREVENT_COPY_AND_ASSIGNMENT( IObjectFactory );
public:
    IObjectFactory() {}
    virtual ~IObjectFactory();

    typedef std::pair< Test::InvokeResult::Status, Memory::Shared< Test::IObject > > Result;
    virtual Result construct( const Test::InvokeContext& context ) const = 0;
};

namespace Test
{
    typedef Memory::Shared<IFunction> FunctionH;
    typedef Memory::Shared<const IFunction> ConstFunctionH;
    typedef Memory::Shared<IObject> ObjectH;
    typedef Memory::Shared<const IObject> ConstObjectH;
    typedef Memory::Shared<IObjectFactory> ObjectFactoryH;
    typedef Memory::Shared<const IObjectFactory> ConstObjectFactoryH;
}

#endif // TEST_BASE_H__INCLUDED
