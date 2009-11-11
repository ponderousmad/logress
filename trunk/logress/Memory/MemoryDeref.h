#ifndef MEMORY_DEREF_H__INCLUDED
#define MEMORY_DEREF_H__INCLUDED

namespace Memory
{
    template <typename T, typename Ptr>
    class Deref;
}

// This class is useful when defining policy based templates
// Since you may want to customize a template to have different
// types to store, pass and manipulate some base type you can
// sometimes use this to handle certain conversions.
//
// One example would be is if a template is storing a value
// using a shared pointer, but you want to have a
// function to access the value.  You might not be able to
// specify the dereference as part of the template implementation
// but if you can customize what type is returned, you can return
// one of these to have it do the dereference.
template <typename T, typename Ptr>
class Memory::Deref
{
    PREVENT_ASSIGNMENT( Deref );
public:
    Deref( const Ptr& ptr )
        : mPtr( ptr )
    {
    }

    Deref( const Deref& other )
        : mPtr( other.mPtr )
    {
    }

    operator T&() const
    {
        return *mPtr;
    }

private:
    Ptr mPtr;
};

#endif // MEMORY_DEREF_H__INCLUDED
