#ifndef TEST_ARGUMENTSPARSER_H__INCLUDED
#define TEST_ARGUMENTSPARSER_H__INCLUDED
/* ---------------------------------------------------------------
 * Copyright (c) Adrian Smith.
 * Licensed under the MIT license. See license.txt at project root.
 * --------------------------------------------------------------- */

#include "Test/TestInvokeContext.h"
#include "Test/TestArgumentNumber.h"
#include "MetaBase/MetaBaseTypeListLength.h"
#include "String/StringCasts.h"
#include "String/StringUtils.h"
#include <string>
#include <assert.h>

namespace Test
{
    template <typename ArgList, int Index>
    struct ArgSetter
    {
        static void setArgs( ArgList& list, const std::string& args, std::string::size_type& current )
        {
            assert( current <= args.length() );
            ArgSetter<ArgList, Index-1>::setArgs( list, args, current );
            std::string::size_type endOfArgument = String::findFirstUnescapedComma(args, current );
            if( endOfArgument == std::string::npos )
            {
                endOfArgument = args.length();
            }

            std::string value = args.substr( current, endOfArgument - current );
            set( list.getItem(Test::ArgumentNumber<Index-1>()), value );
            current = endOfArgument + 1;
        }

        template <typename T>
        static void set( T& slot, const std::string& string )
        {
            slot = String::as<T>( string );
        }
    };

    template <typename ArgList>
    struct ArgSetter<ArgList, 0>
    {
        static void setArgs( ArgList& list, const std::string& args, std::string::size_type& current )
        {
            // Recursion base case.
        }
    };

    template <typename ArgList>
    class ArgumentsParser
    {
        PREVENT_COPY_AND_ASSIGNMENT( ArgumentsParser );
    public:
        ArgumentsParser( const Test::InvokeContext& context )
            : mContext( context )
        {
        }

        ArgList& parse()
        {
            const std::string& args = mContext.arguments();
            std::string::size_type location = 0u;
            Test::ArgSetter<ArgList, MetaBase::ListLength< typename ArgList::ArgumentTypes >::Value>::setArgs( mList, args, location );
            return mList;
        }

    private:
        const Test::InvokeContext& mContext;
        ArgList mList;
    };
}

#endif // TEST_ARGUMENTSPARSER_H__INCLUDED
