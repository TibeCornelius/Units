
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


#pragma region Macros
#define PREFIX_TEMPLATE_UNIT(PREFIX, UNIT) Rational PREFIX##UNIT
#define PREFIX_UNIT(PREFIX, UNIT) PREFIX##UNIT

#define PREFIXED_TEMPLATE_UNIT_SHORTHAND(PREFIX) \
    PREFIX_TEMPLATE_UNIT(PREFIX, Meters), \
    PREFIX_TEMPLATE_UNIT(PREFIX, Seconds), \
    PREFIX_TEMPLATE_UNIT(PREFIX, Kilogram), \
    PREFIX_TEMPLATE_UNIT(PREFIX, Ampere), \
    PREFIX_TEMPLATE_UNIT(PREFIX, Kelvin), \
    PREFIX_TEMPLATE_UNIT(PREFIX, Mol), \
    PREFIX_TEMPLATE_UNIT(PREFIX, Candela)

#define PREFIXED_UNIT_SHORTHAND(PREFIX) \
    PREFIX_UNIT(PREFIX, Meters), \
    PREFIX_UNIT(PREFIX, Seconds), \
    PREFIX_UNIT(PREFIX, Kilogram), \
    PREFIX_UNIT(PREFIX, Ampere), \
    PREFIX_UNIT(PREFIX, Kelvin), \
    PREFIX_UNIT(PREFIX, Mol), \
    PREFIX_UNIT(PREFIX, Candela)

#define TEMPLATE_UNIT_SHORTHAND PREFIXED_TEMPLATE_UNIT_SHORTHAND()
#define UNIT_SHORTHAND PREFIXED_UNIT_SHORTHAND()
#define TYPE_UNIT_SHORTHAND TypeUnit<UNIT_SHORTHAND>

#define PREFIXED_TYPE_UNIT_SHORTHAND(PREFIX) TypeUnit<PREFIXED_UNIT_SHORTHAND(PREFIX)>
#define ScalarUnit TypeUnit<0, 0, 0, 0, 0, 0, 0>


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

#define DOUBLE_TEMPLATE_UNIT_SHORTHAND( PREFIX_1, PREFIX2 ) PREFIXED_TEMPLATE_UNIT_SHORTHAND(PREFIX_1) PREFIXED_TEMPLATE_UNIT_SHORTHAND(PREFIX2)

#define UNIT_ADDITION_SHORTHAND( PREFIX_1, PREFIX_2 ) TypeUnit<PREFIX_1##Meters + PREFIX_2##Meters, PREFIX_1##Seconds + PREFIX_2##Seconds,  PREFIX_1##Kilogram + PREFIX_2##Kilogram, PREFIX_1##Ampere + PREFIX_2##Ampere, PREFIX_1##Kelvin + PREFIX_2##Kelvin, PREFIX_1##Mol + PREFIX_2##Mol, PREFIX_1##Candela + PREFIX_2##Candela>
#define UNIT_SUBTRACTION_SHORTHAND( PREFIX_1, PREFIX_2) TypeUnit<PREFIX_1##Meters - PREFIX_2##Meters, PREFIX_1##Seconds - PREFIX_2##Seconds,  PREFIX_1##Kilogram - PREFIX_2##Kilogram, PREFIX_1##Ampere - PREFIX_2##Ampere, PREFIX_1##Kelvin - PREFIX_2##Kelvin, PREFIX_1##Mol - PREFIX_2##Mol, PREFIX_1##Candela - PREFIX_2##Candela>
#define UNIT_POWER_SHORTHAND( POWER ) TypeUnit<Meters * POWER, Seconds * POWER, Kilogram * POWER, Ampere * POWER, Kelvin * POWER, Mol * POWER, Candela * POWER>
#pragma endregion
#pragma region Rational
struct Rational
{
    int Numerator;
    unsigned int Denominator; // Denominator is now unsigned.

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

    // Division operator.
    constexpr Rational operator/(const Rational &other) const
    {
        return *this * Rational(other.Denominator, static_cast<unsigned int>(other.Numerator));
    }

    // Equality operator.
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
concept isScalarUnit = std::is_same_v<T, ScalarUnit>;

template <typename T>
concept ArithemeticOrScalarUnit = std::is_arithmetic_v<T> || isScalarUnit<T>;

template<ArithemeticOrUnit xType, ArithemeticOrUnit yType>
requires VectorHasArithmeticOrUnitBase<xType, yType>
struct Vector;//Forward declaration

template <typename T1, typename T2>
concept SameType = std::is_same_v<T1, T2>;

template<ArithemeticOrUnit Unit1, ArithemeticOrUnit Unit2>
struct ResultingMultlipicationUnit;

template<TEMPLATE_UNIT_SHORTHAND,PREFIXED_TEMPLATE_UNIT_SHORTHAND(Other)>
struct ResultingMultlipicationUnit<TYPE_UNIT_SHORTHAND,PREFIXED_TYPE_UNIT_SHORTHAND(Other)>
{   
    using type = UNIT_ADDITION_SHORTHAND(,Other);
};

template<TEMPLATE_UNIT_SHORTHAND,Arithmetic Type2>
struct ResultingMultlipicationUnit<TYPE_UNIT_SHORTHAND,Type2>
{
    using type = TYPE_UNIT_SHORTHAND;
};

template<ArithemeticOrUnit Unit1, ArithemeticOrUnit Unit2>
struct ResultingDivisionUnit;

template<TEMPLATE_UNIT_SHORTHAND,PREFIXED_TEMPLATE_UNIT_SHORTHAND(Other)>
struct ResultingDivisionUnit<TYPE_UNIT_SHORTHAND,PREFIXED_TYPE_UNIT_SHORTHAND(Other)>
{
    using type = UNIT_SUBTRACTION_SHORTHAND(,Other);
};

template<TEMPLATE_UNIT_SHORTHAND,Arithmetic Type2>
struct ResultingDivisionUnit<TYPE_UNIT_SHORTHAND,Type2>
{
    using type = TYPE_UNIT_SHORTHAND;
};

template<ArithemeticOrUnit Unit1, uint Unit2>
struct ResultingPowerUnit;

template<TEMPLATE_UNIT_SHORTHAND, uint Power>
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
    TypeUnit() : Value(0.0) {}
    TypeUnit( double value ) : Value(value) {}
#pragma region TypeUnit operators 
    //Implicit double conversion
    operator double()const
    {
        return Value;
    }
    inline TYPE_UNIT_SHORTHAND operator=( double value )
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
    template <PREFIXED_TEMPLATE_UNIT_SHORTHAND(Other)>
    constexpr auto operator*(const PREFIXED_TYPE_UNIT_SHORTHAND(Other)& other) const
    {
        //Empty first prefix
        return UNIT_ADDITION_SHORTHAND(,Other)( this->Value * other.Value);
    }
    template <PREFIXED_TEMPLATE_UNIT_SHORTHAND(Other)>
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
    template <PREFIXED_TEMPLATE_UNIT_SHORTHAND(First),PREFIXED_TEMPLATE_UNIT_SHORTHAND(Second)>
    constexpr auto operator*( const Vector<PREFIXED_TYPE_UNIT_SHORTHAND(First),PREFIXED_TYPE_UNIT_SHORTHAND(Second)> Other )
    {
        //When multlipying a unit scalar with a vector, thus s * v, we return v * s, wich is defined in the Vector struct.
        return Other * Value;
    }
    template<bool isVerbose>
#pragma endregion
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
        std::cout<<get_units_to_string<isVerbose>();
    }
    inline void print_units() const
    {
        constexpr bool isVerbose = false;
        std::cout<<get_units_to_string<isVerbose>();
    }
    template<bool isVerbose>
    constexpr std::string get_units_to_string() const 
    {
        constexpr std::array<Rational, 7> exponents = {Meters, Seconds, Kilogram, Ampere, Kelvin, Mol, Candela};
        constexpr std::array<const char*, 7> unitNames = GetUnitNames<isVerbose>();

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
        result += "\n"; 
        return result;
    }
};

///namespace extension functions acting on Type unit
namespace uExt
{
    template <TEMPLATE_UNIT_SHORTHAND>
    auto square( TYPE_UNIT_SHORTHAND value )
    {
        using ResultingUnit = typename ResultingMultlipicationUnit<TYPE_UNIT_SHORTHAND,TYPE_UNIT_SHORTHAND>::type;
        ResultingUnit Result = { value.Value * value.Value };
        return Result;
    }

    
    
    template <int power,TEMPLATE_UNIT_SHORTHAND>
    auto n_power_lg( TYPE_UNIT_SHORTHAND unit )
    {
        //https://en.wikipedia.org/wiki/Exponentiation_by_squaring
        using ResultingUnit = typename ResultingPowerUnit<TYPE_UNIT_SHORTHAND,power>::type;
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

        double Value = fast_power(unit.Value, power);

        // Create and return the resulting unit
        return ResultingUnit{Value};
    }

    template <int power, TEMPLATE_UNIT_SHORTHAND>
    auto n_power_sm( TYPE_UNIT_SHORTHAND unit )
    {
        using ResultingUnit = typename ResultingPowerUnit<TYPE_UNIT_SHORTHAND,power>::type;
        double Value = 1; 
        for( int index = 0 ; index < power ; index++ )
        {
            Value = Value * unit.Value;
        }
        ResultingUnit Result = { Value };
        return Result;
    }
    //Raise type unit to n power
    //Using different aproach based on power size
    template <int power, TEMPLATE_UNIT_SHORTHAND>
    auto n_power( TYPE_UNIT_SHORTHAND unit )
    {
        if constexpr ( power > 10 )
        {
            return n_power_lg<power>( unit );
        }

        return n_power_sm<power>( unit );
    }
}

namespace Unit
{
    using Scalar = TypeUnit<0, 0, 0, 0, 0, 0, 0>;
    using Radian = Scalar;

    using Meter = TypeUnit<1, 0, 0, 0, 0, 0, 0>;
    using Meter2 = TypeUnit<1, 0, 0, 0, 0, 0, 0>;
    using SquareMeter = TypeUnit<2, 0, 0, 0, 0, 0, 0>;
    using Area = SquareMeter;
    using CubeMeter = TypeUnit<3, 0, 0, 0, 0, 0, 0>;
    using Volume = CubeMeter;

    using Seconds = TypeUnit<0, 1, 0, 0, 0, 0, 0>;
    using Hertz = TypeUnit<0, -1, 0, 0, 0, 0, 0>;

    using Kilogram = TypeUnit<0, 0, 1, 0, 0, 0, 0>;

    using Ampere = TypeUnit<0, 0, 0, 1, 0, 0, 0>;

    using Kelvin = TypeUnit<0, 0, 0, 0, 1, 0, 0>;

    using Mol = TypeUnit<0, 0, 0, 0, 0, 1, 0>;

    using Candela = TypeUnit<0, 0, 0, 0, 0, 0, 1>;

    using Velocity = TypeUnit<1, -1, 0, 0, 0, 0, 0>;
    using Acceleration = TypeUnit<1, -2, 0, 0, 0, 0, 0>;
    using Jerk = TypeUnit<1, -3, 0, 0, 0, 0, 0>;

    using Newton = TypeUnit<1,-2,1,0,0,0,0>;
    using Force = Newton;

    using Work = TypeUnit<2,-2,1,0,0,0,0>;
    using Torque = Work;

    using Watt = TypeUnit<2, -3, 1, 0, 0, 0, 0>; // Power: J/s
    using Pascal = TypeUnit<-1, -2, 1, 0, 0, 0, 0>; 

    using Coulomb = TypeUnit<0, 1, 0, 1, 0, 0, 0>; // Charge: A·s
    using Volt = TypeUnit<2, -3, 1, -1, 0, 0, 0>; // Electric potential: W/A
    using Ohm = TypeUnit<2, -3, 1, -2, 0, 0, 0>; // Resistance: V/A
    using Siemens = TypeUnit<-2, 3, -1, 2, 0, 0, 0>; // Conductance: 1/Ω
    using Farad = TypeUnit<-2, 4, -1, 2, 0, 0, 0>; // Capacitance: C/V
    using Henry = TypeUnit<2, -2, 1, -2, 0, 0, 0>; // Inductance: Ω·s
    using Weber = TypeUnit<2, -2, 1, -1, 0, 0, 0>; // Magnetic flux: V·s
    using Tesla = TypeUnit<0, -2, 1, -1, 0, 0, 0>;

    using Entropy = TypeUnit<2, -2, 1, 0, -1, 0, 0>; // J/K
    using SpecificHeatCapacity = TypeUnit<2, -2, 0, 0, -1, 0, 0>; // J/(kg·K)
    using StefanBoltzmannConstant = TypeUnit<0, -3, 1, 0, -4, 0, 0>;

    using Concentration = TypeUnit<-3, 0, 0, 0, 0, 1, 0>; // mol/m^3
    using CatalyticActivity = TypeUnit<0, -1, 0, 0, 0, 1, 0>; // mol/s

    using Lumen = TypeUnit<0, 0, 0, 0, 0, 0, 1>; // cd·sr
    using Lux = TypeUnit<-2, 0, 0, 0, 0, 0, 1>; // lm/m^2

    using AngularVelocity = TypeUnit<0, -1, 0, 0, 0, 0, 0>; // rad/s
    using AngularAcceleration = TypeUnit<0, -2, 0, 0, 0, 0, 0>; // rad/s^2
    using Impulse = TypeUnit<1, -1, 1, 0, 0, 0, 0>; // N·s
    using Momentum = TypeUnit<1, -1, 1, 0, 0, 0, 0>; // kg·m/s*/
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
            using Resulting_x_unit = typename ResultingMultlipicationUnit<xType,Multiplier>::type;
            using Resulting_y_unit = typename ResultingMultlipicationUnit<yType,Multiplier>::type;

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
#define mCreateVector2X2(x,y) Vector<decltype(x),decltype(y)>::CreateVector2X2(x,y)

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





