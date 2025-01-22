#include "Unitree.hpp"
#include "Tests.hpp"

void UnitCompileTest()
{
    Meter m1 = 5;
    Meter m2 = 3.5;
    Seconds s1 = 10;

    auto resultMultplication = m1 * s1;
    auto resultDivision = m1 / s1;
    auto resultAddition = m2 + m1;
    auto resultSubtraciton = m2 - m1;

    auto resultSquare = m1 * m1;
}