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

    template<typename Unit1, typename Unit2>
    struct ResultingUnit;


    struct Meter
    {
        double Value;
    };
    struct Second
    {
        double Value;
    };
    
}