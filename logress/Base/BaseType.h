#ifndef BASE_TYPE_H__INCLUDED
#define BASE_TYPE_H__INCLUDED

#include <typeinfo>

namespace Base
{
    class Type;
}

class Base::Type
{
public:
    typedef const std::type_info TypeID;
    Type();
    Type( const TypeID& id );
    Type( const Type& other );
    Type& operator=( const Type& other );

    bool operator==( const Type& other ) const;

    // For use in standard containers.
    bool operator<( const Type& other ) const;
private:
    TypeID* mID;
};

#endif // BASE_TYPE_H__INCLUDED
