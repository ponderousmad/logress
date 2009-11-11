#ifndef METABASE_REMOVEREFERENCE_H__INCLUDED
#define METABASE_REMOVEREFERENCE_H__INCLUDED

namespace MetaBase {

    template <typename T>
    struct RemoveReference
    {
        typedef T Type;
    };

    template <typename T>
    struct RemoveReference<T&>
    {
        typedef T Type;
    };
}

#endif // METABASE_REMOVEREFERENCE_H__INCLUDED
