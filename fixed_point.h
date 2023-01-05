#ifndef FIXPOINT_H
#define FIXPOINT_H

#include <cstdint>

template <typename T, int fractional_bits>
class TFixedPoint
{
    T   _type;

    inline TFixedPoint( T t );
public:
    TFixedPoint();
    inline TFixedPoint( const TFixedPoint& t );

    ~TFixedPoint();

    inline const TFixedPoint& operator= (const TFixedPoint& t);
    inline TFixedPoint operator+ (const TFixedPoint& t) const;
    inline TFixedPoint operator- (const TFixedPoint& t) const;
    inline TFixedPoint operator* (const TFixedPoint& t) const;
    inline TFixedPoint operator/ (const TFixedPoint& t) const;

    template <int fbits>
    inline TFixedPoint< T, fractional_bits> operator* (const TFixedPoint< T, fbits>& t ) const;

    inline void ConvertFloat( float t );

    inline int ToInt() const;
    inline float ToFloat() const;
    inline T ToRaw() const;
};

#include "fixed_point.inl"

typedef     TFixedPoint<int16_t,8>   fixed16;

#endif // FIXPOINT_H
