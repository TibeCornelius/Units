
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
#include<concepts>
#include<iostream>

//Set default value of is_unit to false
template<typename>
struct is_unit : std::false_type {};



#define PREFIX_TEMPLATE_UNIT(PREFIX, UNIT) int PREFIX##UNIT
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

#define TEMPLATE_UNIT_SHORTHAND int Meters,int Seconds, int Kilogram, int Ampere, int Kelvin, int Mol, int Candela
#define UNIT_SHORTHAND Meters,Seconds,Kilogram,Ampere,Kelvin,Mol,Candela
#define TYPE_UNIT_SHORTHAND Unit<UNIT_SHORTHAND>

#define PREFIXED_TYPE_UNIT_SHORTHAND(PREFIX) Unit<PREFIXED_UNIT_SHORTHAND(PREFIX)>

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

#define DOUBLE_TEMPLATE_UNIT_SHORTHAND( PREFIX_1, PREFIX2 ) int PREFIX_1##Meters,int PREFIX_1##Seconds, int PREFIX_1##Kilogram, int PREFIX_1##Ampere, int PREFIX_1##Kelvin, int PREFIX_1##Mol, int PREFIX_1##Candela,int PREFIX_2##Meters, int PREFIX_2##Seconds, int PREFIX_2##Kilogram, int PREFIX_2##Ampere, int PREFIX_2##Kelvin,int PREFIX_2##Mol, int PREFIX_2##Candela

#define UNIT_ADDITION_SHORTHAND( PREFIX_1, PREFIX_2 ) Unit<PREFIX_1##Meters + PREFIX_2##Meters, PREFIX_1##Seconds + PREFIX_2##Seconds,  PREFIX_1##Kilogram + PREFIX_2##Kilogram, PREFIX_1##Ampere + PREFIX_2##Ampere, PREFIX_1##Kelvin + PREFIX_2##Kelvin, PREFIX_1##Mol + PREFIX_2##Mol, PREFIX_1##Candela + PREFIX_2##Candela>
#define UNIT_SUBTRACTION_SHORTHAND( PREFIX_1, PREFIX_2) Unit<PREFIX_1##Meters - PREFIX_2##Meters, PREFIX_1##Seconds - PREFIX_2##Seconds,  PREFIX_1##Kilogram - PREFIX_2##Kilogram, PREFIX_1##Ampere - PREFIX_2##Ampere, PREFIX_1##Kelvin - PREFIX_2##Kelvin, PREFIX_1##Mol - PREFIX_2##Mol, PREFIX_1##Candela - PREFIX_2##Candela>


template<typename T>
concept Arithmetic = std::is_arithmetic_v<T>;

template<TEMPLATE_UNIT_SHORTHAND>
struct Unit;//Forward declaration

template<typename T>
constexpr bool is_unit_v = is_unit<T>::value;

template<typename T>
concept ArithemeticOrUnit = std::is_arithmetic_v<T> || is_unit_v<T>;


template<typename T>
concept isUnit = is_unit_v<T>;

template <typename x, typename y>
concept VectorHasArithmeticOrUnitBase = (std::is_arithmetic_v<x> && std::is_arithmetic_v<y>)
    || ( isUnit<x> && isUnit<y> );

template<typename T>
concept isScalarUnit = std::is_same_v<T, Unit<0, 0, 0, 0, 0, 0, 0>>;

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
//Represents the exponents of each unit
//Meters,Seconds,Kilogram,Ampere,Kelvin,Mol,Candela
template <TEMPLATE_UNIT_SHORTHAND>
struct Unit
{
    double Value;
    Unit() : Value(0.0) {}
    Unit( double value ) : Value(value) {}
#pragma region Unit operators 
    //Implicit double conversion
    operator double()const
    {
        return Value;
    }
    inline TYPE_UNIT_SHORTHAND operator=( double value )
    {
        TYPE_UNIT_SHORTHAND Unit = { value };
        return Unit;
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
    static constexpr std::array<const char*,7> GetUnitNames()
    {
        if constexpr( isVerbose )
        {
            return {"Meters", "Seconds", "Kilograms", "Amperes", "Kelvin", "Mol", "Candela"};
        }
        return {"m", "s", "kg", "A", "K", "mol", "cd"};
    }
    inline void PrintUnitsVerbose() const
    {
        constexpr bool isVerbose = true;
        std::cout<<GetUnitsToString<isVerbose>();
    }
    inline void PrintUnits() const
    {
        constexpr bool isVerbose = false;
        std::cout<<GetUnitsToString<isVerbose>();
    }
    template<bool isVerbose>
    constexpr std::string GetUnitsToString() const 
    {
        constexpr std::array<int, 7> exponents = {Meters, Seconds, Kilogram, Ampere, Kelvin, Mol, Candela};
        constexpr std::array<const char*, 7> unitNames = GetUnitNames<isVerbose>();

        std::string result = "Units: "+ std::to_string(Value) + " ";

        bool ThereAreNegativeExponents = false;
        // Process positive exponents
        for (size_t i = 0; i < exponents.size(); ++i)
        {
            if (exponents[i] > 0) 
            {
                result += std::string(unitNames[i]);
                if (exponents[i] != 1)
                {
                    result += "^" + std::to_string(exponents[i]);
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
                        result += "^" + std::to_string(-exponents[i]);
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

#pragma region  UnitMacros
    using Scalar = Unit<0, 0, 0, 0, 0, 0, 0>;
    using Radian = Scalar;

    using Meter = Unit<1, 0, 0, 0, 0, 0, 0>;
    using Meter2 = Unit<1, 0, 0, 0, 0, 0, 0>;
    using SquareMeter = Unit<2, 0, 0, 0, 0, 0, 0>;
    using Area = SquareMeter;
    using CubeMeter = Unit<3, 0, 0, 0, 0, 0, 0>;
    using Volume = CubeMeter;

    using Seconds = Unit<0, 1, 0, 0, 0, 0, 0>;
    using Hertz = Unit<0, -1, 0, 0, 0, 0, 0>;

    using Kilogram = Unit<0, 0, 1, 0, 0, 0, 0>;

    using Ampere = Unit<0, 0, 0, 1, 0, 0, 0>;

    using Kelvin = Unit<0, 0, 0, 0, 1, 0, 0>;

    using Mol = Unit<0, 0, 0, 0, 0, 1, 0>;

    using Candela = Unit<0, 0, 0, 0, 0, 0, 1>;

    using Velocity = Unit<1, -1, 0, 0, 0, 0, 0>;
    using Acceleration = Unit<1, -2, 0, 0, 0, 0, 0>;
    using Jerk = Unit<1, -3, 0, 0, 0, 0, 0>;

    using Newton = Unit<1,-2,1,0,0,0,0>;
    using Force = Newton;

    using Work = Unit<2,-2,1,0,0,0,0>;
    using Torque = Work;

    using Watt = Unit<2, -3, 1, 0, 0, 0, 0>; // Power: J/s
    using Pascal = Unit<-1, -2, 1, 0, 0, 0, 0>; 

    using Coulomb = Unit<0, 1, 0, 1, 0, 0, 0>; // Charge: A·s
    using Volt = Unit<2, -3, 1, -1, 0, 0, 0>; // Electric potential: W/A
    using Ohm = Unit<2, -3, 1, -2, 0, 0, 0>; // Resistance: V/A
    using Siemens = Unit<-2, 3, -1, 2, 0, 0, 0>; // Conductance: 1/Ω
    using Farad = Unit<-2, 4, -1, 2, 0, 0, 0>; // Capacitance: C/V
    using Henry = Unit<2, -2, 1, -2, 0, 0, 0>; // Inductance: Ω·s
    using Weber = Unit<2, -2, 1, -1, 0, 0, 0>; // Magnetic flux: V·s
    using Tesla = Unit<0, -2, 1, -1, 0, 0, 0>;

    using Entropy = Unit<2, -2, 1, 0, -1, 0, 0>; // J/K
    using SpecificHeatCapacity = Unit<2, -2, 0, 0, -1, 0, 0>; // J/(kg·K)
    using StefanBoltzmannConstant = Unit<0, -3, 1, 0, -4, 0, 0>;

    using Concentration = Unit<-3, 0, 0, 0, 0, 1, 0>; // mol/m^3
    using CatalyticActivity = Unit<0, -1, 0, 0, 0, 1, 0>; // mol/s

    using Lumen = Unit<0, 0, 0, 0, 0, 0, 1>; // cd·sr
    using Lux = Unit<-2, 0, 0, 0, 0, 0, 1>; // lm/m^2

    using AngularVelocity = Unit<0, -1, 0, 0, 0, 0, 0>; // rad/s
    using AngularAcceleration = Unit<0, -2, 0, 0, 0, 0, 0>; // rad/s^2
    using Impulse = Unit<1, -1, 1, 0, 0, 0, 0>; // N·s
    using Momentum = Unit<1, -1, 1, 0, 0, 0, 0>; // kg·m/s

#pragma endregion
#pragma region Physical constants
    const Radian Pi =   3.14159265358979323846;
#pragma endregion

//Flag unit struct as is_unit true
template<TEMPLATE_UNIT_SHORTHAND>
struct is_unit<TYPE_UNIT_SHORTHAND> : std::true_type {};

template<ArithemeticOrUnit xType, ArithemeticOrUnit yType>
requires VectorHasArithmeticOrUnitBase<xType, yType>
struct Vector2X2
{
    public:
        xType x;
        yType y;

        void PrintVerbose()
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
        void Print()
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
        
        static Vector<xType,yType> Create( xType myX, yType myY )
        {
            return { myX, myY };
        }
        inline auto GetAngleXaxis()
        {
            if constexpr( std::is_arithmetic_v<xType> )
            {
                return std::atan(y,x);
            }

            Radian angle = std::atan2(y,x);
            return angle;
        }
        inline auto GetAngleYaxis()
        {
            if constexpr( std::is_arithmetic_v<xType> )
            {
                return std::atan(x,y);
            }

            Radian angle = std::atan2(x,y);
            return angle;
        }
    private:
        template<ArithemeticOrUnit T>
        constexpr T AddValues( T Value1, T Value2) const
        {
            //If not arithetic type we return it in a struct
            if constexpr( std::is_arithmetic_v<T> )
            {
                return Value1 + Value2;
            }
            
            return { Value1 + Value2 };
        }
        template<ArithemeticOrUnit T>
        constexpr T SubtractValues( T Value1, T Value2) const
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
constexpr auto CreateVector2X2(const xType& x, const yType& y) { return Vector2X2<xType, yType>(x, y); }

template<ArithemeticOrUnit UnitType, ArithemeticOrScalarUnit AngleType>
constexpr auto CreateAngledVector2X2Vector( const UnitType& magnitude, const AngleType& angle )
{
    UnitType x = magnitude * std::cos( angle );
    UnitType y = magnitude * std::sin( angle );
    auto Created = CreateVector2X2( x, y );
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





