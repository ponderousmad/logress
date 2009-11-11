#ifndef TEST_ARGUMENTNUMBER_H__INCLUDED
#define TEST_ARGUMENTNUMBER_H__INCLUDED

namespace Test
{
    template < typename Types, template <typename> class StoreTraits >
    class ArgumentList;


    template <int N>
    struct ArgumentNumber
    {
        enum {
            Value = N
        };
    };
}

#endif // TEST_ARGUMENTNUMBER_H__INCLUDED
