#ifndef TEST_OBJECT_H__INCLUDED
#define TEST_OBJECT_H__INCLUDED
/* ---------------------------------------------------------------
 * Copyright (c) Adrian Smith.
 * Licensed under the MIT license. See license.txt at project root.
 * --------------------------------------------------------------- */

#include "Test/TestMethod.h"
#include "Test/TestBase.h"
#include "Memory/MemoryShared.h"
#include <map>
#include <assert.h>

namespace Test
{
    template <typename C>
    class Object;
}

template <typename C>
class Test::Object : public Test::IObject
{
    PREVENT_COPY_AND_ASSIGNMENT( Object );
public:
    typedef Test::IMethod<C> CMethod;
    typedef Memory::Shared<const CMethod> MethodH;

    class VTable : public Memory::Counted
    {
    public:
        typedef C ClassType;
        typedef std::map< std::string, MethodH > Methods;

        ~VTable()
        {
        }

        void add( const std::string& methodName, MethodH method )
        {
            assert( mMethods.find( methodName ) == mMethods.end() );
            mMethods[ methodName ] = method;
        }

        MethodH find( const std::string& methodName ) const
        {
            typename Methods::const_iterator method = mMethods.find( methodName );
            if( method != mMethods.end() )
            {
                return method->second;
            }
            return MethodH();
        }

    private:
        Methods mMethods;
    };

    typedef Memory::Shared<VTable> VTableH;
    typedef Memory::Shared<const VTable> ConstVTableH;

    Object( C* object, ConstVTableH vTable )
        : mObject( object )
        , mVTable( vTable )
    {
    }

    virtual ~Object()
    {
    }

    virtual bool hasMethod( const std::string& methodName )
    {
        return !mVTable->find( methodName ).isNull();
    }

    virtual Test::InvokeResult invoke( const std::string& methodName, const Test::InvokeContext& context )
    {
        MethodH method = mVTable->find( methodName );
        if( method.isNull() )
        {
            return Test::InvokeResult( Test::InvokeResult::kMethodNotFound );
        }
        return method->invoke( *mObject, context );
    }

private:
    std::auto_ptr<C> mObject;
    ConstVTableH mVTable;
};

#define VTABLE_DECLARE( type, variable ) typedef type _TYPE_FOR_ ## variable; Memory::Shared< Test::Object< type >::VTable > variable( new Test::Object< type >::VTable() )
#define VTABLE_ADD( variable, method ) variable->add( #method, Test::MethodBuilder< _TYPE_FOR_ ## variable >::build( & _TYPE_FOR_ ## variable ::method ) )

#endif // TEST_OBJECT_H__INCLUDED
