#include <cmath>

#include <QDebug>

template <typename T, int fractional_bits>
TFixedPoint< T, fractional_bits >::TFixedPoint()
{
}

template <typename T, int fractional_bits>
TFixedPoint< T, fractional_bits >::TFixedPoint(const TFixedPoint< T, fractional_bits > &t)
    : _type( t._type )
{
}


template <typename T, int fractional_bits>
TFixedPoint<T,fractional_bits>::TFixedPoint(T t)
    : _type( t )
{
}

template <typename T, int fractional_bits>
TFixedPoint<T,fractional_bits>::~TFixedPoint()
{

}

template <typename T, int fractional_bits>
const TFixedPoint< T, fractional_bits > &TFixedPoint<T, fractional_bits>::operator=(const TFixedPoint< T, fractional_bits > &t)
{
    _type = t._type;
    return _type;
}

template <typename T, int fractional_bits>
TFixedPoint<T,fractional_bits> TFixedPoint<T, fractional_bits>::operator+(const TFixedPoint<T,fractional_bits> &t) const
{
    return TFixedPoint<T, fractional_bits>(_type + t._type);
}

template <typename T, int fractional_bits>
TFixedPoint<T,fractional_bits> TFixedPoint<T, fractional_bits>::operator-(const TFixedPoint<T,fractional_bits> &t) const
{
    return TFixedPoint<T, fractional_bits>(_type - t._type);
}

template <typename T, int fractional_bits>
TFixedPoint<T,fractional_bits> TFixedPoint<T, fractional_bits>::operator*(const TFixedPoint<T, fractional_bits> &t) const
{
    return TFixedPoint<T, fractional_bits>((_type * t._type) >> fractional_bits );
}

template <typename T, int fractional_bits>
TFixedPoint<T,fractional_bits> TFixedPoint<T, fractional_bits>::operator/(const TFixedPoint<T, fractional_bits> &t) const
{
    return TFixedPoint<T, fractional_bits>((_type << fractional_bits) / t._type);
}


template <typename T, int fractional_bits>
template <int fbits>
TFixedPoint<T,fractional_bits> TFixedPoint<T, fractional_bits>::operator*(const TFixedPoint<T, fbits> &t) const
{
    qDebug() << _type << " : " << t.ToRaw() << " : " << ((_type * t.ToRaw()) >> fbits );
    return TFixedPoint<T, fractional_bits>((_type * t.ToRaw() ) >> fbits );
}


template <typename T, int fractional_bits>
void TFixedPoint<T, fractional_bits>::ConvertFloat(float t)
{
    constexpr int bit_count = 8 * sizeof(unsigned);
    constexpr float mf = float((unsigned(-1) >> (bit_count - fractional_bits)) + 1 );
    float intg;
    float frac = modff( t, &intg );
    T ifrac = mf * frac;
    _type = intg;
    _type <<= fractional_bits;
    _type |= ifrac;
}

template <typename T, int fractional_bits>
int TFixedPoint<T, fractional_bits>::ToInt() const
{
    return _type >> fractional_bits;
}

template <typename T, int fractional_bits>
float TFixedPoint<T, fractional_bits>::ToFloat() const
{
    constexpr int bit_count = 8 * sizeof(unsigned);
    constexpr unsigned ci = unsigned(-1) >> (bit_count - fractional_bits);
    constexpr float cf = 1.0f / float(ci + 1);
    float ret = float(_type >> fractional_bits);
    return ret + (cf * float(_type & ci));
}


template <typename T, int fractional_bits>
T TFixedPoint<T, fractional_bits>::ToRaw() const
{
    return _type;
}
