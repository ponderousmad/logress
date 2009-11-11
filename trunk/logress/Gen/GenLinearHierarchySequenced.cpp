/* ---------------------------------------------------------------
 * Copyright (c) Adrian Smith.
 * Licensed under the MIT license. See license.txt at project root.
 * --------------------------------------------------------------- */
#include "Base/Top.h"

#include "Gen/GenLinearHierarchySequenced.h"

#include "Gen/GenTestSwitch.h"

#ifdef COMPILE_GEN_TESTS

#include "MetaBase/MetaBaseTypeListLength.h"

#include <iostream>

namespace {
    class StorageVisitor
    {
    public:
        StorageVisitor() : isFirst( true ) {}

        ~StorageVisitor() { std::cout << std::endl; }

        template <typename T>
        void visit( const T& value ) {
            std::cout << ( isFirst ? "" : ", " ) << value;
            isFirst = false;
        }

    private:
        bool isFirst;
    };

    template <typename T> struct Default {};
    template <> struct Default<int> { enum { Value = 5 }; };
    template <> struct Default<double> { static const double Value; };
    const double Default<double>::Value = 5.5;

    template <typename T, class Base, bool Forward>
    struct Item : public Base
    {
        Item()
            : value( Default<T>::Value )
        {
        }

        void accept( StorageVisitor& visitor )
        {
            visitor.visit( value );
            Base::accept( visitor );
        }

    private:
        T value;
    };

    template <typename T, class Base>
    struct Item<T, Base, false>
    {
        Item()
            : value( Default<T>::Value )
        {
        }

        void accept( StorageVisitor& visitor )
        {
            visitor.visit( value );
        }

    private:
        T value;
    };

    template <typename Typelist>
    class StorageSequence
    {
    private:
        enum { ListLength = MetaBase::ListLength<Typelist>::Value };

        template <typename T, int N, class Base>
        struct LinItem
            : public Item< T, Base, ( N < ListLength-1 ) >
        {
        };
        typedef Gen::LinearHierarchySequenced< LinItem, Typelist > Store;

        Store mStore;

    public:

        void accept( StorageVisitor& visitor )
        {
            mStore.accept( visitor );
        }
    };
}

namespace GenTests {
    void testLinearHierarchySequence()
    {
        StorageSequence< TYPELIST_2( int, double ) > storeIntDouble;

        StorageVisitor v;
        storeIntDouble.accept( v );
    }
}

#endif // COMPILE_GEN_TESTS
