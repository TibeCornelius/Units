#pragma once
#include <tuple>
#include <iostream>
#include <ostream> 
#include <numeric> 
struct Rational
{
    int Numerator;
    uint Denominator;

    static constexpr Rational Zero() 
    {
        return Rational{0, 1};
    }
    constexpr Rational():Numerator(0), Denominator(1){}
    constexpr Rational( int numerator, uint denominator ): Numerator( numerator ), Denominator( denominator ) {}
    constexpr Rational( int value ): Numerator( value ), Denominator( 1 ){}
#pragma region Rational operators
    Rational operator+( Rational other ) const
    {
        Rational r1 = Rational(*this);

        set_common_denominator(r1, other);
        Rational Result = Rational( r1.Numerator + other.Numerator, r1.Denominator);
        Result.simplify_fraction();
        return Result;
    }
    Rational operator-( Rational other ) const
    {
        Rational r1 = Rational(*this);

        set_common_denominator(r1, other);
        Rational Result = Rational( r1.Numerator - other.Numerator, r1.Denominator );
        Result.simplify_fraction();
        return Result;
    }    
    Rational operator*( Rational& other ) const
    {
        Rational Result = { Numerator * other.Numerator, Denominator * other.Denominator };
        return Result;
    }
    Rational operator/( Rational& other ) const
    {// (a/b) / (c/d) = (a/b) * (d/c)
        Rational OtherInverse = other.get_inverse();
        return *this * OtherInverse; 
    }
    constexpr bool operator==( Rational& other )
    {
        if( Numerator == other.Numerator && Denominator == other.Denominator )
        {
            return true;
        }
        return false;
    }
    constexpr bool operator!=( Rational& other )
    {
        if( Numerator != other.Numerator || Denominator != other.Denominator )
        {
            return true;
        }
        return false;
    }
    constexpr bool operator>( Rational& other ) const
    {
        Rational rSelf = Rational(*this);

        set_common_denominator( rSelf, other );
        return rSelf.Numerator > other.Numerator;
    }
    constexpr bool operator<( Rational& other ) const
    {
        Rational rSelf = Rational(*this);

        set_common_denominator( rSelf, other );
        return rSelf.Numerator < other.Numerator;
    }
    constexpr bool operator!=( int other ) const
    {
        Rational rSelf = Rational(*this);
        Rational rOther = Rational(other);
        return rSelf != rOther;
    }
    constexpr bool operator>( int other ) const
    {
        Rational rSelf = Rational(*this);
        Rational rOther = Rational(other);
        return rSelf > rOther; 
    }
    constexpr bool operator<( int other ) const
    {
        Rational rSelf = Rational(*this);
        Rational rOther = Rational(other);
        return rSelf < rOther;
    }
#pragma endregion
    friend std::ostream& operator<<( std::ostream& stream, const Rational& rational )
    {
        stream <<rational.Numerator<<"/"<<rational.Denominator;
        return stream;
    }
    static void set_common_denominator( Rational& rational_1, Rational& rational_2 )
    {
        uint denominator_2 = rational_2.Denominator;
        Rational unit = { static_cast<int>(rational_1.Denominator), rational_1.Denominator };

        rational_2 = multliply_without_simplifying( rational_2, unit );
        unit = { static_cast<int>(denominator_2), denominator_2 };
        rational_1 = multliply_without_simplifying( rational_1, unit );
    }
    static Rational multliply_without_simplifying(const Rational& first, const Rational& second)
    {
        // Perform multiplication and return the result as a new Rational
        Rational Result = { first.Numerator * second.Numerator, first.Denominator * second.Denominator };
        return Result;
    }
    constexpr Rational get_inverse()
    {
        bool isNegative = Numerator < 0 ;
        int NewNumerator = isNegative ? -Denominator : Denominator;
        uint NewDenominator = std::abs( Numerator ); 
        return { NewNumerator, NewDenominator };
    }  
    void simplify_fraction()
    {
        int gcd = std::gcd(Numerator, Denominator);
        Numerator /= gcd;
        Denominator /= gcd;
    }
    void print()
    {
        std::cout<<Numerator<<"/"<<Denominator<<"\n";
    }
    constexpr std::string to_string() const
    {
        if( Denominator == 1 )
        {
            return std::to_string(Numerator);
        }
        return std::to_string(Numerator)+"/"+std::to_string(Denominator);
    }
    constexpr std::string to_string_absolute_value() const
    {
        Rational rSelf = { std::abs(Numerator), Denominator };
        return rSelf.to_string();
    }
};


void TestFailureResponse(bool &Success, const Rational &r1_start, const Rational &r1_excpected, const Rational &r1)
{
    Success = false;
    std::cout << "Fractions where not equal\n";
    std::cout << "Starting fraction : " << r1_start << "\n";
    std::cout << "Excpected fraction : " << r1_excpected << "\n";
    std::cout << "Resulting fraction : " << r1 << "\n";
}
void TestFailureResponse(bool &Success, const Rational &r1, const Rational &r2, std::string Operation, const Rational &r_excpected, const Rational &r_result )
{
    Success = false;
    std::cout << "Fractions where not equal\n";
    std::cout << "First fraction : " << r1 << "\n";
    std::cout << "Second fraction : " << r2 << "\n";
    std::cout << "Operation : " << Operation << "\n";
    std::cout << "Excpected fraction : " << r_excpected << "\n";
    std::cout << "Resulting fraction : " << r_result << "\n\n\n";
}
bool Test()
{
    bool Success = true;

    Rational r1 = { 3,4 };
    Rational r2 = { 1,2 };
    Rational result = r1 + r2 ;


    return Success;
}


