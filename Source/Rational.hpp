#include <tuple>
#include <iostream>
#include <ostream> 
#include <numeric> 
struct Rational
{
    int Numerator;
    int Denominator;
    Rational(){}//Default constructor, don't remove
    Rational( int numerator, int denominator ): Numerator( numerator ), Denominator( denominator ) {}
    //We dont pass by reference since we will change the fraction
    Rational operator+( Rational other )
    {
        Rational r1 = Rational(*this);

        set_common_denominator(r1, other);
        Rational Result = Rational( r1.Numerator + other.Numerator, r1.Denominator);
        Result.simplify_fraction();
        return Result;
    }
    Rational operator-( Rational other )
    {
        Rational r1 = Rational(*this);

        set_common_denominator(r1, other);
        Rational Result = Rational( r1.Numerator - other.Numerator, r1.Denominator );
        Result.simplify_fraction();
        return Result;
    }    
    Rational operator*( Rational& other )
    {
        Rational Result = { Numerator * other.Numerator, Denominator * other.Denominator };
        return Result;
    }
    Rational operator/( Rational& other )
    {// (a/b) / (c/d) = (a/b) * (d/c)
        Rational OtherInverse = other.get_inverse();
        return *this * OtherInverse; 
    }
    bool operator==( Rational& other )
    {
        if( Numerator == other.Numerator && Denominator == other.Denominator )
        {
            return true;
        }
        return false;
    }
    bool operator!=( Rational& other )
    {
        if( Numerator != other.Numerator || Denominator != other.Denominator )
        {
            return true;
        }
        return false;
    }
    friend std::ostream& operator<<( std::ostream& stream, const Rational& rational )
    {
        stream <<rational.Numerator<<"/"<<rational.Denominator;
        return stream;
    }
    static void set_common_denominator( Rational& rational_1, Rational& rational_2 )
    {
        int denominator_2 = rational_2.Denominator;
        Rational unit = { rational_1.Denominator, rational_1.Denominator };

        rational_2 = multliply_without_simplifying( rational_2, unit );
        unit = { denominator_2, denominator_2 };
        rational_1 = multliply_without_simplifying( rational_1, unit );
    }
    static Rational multliply_without_simplifying(const Rational& first, const Rational& second)
    {
        // Perform multiplication and return the result as a new Rational
        Rational Result = { first.Numerator * second.Numerator, first.Denominator * second.Denominator };
        return Result;
    }
    Rational get_inverse()
    {
        return { Denominator, Numerator };
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


