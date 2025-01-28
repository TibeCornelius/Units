#include<iostream>
#include "Unitree.hpp"
#include "Tests.hpp"
#ifdef SEMI_UNIT_SAFETY
#include "CompileTests.hpp"
#endif

using namespace Unit;
int main()
{
    Meter m = 5;
    double d = 4;
    auto r = m + d;
    #ifdef SEMI_UNIT_SAFETY
    test_compile_definitions();
    #endif
}
