#pragma once

#include "Unitree.hpp"
#include <ostream>
#include <print>


///Represents a single entry in a unit type.
//If a unit is m/s^2, the base primitive would represent m.
//The baseconversion represents the conversion rate to the SI unit.
//Km has a 1 000 Converion to m
template<Rational Exponent, Rational BaseConversion>
struct BasePrimitiveUnit
{
    float value;
    template<Rational OldBaseConversion>
    explicit constexpr BasePrimitiveUnit<Exponent, BaseConversion>( BasePrimitiveUnit<Exponent, OldBaseConversion> OldValue )
    {
        value = OldValue.value * (OldBaseConversion / BaseConversion).to_float();
    }
    constexpr BasePrimitiveUnit( float value ): value(value) {}

    constexpr bool operator==( const BasePrimitiveUnit<Exponent, BaseConversion>& other ) const { return value == other.value; }
    constexpr bool operator!=( const BasePrimitiveUnit<Exponent,BaseConversion>& other ) const { return value == other.value; }
    constexpr bool operator<( const BasePrimitiveUnit<Exponent,BaseConversion>& other ) const { return value < other.value; }
    constexpr bool operator<=( const BasePrimitiveUnit<Exponent,BaseConversion>& other ) const { return value <= other.value; }
    constexpr bool operator>( const BasePrimitiveUnit<Exponent,BaseConversion>& other ) const { return value >= other.value; }
    constexpr bool operator>=( const BasePrimitiveUnit<Exponent,BaseConversion>& other ) const { return value >= other.value; }
};




