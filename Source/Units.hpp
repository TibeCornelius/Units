#pragma once
#include<iostream>
#include<math.h>

namespace Units
{
    //Base structs
    //Curiously Recurring Template Pattern
    //https://en.cppreference.com/w/cpp/language/crtp
    //Generic overloading of + and - to return the base struct
    template<typename DerivedStruct>
    struct BaseUnit
    {
        double Value;
        inline DerivedStruct operator-(const DerivedStruct& SecondVariable) const 
        {
            DerivedStruct result;
            result.Value = this->Value - SecondVariable.Value;
            return result;
        }

        inline DerivedStruct operator+(const DerivedStruct& SecondVariable) const 
        {
            DerivedStruct result;
            result.Value = this->Value + SecondVariable.Value;
            return result;
        }
        inline DerivedStruct operator-() const
        {
            DerivedStruct Result = {-this->Value};
            return Result;
        }
        friend inline bool operator<( const DerivedStruct& First, const DerivedStruct& Second ) { return First.Value < Second.Value; }
        friend inline bool operator>( const DerivedStruct& First, const DerivedStruct& Second ) { return First.Value > Second.Value; }
        friend inline bool operator<=( const DerivedStruct& First, const DerivedStruct& Second ) { return Second.Value <= First.Value; }
        friend inline bool operator>=( const DerivedStruct& First, const DerivedStruct& Second ) { return Second.Value >= First.Value; }
        friend inline bool operator==( const DerivedStruct& First, const DerivedStruct& Second ) { return Second.Value == First.Value; }
        friend inline bool operator!=( const DerivedStruct& First, const DerivedStruct& Second ) { return Second.Value != First.Value; }

        friend std::ostream& operator<<(std::ostream& os, const DerivedStruct& derivedStruct) 
        {
            os << derivedStruct.Value;
            return os;
        }
    };

    template<typename DerivedStruct>
    struct BaseVectorUnit : BaseUnit<DerivedStruct> {};
    template<typename DerivedStruct>
    struct BaseScalarUnit : BaseUnit<DerivedStruct> {};

    #pragma region AllUnits
    struct Scalar;
    struct Kilogram;
    struct Meters;
    struct LeverArm;//Special unit which defines the distance from a force to its rotation axis used for generating torque
    struct Temperature;
    struct Mol;
    struct Luminous;
    struct Joule;
    struct Second;
    struct Velocity;
    struct Acceleration;
    struct Momentum;
    struct Force;
    struct Torque;
    struct Radian;
    struct ElectricCurrent;
    #pragma endregion

    //Unit implementations

    struct Scalar : BaseScalarUnit<Scalar>
    {
        template <typename UnitType>
        inline UnitType operator*(const UnitType& unit) const
        {
            UnitType result;
            result.Value = this->Value * unit.Value;
            return result;
        }

        template <typename UnitType>
        inline UnitType operator/(const UnitType& unit) const
        {
            UnitType result;
            result.Value = this->Value / unit.Value;
            return result;
        }
    };
    struct Kilogram : BaseScalarUnit<Kilogram>
    { 
        Force operator * ( const Acceleration& acceleration ) const;
        Momentum operator* ( const Velocity& Velocity ) const;
    };
    struct Meters : BaseVectorUnit<Meters>
    { 
        Velocity operator / ( const Second& seconds ) const;
    };
    struct LeverArm : BaseVectorUnit<LeverArm>
    {
        Torque operator * ( const Force& distance ) const;
    };
    struct Temperature : BaseScalarUnit<Temperature> {};
    struct Mol : BaseScalarUnit<Mol> {};
    struct Luminous : BaseScalarUnit<Luminous> {};//Candela



    struct Joule : BaseScalarUnit<Joule> {};
    struct Second : BaseScalarUnit<Second> {};
    struct Velocity : BaseVectorUnit<Velocity>
    { 
        Acceleration operator / ( const Second& seconds ) const;
        Meters operator*(const Second& seconds) const;
        Momentum operator*(const Kilogram& mass ) const;
    }; // Meter per second
    struct Acceleration : BaseVectorUnit<Acceleration>
    {
        Force operator * ( const Kilogram& mass ) const;
        Velocity operator * ( const Second& mass ) const
        {
            return { this->Value * mass.Value };
        }

    };//Meter per second^squared
    struct Momentum : BaseVectorUnit<Momentum>
    {
        Velocity operator/( const Kilogram& mass ) const;
    };
    struct Force : BaseVectorUnit<Force>
    {
        Joule operator * ( const Meters& distance ) const;
        Acceleration operator/( const Kilogram mass ) const
        {
            return { this->Value / mass.Value };
        }
        Torque operator * ( const LeverArm& distance ) const;
    };//Newton
    struct Torque : BaseVectorUnit<Torque> {};
    struct Radian : BaseScalarUnit<Radian> 
    {
        
        Scalar GetCos()
        {
            return {std::cos( Value )};
        }
        Scalar GetSin()
        {
            return {std::sin(Value)};
        }
    };
    struct ElectricCurrent : BaseScalarUnit<ElectricCurrent> {};//Ampere
}