#ifndef METABASE_TYPELISTNTH_H__INCLUDED
#define METABASE_TYPELISTNTH_H__INCLUDED

namespace MetaBase {

    template <class List, int N>
    struct Nth
    {
        typedef typename Nth< typename List::Tail, N-1 >::Type Type;
    };

    template <class List>
    struct Nth<List, 0>
    {
        typedef typename List::Type Type;
    };
}

#endif //METABASE_TYPELISTNTH_H__INCLUDED
