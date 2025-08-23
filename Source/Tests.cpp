#include "Unitree.hpp"
#include "SiUnitSingleton.hpp"
#include <print>
using namespace Unit;

namespace Eidos
{
    bool esTestAll();
    bool esTestUnitSingleton()
    {
        bool Success = true;
        using minute = BasePrimitiveUnit<1, 60>;
        using second = BasePrimitiveUnit<1,1>;
        using decimeter = BasePrimitiveUnit<1,Rational(1,10)>;
        using centimeter = BasePrimitiveUnit<1,Rational(1,100)>;

        minute m = {8};
        second s = {8};

        decimeter d = 10;
        auto r = centimeter(d);

        if( r.value != 100 )
        {
            Success = false;
            std::println("Value was not equal after primitive base conversion");
            std::println("Result {}, Expected {}", r.value , 100 );
        }

        
        return Success;
    }
}
//A test instantiating units, testing unit operations, template instantiations 
bool type_unit_test()
{
    // arithmetric operations +*-/
    // success is largely based on the fact that the templates are 
    // instantiated with any compilation errors
    bool Success = true;
    Meter m1 = 5;
    Meter m2 = 3.5;

    m2 = m1;
    Seconds s1 = 10;

    auto resultMultplication = m1 * s1;
    auto resultDivision = m1 / s1;
    auto resultAddition = m2 + m1;
    auto resultSubtraciton = m2 - m1;

    auto resultSquare = m1 * m1;
    auto resultSelfDiv = m1/m1;
    auto resultAdd = m1 + m1;
    auto resultSubtr = m1 - m2;

    auto Square = uExt::square( m1 );
    auto Power = uExt::power_sm<5>(m1);

    auto Power0 = uExt::power<0>(m1);
    if( Power0.v() != 1 )
    {
        Success = false;
    }
    Power0 = uExt::power_lg<0>(m1);
    if( Power0.v() != 1 )
    {
        Success = false;
    }
    Power0 = uExt::power_sm<0>(m1);
    if( Power0.v() != 1 )
    {
        Success = false;
    }
    Power0.print_units_verbose();
    auto NewPower = uExt::power<-1>(m1);
    if( Power0.v() != 0.2 )
    {
        Success = false;
        std::cout<<"Negative exponent test failed, function power, operation "<<m1<< "^-1, gave result : "<<Power0.Value<<"\n";
        Power0.print_units_verbose();
    }
    auto ResultPower = uExt::power_sm<-1>(m1);
    ResultPower.print_units();
    if( ResultPower.v() != 0.2 )
    {
        Success = false;
        std::cout<<"Negative exponent test failed, function power_sm, operation "<<m1<< "^-1, gave result : "<<ResultPower.Value<<"\n";
    }

    auto ResultPower2 = uExt::power_lg<-2>(s1);
    if( ResultPower2.v() != 0.01 )
    {
        std::cout<<"Negative exponent power test failed, "<<s1<< "^-1 gave result : "<<ResultPower2<<"\n";
    }

    Scalar scalar = 5;
    auto scalarPowerResult = uExt::power<3>(scalar);
    if( scalarPowerResult.Value != 125 )
    {
        std::cout<<"exponent power test failed, "<<scalar<<"^3 gave result : "<<scalarPowerResult<<"\n";
    }

    SquareMeter sqm = 5;
    auto cbm = sqm * m1;
    CubeMeter cbm2 = 5;
    

    // equality operators
    Meter m3 = 3.5;
    if( !( m2 == m3 ) )
    {
        Success = false;
    }
    if( m2 != m3 )
    {
        Success = false;
    }

    if( m1 < m2 )
    {
        Success = false;
    }

    if( m2 > m1 )
    {
        Success = false;
    }

    if( m1 <= m2 )
    {
        Success = false;
    }

    if( m2 >= m1 )
    {
        Success = false;
    }
    if( !( m2 >= m3 ) )
    {
        Success = false;
    }
    if( !( m3 <= m3 ) )
    {
        Success = false;
    }

    return Success;
}

//void test_base_units()
//{
//    cMeter m1{};
//    cMeter m2{};
//    auto r = m1*m2;
//}
//Runs every test
void test_everything()
{
    if( type_unit_test() == false )
    {
        std::cout<<"Unit test failed\n";
    }
    else
    {
        std::cout<<"Unit test success\n";
    }
}

void print_compile_mode()
{
    #ifdef SEMI_UNIT_SAFETY
    std::cout<<"Semi unit safety activated\n";
    #else
    std::cout<<"Semi unit safety disabled\n";
    #endif
}