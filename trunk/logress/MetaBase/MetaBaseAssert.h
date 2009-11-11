#ifndef METABASE_ASSERT_H__INCLUDED
#define METABASE_ASSERT_H__INCLUDED

namespace MetaBase {
    struct AssertFailed;

    template < bool, typename Message = AssertFailed >
    struct CompileAssert {};

    template < typename Message >
    struct CompileAssert<false, Message> : public Message {};
}

#endif //METABASE_ASSERT_H__INCLUDED
