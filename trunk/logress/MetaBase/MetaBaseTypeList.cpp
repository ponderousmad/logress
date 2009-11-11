/* ---------------------------------------------------------------
 * Copyright (c) Adrian Smith.
 * Licensed under the MIT license. See license.txt at project root.
 * --------------------------------------------------------------- */
#include "Base/Top.h"

#include "MetaBase/MetaBaseTypeList.h"
#include "MetaBase/MetaBaseTypeListLength.h"
#include "MetaBase/MetaBaseTypeListNth.h"

#include "MetaBase/MetaBaseTestSwitch.h"

#ifdef COMPILE_METABASE_TESTS

#include "MetaBase/MetaBaseSame.h"
#include "MetaBase/MetaBaseAssert.h"

namespace MetaBaseTest {
    using namespace MetaBase;

    struct LengthMismatch;
    struct TypeMismatch;

    void testTypeList()
    {
        CompileAssert< ListLength< EmptyTypeList >::Value == 0, LengthMismatch >();

        typedef TYPELIST_3( int, int, double ) IID;

        CompileAssert< ListLength< IID >::Value == 3, LengthMismatch >();
        CompileAssert< Same< Nth< IID, 0 >::Type, int >::Value, TypeMismatch >();
        CompileAssert< Same< Nth< IID, 1 >::Type, int >::Value, TypeMismatch >();
        CompileAssert< Same< Nth< IID, 2 >::Type, double >::Value, TypeMismatch >();
    }
}

#endif // COMPILE_METABASE_TESTS
