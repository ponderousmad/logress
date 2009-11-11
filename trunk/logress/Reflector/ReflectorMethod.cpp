/* ---------------------------------------------------------------
 * Copyright (c) Adrian Smith.
 * Licensed under the MIT license. See license.txt at project root.
 * --------------------------------------------------------------- */
#include "Base/Top.h"

#include "Reflector/ReflectorMethod.h"
#include "Reflector/ReflectorConstMethod.h"

#include "Reflector/ReflectorTestSwitch.h"

#ifdef COMPILE_REFLECTOR_TESTS

#include "MetaBase/MetaBaseTypeListLength.h"
#include "MetaBase/MetaBaseTypeListNth.h"
#include "MetaBase/MetaBaseSame.h"
#include "MetaBase/MetaBaseAssert.h"
#include "MetaBase/MetaBaseTypeTraits.h"

using namespace MetaBase;
using namespace Reflector;

namespace {
    class Bar
    {
    public:
        int three( int, int, double ) {
            return 0;
        }

        int ten( int, int, int, int, int, int, int, int, double, int ) {
            return 0;
        }

        int threeConst( int, int, double ) const {
            return 0;
        }

        int tenConst( int, int, int, int, int, int, int, int, double, int ) const {
            return 0;
        }
    };

    template <typename Target>
    struct CheckTarget
    {
        template <typename Func>
        void reflect( Func )
        {
            typedef Function< Func > Reflection;
            typedef typename Nth< typename Reflection::ArgumentTypes, ListLength< typename Reflection::ArgumentTypes >::Value - 1 >::Type LastArgType;

            CompileAssert< Same< typename Reflection::ClassType, Bar >::Value >();
            CompileAssert< Same< typename Reflection::ReturnType, int >::Value >();
            CompileAssert< Same< LastArgType, Target >::Value >();

        }
    };

    struct CheckConst
    {
        template <typename Func>
        void checkIsConst( Func )
        {
            typedef Function< Func > Reflection;
            CompileAssert< Reflection::IsConst::Value >();
        }

        template <typename Func>
        void checkIsNotConst( Func )
        {
            typedef Function< Func > Reflection;
            CompileAssert< !Reflection::IsConst::Value >();
        }
    };
}

namespace ReflectorTest {
    void testMethod()
    {
        CheckTarget< double > checkDouble;
        checkDouble.reflect( &Bar::three );

        CheckTarget< int > checkInt;
        checkInt.reflect( &Bar::ten );

        checkDouble.reflect( &Bar::threeConst );
        checkInt.reflect( &Bar::tenConst );

        CheckConst checkConst;
        checkConst.checkIsNotConst( &Bar::three );
        checkConst.checkIsConst( &Bar::threeConst );

        checkConst.checkIsNotConst( &Bar::ten );
        checkConst.checkIsConst( &Bar::tenConst );
    }
}

#endif // COMPILE_REFLECTOR_TESTS
