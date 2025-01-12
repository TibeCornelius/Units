#include<concepts>
//Set default value of is unit to false



template<typename>
struct is_unit : std::false_type {};

#define TEMPLATE_UNIT_SHORTHAND int Meters,int Seconds, int Kilogram, int Ampere, int Kelvin, int Mol, int Candela
#define UNIT_SHORTHAND Meters,Seconds,Kilogram,Ampere,Kelvin,Mol,Candela
#define TYPE_UNIT_SHORTHAND Unit<UNIT_SHORTHAND>

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
#define TYPE_PREFIXED_UNIT_SHORTHAND(PREFIX) Unit<PREFIXED_UNIT_SHORTHAND(PREFIX)>
    


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

template<ArithemeticOrUnit xType, ArithemeticOrUnit yType>
struct Vector;//Forward declaration


template<ArithemeticOrUnit Unit1, ArithemeticOrUnit Unit2>
struct ResultingMultlipicationUnit;

template <TEMPLATE_UNIT_SHORTHAND,PREFIXED_TEMPLATE_UNIT_SHORTHAND(Other)>
struct ResultingMultlipicationUnit<TYPE_UNIT_SHORTHAND,TYPE_PREFIXED_UNIT_SHORTHAND(Other)>
{   
    using type = UNIT_ADDITION_SHORTHAND(,Other);
};

template <TEMPLATE_UNIT_SHORTHAND,Arithmetic Type2>
struct ResultingMultlipicationUnit<TYPE_UNIT_SHORTHAND,Type2>
{
    using type = TYPE_UNIT_SHORTHAND;
};

//Represents the exponents of each unit
template <TEMPLATE_UNIT_SHORTHAND>
struct Unit
{
    double Value;

    inline TYPE_UNIT_SHORTHAND operator+( TYPE_UNIT_SHORTHAND& Other )
    {
        return { this->Value + Other.Value };
    }

    inline TYPE_UNIT_SHORTHAND operator-( TYPE_UNIT_SHORTHAND& other )
    {
        return { this->Value - other.Value };
    }

    template <PREFIXED_TEMPLATE_UNIT_SHORTHAND(Other)>
    constexpr auto operator*(const TYPE_PREFIXED_UNIT_SHORTHAND(Other)& other) const
    {
        //Empty first prefix
        return UNIT_ADDITION_SHORTHAND(,Other)( this->Value * other.Value);
    }
    template <PREFIXED_TEMPLATE_UNIT_SHORTHAND(Other)>
    constexpr auto operator/( const TYPE_PREFIXED_UNIT_SHORTHAND(Other)& other )const
    {
        return UNIT_SUBTRACTION_SHORTHAND(,Other)( Value / other.Value );
    }
    template <PREFIXED_TEMPLATE_UNIT_SHORTHAND(First),PREFIXED_TEMPLATE_UNIT_SHORTHAND(Second)>
    constexpr auto operator*( const Vector<Unit<PREFIXED_UNIT_SHORTHAND(First)>,Unit<PREFIXED_UNIT_SHORTHAND(Second)>> Other )
    {
        //When multlipying a unit scalar with a vector, thus s * v, we return v * s, wich is defined in the Vector struct.
        return Other * Value;
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
