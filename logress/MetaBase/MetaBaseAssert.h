#ifndef METABASE_ASSERT_H__INCLUDED
#define METABASE_ASSERT_H__INCLUDED
/* ---------------------------------------------------------------
 * Copyright (c) Adrian Smith.
 * Licensed under the MIT license. See license.txt at project root.
 * --------------------------------------------------------------- */

namespace MetaBase {
    struct AssertFailed;

    template < bool, typename Message = AssertFailed >
    struct CompileAssert {};

    template < typename Message >
    struct CompileAssert<false, Message> : public Message {};
}

#endif //METABASE_ASSERT_H__INCLUDED
