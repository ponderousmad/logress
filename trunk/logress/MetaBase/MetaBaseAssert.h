#ifndef METABASE_ASSERT_H__INCLUDED
#define METABASE_ASSERT_H__INCLUDED
/* ---------------------------------------------------------------
 * Copyright (c) Adrian Smith.
 * Licensed under the MIT license. See license.txt at project root.
 * --------------------------------------------------------------- */

/*
 * Compile time assert checking.
 * For example, the line will fail to compile:
 * MetaBase::CompileAssert< MetaBase::IsConst<int>::Value >()
 *
 * Note that due to the nature of template instantiation, the placement
 * of this line can influence whether the compiler will even encounter it.
 * For best results, it should be used in the body of a template function,
 * but any place that the type signature is guarnteed to be instantiate with
 * the type will work.
 *
 * You can customize the error that occurs by using any declared but not defined
 * type as the second template argument.
 */
namespace MetaBase {
    // This forward declaration must never be defined, which will result in
    // the compilation error when trying to derive from it in the 'false' case.
    struct AssertFailed;

    template < bool, typename Message = AssertFailed >
    struct CompileAssert {};

    // Specialize for the false case to derive from an (undefined) type.
    template < typename Message >
    struct CompileAssert<false, Message> : public Message {};
}

#endif //METABASE_ASSERT_H__INCLUDED
