#include "Unitree.hpp"

//A test instantiating units, testing unit operations, template instantiations 
bool UnitTest()
{
    // arithmetric operations +*-/
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
void TestTotal()
{
    if( UnitTest() == false )
    {
        std::cout<<"Unit test failed\n";
    }
    else
    {
        std::cout<<"Unit test success\n";
    }
}