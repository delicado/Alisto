#ifndef UTILITIES_H
#define UTILITIES_H

#include "config.h"

#include <string_view>
#include <cassert>
#include <cmath>
#include <iostream>

// math type specialization class
template <typename T>
struct TMath
{
};

template <>
struct TMath<float>
{
    static float Power( float a, float b )
    {
        return powf( a, b );
    }
};

template <>
struct TMath<double>
{
    static double Power( double a, double b )
    {
        return pow( a, b );
    }
};

template <typename T>
const T* WalkStringUntilNotOfRange( const T* begin, const T* end, int range_begin, int range_end )
{
    const T* ret = begin;
    while( ret < end )
    {
        if( *ret < range_begin || *ret > range_end )
            return ret;
        ++ret;
    }
    return ret;
}



template <typename T, typename Ret>
Ret ToInteger( const T* start, const T* end, const T** end_pos = nullptr )
{
    Ret ret = static_cast<Ret>(0);
    bool neg = false;
    if( start < end )
    {
        if( *start == '-' )
        {
            neg = true;
            start++;
        } else if( *start == '+' )
            start++;

        const T* cur = WalkStringUntilNotOfRange( start, end, '0', '9' );
        Ret l = static_cast<Ret>(1);
        for( const T* i = cur - 1; i >= start; --i, l *= 10 )
            ret += static_cast<Ret>( *i - '0' ) * l;
        if( neg )
            ret = -ret;
        if( end_pos )
            *end_pos = cur;
    }
    return ret;
}

template <typename T,typename Ret>
Ret ToDouble( const T* start, const T* end, const T** end_pos = nullptr )
{
    const T* cur = nullptr;
    Ret ret = ToInteger<T,Ret>( start, end, &cur );
    bool neg = false;
    if( ret < 0 )
    {
        ret = -ret;
        neg = true;
    }
    if( cur+1 < end )
    {
        if( *cur == '.' )
        {
            cur++;
            const T* e = WalkStringUntilNotOfRange( cur, end, '0', '9' );
            Ret d = 0.1;
            while( cur < e )
            {
                ret += Ret( *cur - '0' ) * d;
                cur++;
                d *= 0.1;
            }
        }
    }
    /*
    if( cur+1 < end )
    {
        if( *cur == 'E' || *cur == 'e' )
        {
            cur++;
            Ret p = ToInteger<T,Ret>( cur, end, &cur );
            if( p < static_cast<Ret>(0) )
                p = TMath<Ret>::Power( 0.1, -p );
            else p = TMath<Ret>::Power( 10, p );
            ret *= p;
        }
    }
    */
    if( end_pos )
        *end_pos = cur;
    if( neg )
        ret = -ret;
    return ret;
}

template <typename T>
const T* WalkStringUntil( const T* begin, const T* end, const T* sep, const T* sep_end )
{
    const T* ret = begin;
    while( ret < end )
    {
        for( const T* i = sep; i < sep_end; ++i )
        {
            if( *ret == *i )
                return ret;
        }
        ++ret;
    }
    return ret;
}

template <typename T>
const T* WalkStringUntilNotOf( const T* begin, const T* end, const T* sep, const T* sep_end )
{
    const T* ret = begin;
    bool exit = false;
    while( ret < end )
    {
        exit = true;
        for( const T* i = sep; i < sep_end; ++i )
        {
            if( *ret == *i )
            {
                exit = false;
                break;
            }
        }
        if( exit )
            return ret;
        ++ret;
    }
    return ret;
}

size_t ParseCommand(const char*& index, const char* end, char& command);
float ParseParam(const char*& index, const char* end, char &axis);
const char* NextParam(const char* index, const char* end);
#endif // UTILITIES_H
