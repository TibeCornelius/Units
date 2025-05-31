#define IRRATIONAL
#define IRRATIONAL_BASES

struct Rationals
{
    int Numerator;
    unsigned int Denominator; 

    // Default constructor.
    constexpr Rationals() : Numerator(0), Denominator(1) {}

    // Parameterized constructor.
    constexpr Rationals(int numerator, unsigned int denominator) : Numerator(numerator), Denominator(denominator)
    {
        if (Denominator == 0)
        {

        }
    }

    // Integer-to-Rationals constructor.
    constexpr Rationals(int value) : Numerator(value), Denominator(1) {}

    // Simplify the rational number.
    constexpr Rationals simplified() const
    {
        unsigned int gcd = std::gcd(Numerator, Denominator);
        return {Numerator / static_cast<int>(gcd), Denominator / gcd};
    }

    // Addition operator.
    constexpr Rationals operator+(const Rationals &other) const
    {
        return Rationals( Numerator * static_cast<int>(other.Denominator) + 
            other.Numerator * static_cast<int>(Denominator),
            Denominator * other.Denominator)
            .simplified();
    }

    // Subtraction operator.
    constexpr Rationals operator-(const Rationals &other) const
    {
        return Rationals( Numerator * static_cast<int>(other.Denominator) -
            other.Numerator * static_cast<int>(Denominator),Denominator * other.Denominator)
            .simplified();
    }

    // Multiplication operator.
    constexpr Rationals operator*(const Rationals &other) const
    {
        return Rationals( Numerator * other.Numerator, Denominator * other.Denominator)
            .simplified();
    }

    constexpr Rationals operator/(const Rationals &other) const
    {
        return *this * Rationals(other.Denominator, static_cast<unsigned int>(other.Numerator));
    }

    constexpr bool operator==(const Rationals &other) const
    {
        return Numerator * static_cast<int>(other.Denominator) ==
            other.Numerator * static_cast<int>(Denominator);
    }

    // Inequality operator.
    constexpr bool operator!=(const Rationals &other) const
    {
        return !(*this == other);
    }

    // Less-than operator.
    constexpr bool operator<(const Rationals &other) const
    {
        return Numerator * static_cast<int>(other.Denominator) <
            other.Numerator * static_cast<int>(Denominator);
    }

    // Greater-than operator.
    constexpr bool operator>(const Rationals &other) const
    {
        return other < *this;
    }

    // Less-than-or-equal-to operator.
    constexpr bool operator<=(const Rationals &other) const
    {
        return !(*this > other);
    }

    constexpr bool operator>=(const Rationals &other) const
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
        Rationals rSelf = {std::abs(Numerator), Denominator};
        if (rSelf.Denominator == 1)
        {
            return std::to_string(rSelf.Numerator);
        }
        return std::to_string(rSelf.Numerator) + "/" + std::to_string(rSelf.Denominator);
    }

    // Overload for output stream.
    friend std::ostream &operator<<(std::ostream &os, const Rationals &rational)
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

/*template <Rationals Exponent, Rationals BaseConversion> 
struct BaseUnit
{
    inline constexpr BaseUnit<Exponent+Exponent,BaseConversion*BaseConversion> operator *( const BaseUnit Other ) const
    {
        return{};
    }
};

using BaseMeter = BaseUnit< (1), (1) >;  // Dimensionless*/
void TestMacros()
{
    
}