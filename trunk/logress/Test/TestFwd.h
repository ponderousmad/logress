#ifndef TEST_FWD_H__INCLUDED
#define TEST_FWD_H__INCLUDED

#include "Memory/MemoryFwd.h"

namespace Test {
    class Environment;

    class ValueCheck;

    class InvokeResult;

    class InvokeContext;

    class IFunction;

    template <typename C>
    class IMethod;

    class IObject;

    class IObjectFactory;

    typedef Memory::Shared<IFunction> FunctionH;
    typedef Memory::Shared<const IFunction> ConstFunctionH;
    typedef Memory::Shared<IObject> ObjectH;
    typedef Memory::Shared<const IObject> ConstObjectH;
    typedef Memory::Shared<IObjectFactory> ObjectFactoryH;
    typedef Memory::Shared<const IObjectFactory> ConstObjectFactoryH;
}


#endif // TEST_FWD_H__INCLUDED
