#ifndef METABASE_TYPELIST_H__INCLUDED
#define METABASE_TYPELIST_H__INCLUDED

#include "MetaBase/MetaBaseNullType.h"

namespace MetaBase {

    typedef NullType EmptyTypeList;

    template <typename ItemType, typename TailList = EmptyTypeList >
    struct TypeList
    {
        typedef ItemType Type;
        typedef TailList Tail;
    };
}

#define TYPELIST_1( T1 ) MetaBase::TypeList< T1 >
#define TYPELIST_2( T1, T2 ) MetaBase::TypeList< T1, TYPELIST_1( T2 ) >
#define TYPELIST_3( T1, T2, T3 ) MetaBase::TypeList< T1, TYPELIST_2( T2, T3 ) >
#define TYPELIST_4( T1, T2, T3, T4 ) MetaBase::TypeList< T1, TYPELIST_3( T2, T3, T4 ) >
#define TYPELIST_5( T1, T2, T3, T4, T5 ) MetaBase::TypeList< T1, TYPELIST_4( T2, T3, T4, T5 ) >
#define TYPELIST_6( T1, T2, T3, T4, T5, T6 ) MetaBase::TypeList< T1, TYPELIST_5( T2, T3, T4, T5, T6 ) >
#define TYPELIST_7( T1, T2, T3, T4, T5, T6, T7 ) MetaBase::TypeList< T1, TYPELIST_6( T2, T3, T4, T5, T6, T7 ) >
#define TYPELIST_8( T1, T2, T3, T4, T5, T6, T7, T8 ) MetaBase::TypeList< T1, TYPELIST_7( T2, T3, T4, T5, T6, T7, T8 ) >
#define TYPELIST_9( T1, T2, T3, T4, T5, T6, T7, T8, T9 ) MetaBase::TypeList< T1, TYPELIST_8( T2, T3, T4, T5, T6, T7, T8, T9 ) >
#define TYPELIST_10( T1, T2, T3, T4, T5, T6, T7, T8, T9, T10 ) MetaBase::TypeList< T1, TYPELIST_9( T2, T3, T4, T5, T6, T7, T8, T9, T10 ) >
#define TYPELIST_11( T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11 ) MetaBase::TypeList< T1, TYPELIST_10( T2, T3, T4, T5, T6, T7, T8, T9, T10, T11 ) >
#define TYPELIST_12( T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12 ) MetaBase::TypeList< T1, TYPELIST_11( T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12 ) >
#define TYPELIST_13( T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13 ) MetaBase::TypeList< T1, TYPELIST_12( T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13 ) >
#define TYPELIST_14( T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14 ) MetaBase::TypeList< T1, TYPELIST_13( T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14 ) >
#define TYPELIST_15( T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15 ) MetaBase::TypeList< T1, TYPELIST_14( T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15 ) >

#endif //METABASE_TYPELIST_H__INCLUDED
