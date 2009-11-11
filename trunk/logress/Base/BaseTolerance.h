#ifndef BASE_TOLERANCE_H__INCLUDED
#define BASE_TOLERANCE_H__INCLUDED

namespace Base {
    inline bool equal( double a, double b, double tolerance )
    {
        double difference = a - b;
        return difference > 0.0 ? difference < tolerance : -difference < tolerance;
    }

    template< typename T >
    T clamp( T value, T min, T max )
    {
        return value < min ? min : value > max ? max : value;
    }

    template< typename T >
    T abs( T value )
    {
        return value < static_cast< T >( 0 ) ? -value : value;
    }
}


#endif // BASE_TOLERANCE_H__INCLUDED
