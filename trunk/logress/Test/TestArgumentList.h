#ifndef TEST_ARGUMENTLIST_H__INCLUDED
#define TEST_ARGUMENTLIST_H__INCLUDED

#include "Gen/GenScatterHierarchySequenced.h"
#include "MetaBase/MetaBaseTypeListNth.h"

#include <string>

namespace Test
{
    template < typename Types, template <typename> class StoreTraits >
    class ArgumentList;
}

// This is for storage of argument lists
template < typename Types, template <typename> class Traits >
class Test::ArgumentList
{
private:
    template <typename T, int N> struct Item {
        typename Traits<T>::StoreType value;
    };

    typedef Gen::ScatterHierarchySequenced< Item, Types > Storage;
    Storage mStore;

public:
    typedef Types ArgumentTypes;

    template <typename Index>
    typename Traits< typename MetaBase::Nth< Types, Index::Value >::Type >::ConstReturnType getItem(const Index& index) const
    {
        typedef Traits< typename MetaBase::Nth< Types, Index::Value >::Type > TraitsN;
        const Item< typename MetaBase::Nth< Types, Index::Value >::Type, Index::Value >& storeRef( mStore );
        return TraitsN::forConstReturn( storeRef.value );
    }

    template <typename Index>
    typename Traits< typename MetaBase::Nth< Types, Index::Value >::Type >::RefReturnType getItem(const Index& index)
    {
        typedef Traits< typename MetaBase::Nth< Types, Index::Value >::Type > TraitsN;
        Item< typename MetaBase::Nth< Types, Index::Value >::Type, Index::Value >& storeRef( mStore );
        return TraitsN::forRefReturn( storeRef.value );
    }
};

#endif // TEST_ARGUMENTLIST_H__INCLUDED
