
/*
 * This file is part of Unitree.
 *
 * Unitree is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Unitree is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Unitree. If not, see <https://www.gnu.org/licenses/>.
 */
#pragma once
#include<concepts>
#include<iostream>
#include <tuple>
#include <iostream>
#include <ostream> 
#include <numeric> 
#include<string>


#pragma region Macros
/*
 * Macro declarations to ease the proccess of templated class and function declarations.
 * 
 * The following list is description of every keyword used in the macros,
 * numbered in the order they should appear when combined
 * ( 1 -> First/Most to the right)
 * 
 * 1-> SHORTHAND:
 *      Describes a macro intended for aiding class and function declarations using generics.
 *      Macros without this suffix soley have the intension to be used while declaring macros. 
 * 2-> Actions:
 *      Describes the a type of action to be preformed on the type.
 *      Examples:
 *          Addition,
 *          Subtraction
 * 2-> UNIT(S):
 *      Refers to the physical SI unit.
 *      When used in plural its describes a listing of each si unit in a row.
 *      Meters, Seconds, ..., Candela
 * 3-> Type:
 *      Refers to a type that the marco acts on
 *      
 *      Examples:
 *          UnitType<UNITS>
 *          Vector..
 *          Matrix..
 *          
 * 4-> TEMPLATE:
 *      If the macro is intended to be used in a template declaration.
 *      Most macros have a template counter part, they differ in that the tempalte version
 *      specifies type, but the regular version does not.
 *      
 *      Example:
 *          template<TEMPLATE_UNIT_SHORTHAND, uint Power> //TEMPLATE_UNIT_SHORTHAND -> Rational Meters, Rational Seconds ..
 *          struct ResultingPowerUnit<TYPE_UNIT_SHORTHAND, Power>   //TYPE_UNIT_SHORTHAND -> Meters, Seconds..
 *          {..}
 * 5-> PREFIX(ED):
 *      Takes in a prefix as argument and places in in front of the UNITS, to allow multiple instances of the UNITS for opperations.
 *      When using both the TEMPLATE and regular prefixed marcos, the prefixes must match.
 *      
 *      Difference PREFIX and PREFIXED->
 *          Macros without the "ED" suffix only used when declaring other macros. 
 *      
*/



#define PREFIX_TEMPLATE_UNIT(PREFIX, UNIT) Rational PREFIX##UNIT
#define PREFIX_UNIT(PREFIX, UNIT) PREFIX##UNIT

#define PREFIXED_TEMPLATE_UNITS_SHORTHAND(PREFIX) \
    PREFIX_TEMPLATE_UNIT(PREFIX, Meters), \
    PREFIX_TEMPLATE_UNIT(PREFIX, Seconds), \
    PREFIX_TEMPLATE_UNIT(PREFIX, Kilogram), \
    PREFIX_TEMPLATE_UNIT(PREFIX, Ampere), \
    PREFIX_TEMPLATE_UNIT(PREFIX, Kelvin), \
    PREFIX_TEMPLATE_UNIT(PREFIX, Mol), \
    PREFIX_TEMPLATE_UNIT(PREFIX, Candela)

#define PREFIXED_UNITS_SHORTHAND(PREFIX) \
    PREFIX_UNIT(PREFIX, Meters), \
    PREFIX_UNIT(PREFIX, Seconds), \
    PREFIX_UNIT(PREFIX, Kilogram), \
    PREFIX_UNIT(PREFIX, Ampere), \
    PREFIX_UNIT(PREFIX, Kelvin), \
    PREFIX_UNIT(PREFIX, Mol), \
    PREFIX_UNIT(PREFIX, Candela)

#define TEMPLATE_UNIT_SHORTHAND PREFIXED_TEMPLATE_UNITS_SHORTHAND()
#define UNIT_SHORTHAND PREFIXED_UNITS_SHORTHAND()
#define TYPE_UNIT_SHORTHAND TypeUnit<UNIT_SHORTHAND>

#define PREFIXED_TYPE_UNIT_SHORTHAND(PREFIX) TypeUnit<PREFIXED_UNITS_SHORTHAND(PREFIX)>
#define mScalarUnit TypeUnit<0, 0, 0, 0, 0, 0, 0>


#define PREFIX_TEMPLATE_ARITHEMETIC_OR_UNIT_TYPE(Prefix) ArithemeticOrUnit Prefix##Type


#define TEMPLATE_MATRIX_2X2_UNIT_SHORTHAND \
    PREFIX_TEMPLATE_ARITHEMETIC_OR_UNIT_TYPE(a_1), \
    PREFIX_TEMPLATE_ARITHEMETIC_OR_UNIT_TYPE(a_2), \
    PREFIX_TEMPLATE_ARITHEMETIC_OR_UNIT_TYPE(b_1), \
    PREFIX_TEMPLATE_ARITHEMETIC_OR_UNIT_TYPE(b_2) \

#define TEMPLATE_MATRIX_3X3_UNITSHORTHAND \
    PREFIX_TEMPLATE_ARITHEMETIC_OR_UNIT_TYPE(a_1), \
    PREFIX_TEMPLATE_ARITHEMETIC_OR_UNIT_TYPE(a_2), \
    PREFIX_TEMPLATE_ARITHEMETIC_OR_UNIT_TYPE(a_3), \
    PREFIX_TEMPLATE_ARITHEMETIC_OR_UNIT_TYPE(b_1), \
    PREFIX_TEMPLATE_ARITHEMETIC_OR_UNIT_TYPE(b_2), \
    PREFIX_TEMPLATE_ARITHEMETIC_OR_UNIT_TYPE(b_3), \
    PREFIX_TEMPLATE_ARITHEMETIC_OR_UNIT_TYPE(c_1), \
    PREFIX_TEMPLATE_ARITHEMETIC_OR_UNIT_TYPE(c_2), \
    PREFIX_TEMPLATE_ARITHEMETIC_OR_UNIT_TYPE(c_3) \


#define UNIT_ADDITION_SHORTHAND( PREFIX_1, PREFIX_2 ) TypeUnit<PREFIX_1##Meters + PREFIX_2##Meters, PREFIX_1##Seconds + PREFIX_2##Seconds,  PREFIX_1##Kilogram + PREFIX_2##Kilogram, PREFIX_1##Ampere + PREFIX_2##Ampere, PREFIX_1##Kelvin + PREFIX_2##Kelvin, PREFIX_1##Mol + PREFIX_2##Mol, PREFIX_1##Candela + PREFIX_2##Candela>
#define UNIT_SUBTRACTION_SHORTHAND( PREFIX_1, PREFIX_2) TypeUnit<PREFIX_1##Meters - PREFIX_2##Meters, PREFIX_1##Seconds - PREFIX_2##Seconds,  PREFIX_1##Kilogram - PREFIX_2##Kilogram, PREFIX_1##Ampere - PREFIX_2##Ampere, PREFIX_1##Kelvin - PREFIX_2##Kelvin, PREFIX_1##Mol - PREFIX_2##Mol, PREFIX_1##Candela - PREFIX_2##Candela>
#define UNIT_EQUALITY_SHORTHAND( PREFIX_1, PREFIX_2) PREFIX_1##Meters != PREFIX_2##Meters || PREFIX_1##Seconds != PREFIX_2##Seconds ||  PREFIX_1##Kilogram != PREFIX_2##Kilogram || PREFIX_1##Ampere != PREFIX_2##Ampere || PREFIX_1##Kelvin != PREFIX_2##Kelvin || PREFIX_1##Mol != PREFIX_2##Mol || PREFIX_1##Candela != PREFIX_2##Candela
#define UNIT_POWER_SHORTHAND( POWER ) TypeUnit<Meters * POWER, Seconds * POWER, Kilogram * POWER, Ampere * POWER, Kelvin * POWER, Mol * POWER, Candela * POWER>
#pragma endregion
#pragma region Rational
struct Rational
{
    int Numerator;
    unsigned int Denominator; 

    // Default constructor.
    constexpr Rational() : Numerator(0), Denominator(1) {}

    // Parameterized constructor.
    constexpr Rational(int numerator, unsigned int denominator) : Numerator(numerator), Denominator(denominator)
    {
        if (Denominator == 0)
        {
            throw "Denominator cannot be zero!";
        }
    }

    // Integer-to-Rational constructor.
    constexpr Rational(int value) : Numerator(value), Denominator(1) {}

    // Simplify the rational number.
    constexpr Rational simplified() const
    {
        unsigned int gcd = std::gcd(Numerator, Denominator);
        return {Numerator / static_cast<int>(gcd), Denominator / gcd};
    }

    // Addition operator.
    constexpr Rational operator+(const Rational &other) const
    {
        return Rational( Numerator * static_cast<int>(other.Denominator) + 
            other.Numerator * static_cast<int>(Denominator),
            Denominator * other.Denominator)
            .simplified();
    }

    // Subtraction operator.
    constexpr Rational operator-(const Rational &other) const
    {
        return Rational( Numerator * static_cast<int>(other.Denominator) -
            other.Numerator * static_cast<int>(Denominator),Denominator * other.Denominator)
            .simplified();
    }

    // Multiplication operator.
    constexpr Rational operator*(const Rational &other) const
    {
        return Rational( Numerator * other.Numerator, Denominator * other.Denominator)
            .simplified();
    }

    constexpr Rational operator/(const Rational &other) const
    {
        return *this * Rational(other.Denominator, static_cast<unsigned int>(other.Numerator));
    }

    constexpr bool operator==(const Rational &other) const
    {
        return Numerator * static_cast<int>(other.Denominator) ==
            other.Numerator * static_cast<int>(Denominator);
    }

    // Inequality operator.
    constexpr bool operator!=(const Rational &other) const
    {
        return !(*this == other);
    }

    // Less-than operator.
    constexpr bool operator<(const Rational &other) const
    {
        return Numerator * static_cast<int>(other.Denominator) <
            other.Numerator * static_cast<int>(Denominator);
    }

    // Greater-than operator.
    constexpr bool operator>(const Rational &other) const
    {
        return other < *this;
    }

    // Less-than-or-equal-to operator.
    constexpr bool operator<=(const Rational &other) const
    {
        return !(*this > other);
    }

    constexpr bool operator>=(const Rational &other) const
    {
        return !(*this < other);
    }

    // Convert to string representation.
    constexpr std::string to_string() const
    {
        if (Denominator == 1)
        {
            return std::to_string(Numerator);
        }
        return std::to_string(Numerator) + "/" + std::to_string(Denominator);
    }

    // Convert to absolute value string representation.
    constexpr std::string to_string_absolute_value() const
    {
        Rational rSelf = {std::abs(Numerator), Denominator};
        if (rSelf.Denominator == 1)
        {
            return std::to_string(rSelf.Numerator);
        }
        return std::to_string(rSelf.Numerator) + "/" + std::to_string(rSelf.Denominator);
    }

    // Overload for output stream.
    friend std::ostream &operator<<(std::ostream &os, const Rational &rational)
    {
        if (rational.Denominator == 1)
        {
            os << rational.Numerator;
        }
        else
        {
            os << rational.Numerator << "/" << rational.Denominator;
        }
        return os;
    }
};
#pragma endregion
#pragma region Concepts and forward declarations
//Set default value of is_type_unit to false
template<typename>
struct is_type_unit : std::false_type {};

template<TEMPLATE_UNIT_SHORTHAND>
struct TypeUnit;//Forward declaration
template<typename T>
concept Arithmetic = std::is_arithmetic_v<T>;



//Flag unit struct as is_type_unit true
template<TEMPLATE_UNIT_SHORTHAND>
struct is_type_unit<TYPE_UNIT_SHORTHAND> : std::true_type {};

template<typename T>
constexpr bool is_unit_v = is_type_unit<T>::value;

template<typename T>
concept ArithemeticOrUnit = std::is_arithmetic_v<T> || is_unit_v<T>;


template<typename T>
concept isUnit = is_unit_v<T>;

template <typename x, typename y>
concept VectorHasArithmeticOrUnitBase = (std::is_arithmetic_v<x> && std::is_arithmetic_v<y>)
    || ( isUnit<x> && isUnit<y> );

template<typename T>
concept isScalarUnit = std::is_same_v<T, mScalarUnit>;

template <typename T>
concept ArithemeticOrScalarUnit = std::is_arithmetic_v<T> || isScalarUnit<T>;

template<ArithemeticOrUnit xType, ArithemeticOrUnit yType>
requires VectorHasArithmeticOrUnitBase<xType, yType>
struct Vector;//Forward declaration

template <typename T1, typename T2>
concept SameType = std::is_same_v<T1, T2>;

template<ArithemeticOrUnit Unit1, ArithemeticOrUnit Unit2>
struct ResultingMultiplicationUnit;

template<TEMPLATE_UNIT_SHORTHAND,PREFIXED_TEMPLATE_UNITS_SHORTHAND(Other)>
struct ResultingMultiplicationUnit<TYPE_UNIT_SHORTHAND,PREFIXED_TYPE_UNIT_SHORTHAND(Other)>
{   
    using type = UNIT_ADDITION_SHORTHAND(,Other);
};

template<TEMPLATE_UNIT_SHORTHAND,Arithmetic Type2>
struct ResultingMultiplicationUnit<TYPE_UNIT_SHORTHAND,Type2>
{
    using type = TYPE_UNIT_SHORTHAND;
};

template<ArithemeticOrUnit Unit1, ArithemeticOrUnit Unit2>
struct ResultingDivisionUnit;

template<TEMPLATE_UNIT_SHORTHAND,PREFIXED_TEMPLATE_UNITS_SHORTHAND(Other)>
struct ResultingDivisionUnit<TYPE_UNIT_SHORTHAND,PREFIXED_TYPE_UNIT_SHORTHAND(Other)>
{
    using type = UNIT_SUBTRACTION_SHORTHAND(,Other);
};

template<TEMPLATE_UNIT_SHORTHAND,Arithmetic Type2>
struct ResultingDivisionUnit<TYPE_UNIT_SHORTHAND,Type2>
{
    using type = TYPE_UNIT_SHORTHAND;
};

template<ArithemeticOrUnit Unit1, int Unit2>
struct ResultingPowerUnit;

template<TEMPLATE_UNIT_SHORTHAND, int Power>
struct ResultingPowerUnit<TYPE_UNIT_SHORTHAND, Power>
{
    using type = UNIT_POWER_SHORTHAND( Power );
};




#pragma endregion


#pragma region Units

//Represents the exponents of each unit
//Meters,Seconds,Kilogram,Ampere,Kelvin,Mol,Candela
template <TEMPLATE_UNIT_SHORTHAND>
//A struct representing a unit as the combination of si unit components
struct TypeUnit
{
    double Value;
    //Flagged 
    //temporary
    double v() const{
        return Value;
    }
    TypeUnit() : Value(0.0) {}
    TypeUnit( double value ) : Value(value) {}
#pragma region TypeUnit operators 
    //Implicit double conversion
    //Flagged should probably only work if type is scalar
    //result in weird conversion when taking a unit to the nth power, and seting a existing unit of different type 
    //to this it implicitly converts the nth power to a double and then assigns the existing unit the double with a nother 
    //implicit conversion
    /*
    operator double()const
    {
        return Value;
    }*/
    template <PREFIXED_TEMPLATE_UNITS_SHORTHAND(Other)>
    inline PREFIXED_TYPE_UNIT_SHORTHAND(Other) operator=( PREFIXED_TYPE_UNIT_SHORTHAND(Other)& other )
    {
        if constexpr(!( UNIT_EQUALITY_SHORTHAND(,Other)) )
        {
            static_assert("Attemptet to assign different TypeUnit to existing TypeUnit\n");
        }
        Value = other.Value;
        return *this;
    }
    inline TYPE_UNIT_SHORTHAND operator=( const double value ) const
    {
        TYPE_UNIT_SHORTHAND TypeUnit = { value };
        return TypeUnit;
    }
    inline bool operator==( TYPE_UNIT_SHORTHAND& other ) const
    {
        return this->Value == other.Value;
    }
    inline bool operator!=( TYPE_UNIT_SHORTHAND& other ) const
    {
        return this->Value != other.Value;
    }
    inline bool operator>=( TYPE_UNIT_SHORTHAND& other ) const
    {
        return this->Value >= other.Value;
    }
    inline bool operator<=( TYPE_UNIT_SHORTHAND& other ) const
    {
        return this->Value <= other.Value;
    }
    inline bool operator<( TYPE_UNIT_SHORTHAND& other ) const
    {
        return this->Value < other.Value;
    }
    inline bool operator>( TYPE_UNIT_SHORTHAND& other ) const
    {
        return this->Value > other.Value;
    }
    inline TYPE_UNIT_SHORTHAND operator+( TYPE_UNIT_SHORTHAND& Other ) const
    {
        return { this->Value + Other.Value };
    }
    inline TYPE_UNIT_SHORTHAND operator-( TYPE_UNIT_SHORTHAND& other ) const
    {
        return { this->Value - other.Value };
    }
    template <PREFIXED_TEMPLATE_UNITS_SHORTHAND(Other)>
    constexpr auto operator*(const PREFIXED_TYPE_UNIT_SHORTHAND(Other)& other) const
    {
        //Empty first prefix
        return UNIT_ADDITION_SHORTHAND(,Other)( this->Value * other.Value);
    }
    template <PREFIXED_TEMPLATE_UNITS_SHORTHAND(Other)>
    constexpr auto operator/( const PREFIXED_TYPE_UNIT_SHORTHAND(Other)& other )const
    {
        //Empty first prefix
        return UNIT_SUBTRACTION_SHORTHAND(,Other)( Value / other.Value );
    }
    template<Arithmetic Scalar>
    constexpr TYPE_UNIT_SHORTHAND operator*( Scalar& scalar ) const
    {
        return { this->Value * scalar };
    }
    template<Arithmetic Scalar>
    constexpr TYPE_UNIT_SHORTHAND operator/( Scalar& scalar ) const
    {
        return { this->Value / scalar };
    }

#pragma region Semi_Unit_Safety operators

    #define SEMI_UNIT_SAFETY_ERROR "\nCompile error, TypeUnit-ArithmeticTypes operations are only allowed when SEMI_UNIT_SAFETY is enabled.\n"
    inline TYPE_UNIT_SHORTHAND operator+( double valueOther ) const
    {
        #ifdef SEMI_UNIT_SAFETY
        return { this->Value + valueOther };
        #else
        static_assert( false, SEMI_UNIT_SAFETY_ERROR );
        #endif
    }
    inline TYPE_UNIT_SHORTHAND operator-( double valueOther ) const
    {
        #ifdef SEMI_UNIT_SAFETY
        return { this->Value - valueOther };
        #else
        static_assert( false, SEMI_UNIT_SAFETY_ERROR );
        #endif
    }
    //double gets looked at as scalar
    inline TYPE_UNIT_SHORTHAND operator*( double valueOther ) const
    {
        #ifdef SEMI_UNIT_SAFETY
        return { this->Value * valueOther };
        #else
        static_assert( false, SEMI_UNIT_SAFETY_ERROR );
        #endif
    }
    inline TYPE_UNIT_SHORTHAND operator/( double valueOther ) const
    {
        #ifdef SEMI_UNIT_SAFETY
        return { this->Value / valueOther };
        #else
        static_assert( false, SEMI_UNIT_SAFETY_ERROR );
        #endif
    }
    inline bool operator==( double valueOther ) const
    {
        bool Result;
        #ifdef SEMI_UNIT_SAFETY
        Result = valueOther == Value;
        #else
        static_assert( false, SEMI_UNIT_SAFETY_ERROR );
        #endif

        return Result;
    }
    inline bool operator!=( double valueOther ) const
    {
        bool Result;
        #ifdef SEMI_UNIT_SAFETY
        Result = valueOther != Value;
        #else
        static_assert( false, SEMI_UNIT_SAFETY_ERROR );
        #endif

        return Result;
    }
    inline bool operator<( double valueOther ) const
    {
        bool Result;
        #ifdef SEMI_UNIT_SAFETY
        Result = valueOther < Value;
        #else
        static_assert( false, SEMI_UNIT_SAFETY_ERROR );
        #endif

        return Result;
    }
    inline bool operator>( double valueOther ) const
    {
        bool Result;
        #ifdef SEMI_UNIT_SAFETY
        Result = valueOther > Value;
        #else
        static_assert( false, SEMI_UNIT_SAFETY_ERROR );
        #endif

        return Result;
    }
    inline bool operator>=( double valueOther ) const
    {
        bool Result;
        #ifdef SEMI_UNIT_SAFETY
        Result = valueOther >= Value;
        #else
        static_assert( false, SEMI_UNIT_SAFETY_ERROR );
        #endif

        return Result;
    }
    inline bool operator<=( double valueOther ) const
    {
        bool Result;
        #ifdef SEMI_UNIT_SAFETY
        Result = valueOther <= Value;
        #else
        static_assert( false, SEMI_UNIT_SAFETY_ERROR );
        #endif

        return Result;
    }
#pragma endregion
    template <PREFIXED_TEMPLATE_UNITS_SHORTHAND(First),PREFIXED_TEMPLATE_UNITS_SHORTHAND(Second)>
    constexpr auto operator*( const Vector<PREFIXED_TYPE_UNIT_SHORTHAND(First),PREFIXED_TYPE_UNIT_SHORTHAND(Second)> Other )
    {
        //When multlipying a unit scalar with a vector, thus s * v, we return v * s, wich is defined in the Vector struct.
        return Other * Value;
    }
    // Overload for output stream.
    friend std::ostream &operator<<(std::ostream &os, const TYPE_UNIT_SHORTHAND &unit)
    {
        os << unit.get_units_to_string<false>();
        return os;
    }
#pragma endregion
    template<bool isVerbose>
    static constexpr std::array<const char*,7> get_unit_names()
    {
        if constexpr( isVerbose )
        {
            return {"Meters", "Seconds", "Kilograms", "Amperes", "Kelvin", "Mol", "Candela"};
        }
        return {"m", "s", "kg", "A", "K", "mol", "cd"};
    }

    inline void print_units_verbose() const
    {
        constexpr bool isVerbose = true;
        std::cout<<get_units_to_string<isVerbose>()<<"\n";
    }
    inline void print_units() const
    {
        constexpr bool isVerbose = false;
        std::cout<<get_units_to_string<isVerbose>()<<"\n";
    }
    template<bool isVerbose>
    constexpr std::string get_units_to_string() const 
    {
        constexpr std::array<Rational, 7> exponents = {Meters, Seconds, Kilogram, Ampere, Kelvin, Mol, Candela};
        constexpr std::array<const char*, 7> unitNames = get_unit_names<isVerbose>();

        std::string result = "Units: "+ std::to_string(Value) + " ";

        bool ThereAreNegativeExponents = false;
        // Process positive exponents
        for (size_t i = 0; i < exponents.size(); ++i)
        {
            if (exponents[i] > 0) 
            {
                result += std::string(unitNames[i]);
                if (exponents[i] != 1 )
                {
                    result += "^" + exponents[i].to_string();
                }
                result += "*";
            }
            else if( exponents[i] < 0 )
            {
                ThereAreNegativeExponents = true;
            }
        }
        //Remove last * sign
        result.pop_back();

        if( ThereAreNegativeExponents )
        {
            result += "/";
            // Process negative exponents
            for (size_t i = 0; i < exponents.size(); ++i)
            {
                if (exponents[i] < 0) 
                {
                    result += std::string(unitNames[i]);
                    if (exponents[i] != -1) 
                    {
                        //Make negetive exponent positive since we are already dividing
                        result += "^" + exponents[i].to_string_absolute_value();
                    }
                    result += "*";
                }
            }
            //Remove last * sign
            result.pop_back();
        }


        if (result == "Units: ") result += "1"; // If no units are present
        return result;
    }
};

///namespace extension functions acting on Type unit
namespace uExt
{
    template <TEMPLATE_UNIT_SHORTHAND>
    auto square( TYPE_UNIT_SHORTHAND value )
    {
        using ResultingUnit = typename ResultingMultiplicationUnit<TYPE_UNIT_SHORTHAND,TYPE_UNIT_SHORTHAND>::type;
        ResultingUnit Result = { value.Value * value.Value };
        return Result;
    }
    template <int Exponent,TEMPLATE_UNIT_SHORTHAND>
    auto power_lg( TYPE_UNIT_SHORTHAND unit )
    {
        //https://en.wikipedia.org/wiki/Exponentiation_by_squaring
        using ResultingUnit = typename ResultingPowerUnit<TYPE_UNIT_SHORTHAND,Exponent>::type;
        // Recursive exponentiation by squaring
        auto fast_power = [](double base, uint exp) -> double 
        {
            double result = 1.0;
            while (exp > 0)
            {
                if (exp % 2 == 1) 
                { // If odd, multiply the result
                    result *= base;
                }
                base *= base; // Square the base
                exp /= 2;     // Halve the exponent
            }
            return result;
        };

        double Value = fast_power(unit.Value, Exponent);

        // Create and return the resulting unit
        return ResultingUnit{Value};
    }

    template <int Exponent, TEMPLATE_UNIT_SHORTHAND>
    auto power_sm( TYPE_UNIT_SHORTHAND& unit )
    {
        using ResultingUnit = typename ResultingPowerUnit<TYPE_UNIT_SHORTHAND,Exponent>::type;
        double Value = 1;
        constexpr bool PowerIsPositive = Exponent > 0 ? true : false;
        constexpr int UpperBound = PowerIsPositive ? Exponent : -Exponent;
        for( int index = 0 ; index < UpperBound ; index++ )
        {
            Value = Value * unit.Value;
        }
        ResultingUnit Result;
        if constexpr ( PowerIsPositive )
        {
            Result.Value = Value;
            return Result;
        }
        else
        {
            Result.Value = 1/Value;
            return Result;
        }
    }
    //Flagged
    //Gives wrong result with negative exponents;
    template <int Exponent, TEMPLATE_UNIT_SHORTHAND>
    auto power( TYPE_UNIT_SHORTHAND unit )
    {
        if constexpr ( Exponent > 10  || Exponent < -10 )
        {
            return power_lg<Exponent>( unit );
        }

        return power_sm<Exponent>( unit );
    }
}

namespace Unit
{
    //Flagged
    //Maybe be incorrect, still need to be checked, written by chatgpt
    // Base units (for reference)
    using Scalar = TypeUnit<0, 0, 0, 0, 0, 0, 0>;  // Dimensionless
    using Radian = Scalar;
    using Meter = TypeUnit<1, 0, 0, 0, 0, 0, 0>;   // Length
    using Seconds = TypeUnit<0, 1, 0, 0, 0, 0, 0>; // Time
    using Kilogram = TypeUnit<0, 0, 1, 0, 0, 0, 0>; // Mass
    using Ampere = TypeUnit<0, 0, 0, 1, 0, 0, 0>;  // Electric current
    using Kelvin = TypeUnit<0, 0, 0, 0, 1, 0, 0>;  // Temperature
    using Mol = TypeUnit<0, 0, 0, 0, 0, 1, 0>;     // Amount of substance
    using Candela = TypeUnit<0, 0, 0, 0, 0, 0, 1>; // Luminous intensity

    // Derived units
    using SquareMeter = typename ResultingMultiplicationUnit<Meter, Meter>::type; // m^2
    using CubeMeter = typename ResultingMultiplicationUnit<SquareMeter, Meter>::type; // m^3

    // Velocity and Acceleration
    using Velocity = typename ResultingDivisionUnit<Meter, Seconds>::type; // m/s
    using Acceleration = typename ResultingDivisionUnit<Velocity, Seconds>::type; // m/s^2
    using Jerk = typename ResultingDivisionUnit<Acceleration, Seconds>::type; // m/s^3

    // Force, Work, Power
    using Newton = typename ResultingMultiplicationUnit<Acceleration, Kilogram>::type; // N = kg·m/s^2
    using Force = Newton;
    using Work = typename ResultingMultiplicationUnit<Newton, Meter>::type; // J = N·m
    using Power = typename ResultingDivisionUnit<Work, Seconds>::type; // W = J/s

    // Pressure
    using Pascal = typename ResultingDivisionUnit<Newton, SquareMeter>::type; // Pa = N/m^2

    // Electromagnetism
    using Coulomb = typename ResultingMultiplicationUnit<Seconds, Ampere>::type; // C = A·s
    using Volt = typename ResultingDivisionUnit<Work, Coulomb>::type; // V = J/C
    using Ohm = typename ResultingDivisionUnit<Volt, Ampere>::type; // Ω = V/A
    using Siemens = typename ResultingDivisionUnit<Scalar, Ohm>::type; // S = 1/Ω
    using Farad = typename ResultingDivisionUnit<Coulomb, Volt>::type; // F = C/V
    using Henry = typename ResultingMultiplicationUnit<Ohm, Seconds>::type; // H = Ω·s
    using Weber = typename ResultingMultiplicationUnit<Volt, Seconds>::type; // Wb = V·s
    using Tesla = typename ResultingDivisionUnit<Weber, SquareMeter>::type; // T = Wb/m^2

    // Optics
    using Lumen = typename ResultingMultiplicationUnit<Candela, Scalar>::type; // Lumen = cd·sr
    using Lux = typename ResultingDivisionUnit<Lumen, SquareMeter>::type; // lx = lm/m^2

    // Thermodynamics
    using Entropy = typename ResultingDivisionUnit<Work, Kelvin>::type; // J/K
    using SpecificHeatCapacity = typename ResultingDivisionUnit<Entropy, Kilogram>::type; // J/(kg·K)
    using ThermalConductivity = typename ResultingDivisionUnit<Power, typename ResultingMultiplicationUnit<Meter, Kelvin>::type>::type; // W/(m·K)

    // Chemistry
    using Concentration = typename ResultingDivisionUnit<Mol, CubeMeter>::type; // mol/m^3
    using CatalyticActivity = typename ResultingDivisionUnit<Mol, Seconds>::type; // mol/s

    // Additional Mechanics
    using Momentum = typename ResultingMultiplicationUnit<Velocity, Kilogram>::type; // kg·m/s
    using Impulse = typename ResultingMultiplicationUnit<Force, Seconds>::type; // N·s
    using AngularVelocity = typename ResultingDivisionUnit<Radian, Seconds>::type; // rad/s
    using AngularAcceleration = typename ResultingDivisionUnit<AngularVelocity, Seconds>::type; // rad/s^2

    // Radiation and Photonics
    using Gray = typename ResultingDivisionUnit<Work, Kilogram>::type; // Gy = J/kg (Absorbed dose)
    using Sievert = Gray; // Sv = Gy (Equivalent dose)

    // Advanced Derived Units
    using StefanBoltzmannConstant = typename ResultingDivisionUnit<Power, typename ResultingMultiplicationUnit<SquareMeter, typename ResultingPowerUnit<Kelvin, 4>::type>::type>::type; // W/(m^2·K^4)
    using PlanckConstant = typename ResultingMultiplicationUnit<Work, Seconds>::type; // J·s
    using BoltzmannConstant = typename ResultingDivisionUnit<Entropy, Kelvin>::type; // J/K
    using GasConstant = typename ResultingDivisionUnit<Work, typename ResultingMultiplicationUnit<Mol, Kelvin>::type>::type; // J/(mol·K)
}

   
namespace Constants
{
    using namespace Unit;
    const Radian Pi =   3.14159265358979323846;
}





template<ArithemeticOrUnit xType, ArithemeticOrUnit yType>
requires VectorHasArithmeticOrUnitBase<xType, yType>
struct Vector2X2
{
    public:
        xType x;
        yType y;

        void print_verbose()
        {
            if constexpr ( std::is_arithmetic_v<xType> )
            {
                std::cout<<"x --> "<< x <<"\n";
                std::cout<<"y --> "<< y <<"\n";
            }
            else
            {
                std::cout<<"x --> ";
                x.PrintUnitsVerbose();

                std::cout<<"y --> ";
                y.PrintUnitsVerbose();
            }
            std::cout<<"\n\n";
        }
        void print()
        {
            if constexpr ( std::is_arithmetic_v<xType> )
            {
                std::cout<<"x --> "<< x <<"\n";
                std::cout<<"y --> "<< y <<"\n";
            }
            else
            {
                std::cout<<"x --> ";
                x.PrintUnits();

                std::cout<<"y --> ";
                y.PrintUnits();
            }
            std::cout<<"\n\n";
        }
        
        
        inline Vector<xType,yType> operator+( const Vector<xType,yType>& V_other ) const
        {
            Vector<xType,yType> Created;
            Created.x = AddValues<xType>( x, V_other.x );
            Created.y = AddValues<yType>( y, V_other.y );
            return Created;
        }
        inline Vector<xType,yType> operator-( const Vector<xType,yType>& V_other ) const
        {
            Vector<xType,yType> Created;
            Created.x = SubtractValues<xType>( x, V_other.x );
            Created.y = SubtractValues<yType>( y, V_other.y );
            return Created;
        }
        //Dot product is only define between vectors with the same units
        template <typename T = xType>
        requires std::is_same_v<xType, yType>
        inline T operator*( const Vector<T,T>& V_other )
        {
            if constexpr( std::is_arithmetic_v<T> )
            {
                return x * V_other.x + y * V_other.y;
            }
            T Result = {x.Value * V_other.x.Value + y.Value * V_other.y.Value};
            return Result;
        }
        template<ArithemeticOrUnit Multiplier>
        inline auto operator*( const Multiplier& scalarMultlipier ) const
        {
            using Resulting_x_unit = typename ResultingMultiplicationUnit<xType,Multiplier>::type;
            using Resulting_y_unit = typename ResultingMultiplicationUnit<yType,Multiplier>::type;

            Vector<Resulting_x_unit,Resulting_y_unit> ResultingVector = { x * scalarMultlipier, y * scalarMultlipier }; 
            return ResultingVector ;
        }
        template<ArithemeticOrUnit Divider>
        inline auto operator/( const Divider& scalarDivider ) const
        {
            using Resulting_x_unit = typename ResultingDivisionUnit<xType,Divider>::type;
            using Resulting_y_unit = typename ResultingDivisionUnit<yType,Divider>::type;

            Vector<Resulting_x_unit,Resulting_y_unit> ResultingVector = { x / scalarDivider, y / scalarDivider };
            return ResultingVector;
        }
        
        static Vector<xType,yType> create( xType myX, yType myY )
        {
            return { myX, myY };
        }
        inline auto get_angle_x_axis()
        {
            if constexpr( std::is_arithmetic_v<xType> )
            {
                return std::atan(y,x);
            }
            Unit::Radian angle = std::atan2(y,x);
            return angle;
        }
        inline auto get_angle_y_axis()
        {
            if constexpr( std::is_arithmetic_v<xType> )
            {
                return std::atan(x,y);
            }
            Unit::Radian angle = std::atan2(x,y);
            return angle;
        }
    private:
        template<ArithemeticOrUnit T>
        constexpr T add_values( T Value1, T Value2) const
        {
            //If not arithetic type we return it in a struct
            if constexpr( std::is_arithmetic_v<T> )
            {
                return Value1 + Value2;
            }
            
            return { Value1 + Value2 };
        }
        template<ArithemeticOrUnit T>
        constexpr T subtract_values( T Value1, T Value2) const
        {
            //If not arithetic type we return it in a struct
            if constexpr( std::is_arithmetic_v<T> )
            {
                return Value1 - Value2;
            }
            
            return { Value1 - Value2 };
        }
};

//Helper function to deduce template types
//outside of vector struct to not have to specify type 
template<ArithemeticOrUnit xType, ArithemeticOrUnit yType>
requires VectorHasArithmeticOrUnitBase<xType, yType>
constexpr auto create_vector_2x2(const xType& x, const yType& y) { return Vector2X2<xType, yType>(x, y); }

template<ArithemeticOrUnit UnitType, ArithemeticOrScalarUnit AngleType>
constexpr auto create_angled_vector_2x2( const UnitType& magnitude, const AngleType& angle )
{
    UnitType x = magnitude * std::cos( angle );
    UnitType y = magnitude * std::sin( angle );
    auto Created = create_vector_2x2( x, y );
    return Created;
}





template<TEMPLATE_MATRIX_2X2_UNIT_SHORTHAND>
struct Matrix2X2
{
    a_1Type a_1; b_1Type b_1;
    a_2Type a_2; b_2Type b_2;

    
};

template<TEMPLATE_MATRIX_3X3_UNITSHORTHAND>
struct Matrix3X3
{
    a_1Type a_1; b_1Type b_1; c_1Type c_1;
    a_2Type a_2; b_2Type b_2; c_2Type c_2;
    a_3Type a_3; b_3Type b_3; c_3Type c_3;  
};





