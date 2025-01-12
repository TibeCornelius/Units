#include<concepts>
//Set default value of is unit to false



template<typename>
struct is_unit : std::false_type {};

#define TemplateUnitShortHand int Meters,int Seconds, int Kilogram, int Ampere, int Kelvin, int Mol, int Candela
#define UnitShortHand Unit<Meters,Seconds,Kilogram,Ampere,Kelvin,Mol,Candela>

#define PREFIX_TemplateUNIT(PREFIX, UNIT) int PREFIX##UNIT
#define PREFIX_UNIT(PREFIX, UNIT) PREFIX##UNIT


#define PREFIXED_TEMPLATE_UNIT_SHORTHAND(PREFIX) \
    PREFIX_TemplateUNIT(PREFIX, Meters), \
    PREFIX_TemplateUNIT(PREFIX, Seconds), \
    PREFIX_TemplateUNIT(PREFIX, Kilogram), \
    PREFIX_TemplateUNIT(PREFIX, Ampere), \
    PREFIX_TemplateUNIT(PREFIX, Kelvin), \
    PREFIX_TemplateUNIT(PREFIX, Mol), \
    PREFIX_TemplateUNIT(PREFIX, Candela)

#define PREFIXED_UNIT_SHORTHAND(PREFIX) \
    PREFIX_UNIT(PREFIX, Meters), \
    PREFIX_UNIT(PREFIX, Seconds), \
    PREFIX_UNIT(PREFIX, Kilogram), \
    PREFIX_UNIT(PREFIX, Ampere), \
    PREFIX_UNIT(PREFIX, Kelvin), \
    PREFIX_UNIT(PREFIX, Mol), \
    PREFIX_UNIT(PREFIX, Candela)


#define TemplateOtherUnitShortHand int OtherMeters, int OtherSeconds, int OtherKilogram, int OtherAmpere, int OtherKelvin,int OtherMol, int OtherCandela
#define OtherUnitShortHand Unit<OtherMeters,OtherSeconds,OtherKilogram,OtherAmpere,OtherKelvin,OtherMol,OtherCandela>


#define DoubleTemplateUnitShortHand int Meters,int Seconds, int Kilogram, int Ampere, int Kelvin, int Mol, int Candela,int OtherMeters, int OtherSeconds, int OtherKilogram, int OtherAmpere, int OtherKelvin,int OtherMol, int OtherCandela

#define UnitAdditionShortHand Unit<Meters + OtherMeters, Seconds + OtherSeconds,  Kilogram + OtherKilogram, Ampere + OtherAmpere, Kelvin + OtherKelvin, Mol + OtherMol, Candela + Candela>
#define UnitSubtractionShortHand Unit<Meters - OtherMeters, Seconds - OtherSeconds,  Kilogram - OtherKilogram, Ampere - OtherAmpere, Kelvin - OtherKelvin, Mol - OtherMol, Candela - Candela>


template<typename T>
concept Arithmetic = std::is_arithmetic_v<T>;

template<TemplateUnitShortHand>
struct Unit;//Forward declaration

template<typename T>
constexpr bool is_unit_v = is_unit<T>::value;

template<typename T>
concept ArithemeticOrUnit = std::is_arithmetic_v<T> || is_unit_v<T>;


template<typename T>
concept isUnit = is_unit_v<T>;

template<ArithemeticOrUnit xType, ArithemeticOrUnit yType>
struct Vector;//Forward declaration


template<ArithemeticOrUnit Unit1, ArithemeticOrUnit Unit2>
struct ResultingMultlipicationUnit;

template <DoubleTemplateUnitShortHand>
struct ResultingMultlipicationUnit<UnitShortHand,OtherUnitShortHand>
{
    using type = UnitAdditionShortHand;
};

template <TemplateUnitShortHand,ArithemeticOrUnit Type2>
struct ResultingMultlipicationUnit<UnitShortHand,Type2>
{
    using type = UnitShortHand;
};

//Represents the exponents of each unit
template <TemplateUnitShortHand>
struct Unit
{
    double Value;

    inline UnitShortHand operator+( UnitShortHand& Other )
    {
        return { this->Value + Other.Value };
    }

    inline UnitShortHand operator-( UnitShortHand& other )
    {
        return { this->Value - other.Value };
    }

    template <TemplateOtherUnitShortHand>
    constexpr auto operator*(const OtherUnitShortHand& other) const 
    {
        return UnitAdditionShortHand( this->Value * other.Value);
    }
    template <TemplateOtherUnitShortHand>
    constexpr auto operator/( const OtherUnitShortHand& other )const
    {
        return UnitSubtractionShortHand( Value / other.Value );
    }
    template <PREFIXED_TEMPLATE_UNIT_SHORTHAND(First),PREFIXED_TEMPLATE_UNIT_SHORTHAND(Second)>
    constexpr auto operator*( const Vector<Unit<PREFIXED_UNIT_SHORTHAND(First)>,Unit<PREFIXED_UNIT_SHORTHAND(Second)>> Other )
    {
        //When multlipying a unit scalar with a vector, thus s * v, we return v * s, since this is defined.
        return Other * Value;
    }
    template<Arithmetic Scalar>
    constexpr UnitShortHand operator*( Scalar& scalar ) const
    {
        return { this->Value * scalar };
    }

    template<Arithmetic Scalar>
    constexpr UnitShortHand operator/( Scalar& scalar ) const
    {
        return { this->Value / scalar };
    }

    template<bool isVerbose>
    static constexpr std::array<const char*,7> GetUnitNames()
    {
        if constexpr( isVerbose )
        {
            return {"Meters", "Seconds", "Kilograms", "Amperes", "Kelvin", "Mol", "Candela"};
        }
        return {"m", "s", "kg", "A", "K", "mol", "cd"};
    }

    inline void PrintType() const
    {
        std::cout << "Units"<< " [Meters^" << Meters
            << " Seconds^" << Seconds
            << " Kilograms^" << Kilogram
            << " Amperes^" << Ampere
            << " Kelvin^" << Kelvin
            << " Mol^" << Mol
            << " Candela^" << Candela << "]\n";
    }
    inline void PrintUnitsVerbose() const
    {
        constexpr bool Verbose = true;
        std::cout<<GetUnitsToString<Verbose>();
    }
    inline void PrintUnits() const
    {
        constexpr bool Verbose = false;
        std::cout<<GetUnitsToString<Verbose>();
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
        }

       

        if (result == "Units: ") result += "1"; // If no units are present
        result += "\n"; 
        return result;
    }

};

//Flag unit struct as is_unit true
template<int Meters, int Seconds, int Kilograms, int Amperes, int Kelvin, int Mol, int Candela>
struct is_unit<Unit<Meters, Seconds, Kilograms, Amperes, Kelvin, Mol, Candela>> : std::true_type {};



#define Meter Unit<1,0,0,0,0,0,0>
#define Second Unit<0,1,0,0,0,0,0>
#define Velocity Unit<1,-1,0,0,0,0,0>



template<ArithemeticOrUnit xType, ArithemeticOrUnit yType>
struct Vector
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
        }
        
        inline Vector<xType,yType> operator+( const Vector<xType,yType>& V_other ) const
        {
            Vector<xType,yType> Created;
            Created.x = AddValues<xType>( x, V_other.x );
            Created.y = AddValues<yType>( y, V_other.y );
            return Created;
        }

        template<ArithemeticOrUnit Multiplier>
        inline auto operator*( const Multiplier& scalar ) const
        {
            using Resulting_x_unit = typename ResultingMultlipicationUnit<xType,Multiplier>::type;
            using Resulting_y_unit = typename ResultingMultlipicationUnit<yType,Multiplier>::type;

            Vector<Resulting_x_unit,Resulting_y_unit> ResultingVector = { x * scalar, y * scalar }; 
            return ResultingVector ;
        }
        
        static Vector<xType,yType> Create( xType myX, yType myY )
        {
            return { myX, myY };
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

#define CreateVector(x,y) Vector<decltype(x),decltype(y)>::Create(x,y)
