#include "Unitree.hpp"
using namespace Unit;
//A test instantiating units, testing unit operations, template instantiations 
bool type_unit_test()
{
    // arithmetric operations +*-/
    // success is largely based on the fact that the templates are 
    // instantiated with any compilation errors
    bool Success = true;
    Meter m1 = 5;
    Meter m2 = 3.5;
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
    auto Power = uExt::n_power_sm<5>(m1);

    auto Power0 = uExt::n_power<0>(m1);
    if( Power0 != 1 )
    {
        Success = false;
    }
    Power0 = uExt::n_power_lg<0>(m1);
    if( Power0 != 1 )
    {
        Success = false;
    }
    Power0 = uExt::n_power_sm<0>(m1);
    if( Power0 != 1 )
    {
        Success = false;
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