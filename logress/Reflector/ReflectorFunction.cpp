#include "Base/Top.h"

#include "Reflector/ReflectorFunction.h"

#include "Reflector/ReflectorTestSwitch.h"

#ifdef COMPILE_REFLECTOR_TESTS

#include "MetaBase/MetaBaseTypeListNth.h"
#include "MetaBase/MetaBaseSame.h"
#include "MetaBase/MetaBaseAssert.h"

using namespace MetaBase;
using namespace Reflector;

namespace {
    int foo( int, int, double )
    {
        return 0;
    }

    template <typename Func>
    void reflect( Func )
    {
        typedef Function< Func > Reflection;
        typedef typename Nth< typename Reflection::ArgumentTypes, 2 >::Type LastArgType;
        CompileAssert< Same< LastArgType, double >::Value >();
        CompileAssert< Same< typename Reflection::ClassType, NullType >::Value >();
        CompileAssert< Same< typename Reflection::ReturnType, int >::Value >();
    }
}

namespace ReflectorTest
{
    void testFunction()
    {
        reflect( &foo );
    }
}

#endif // COMPILE_REFLECTOR_TESTS
