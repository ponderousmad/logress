#ifndef METABASE_REMOVECONST_H__INCLUDED
#define METABASE_REMOVECONST_H__INCLUDED

namespace MetaBase {

    template <typename T>
    struct RemoveConst
    {
        typedef T Type;
    };

    template <typename T>
    struct RemoveConst<const T>
    {
        typedef T Type;
    };
}

#endif // METABASE_REMOVECONST_H__INCLUDED
