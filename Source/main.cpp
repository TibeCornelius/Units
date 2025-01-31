#include<iostream>
#include "Unitree.hpp"
#include "Tests.hpp"
#ifdef SEMI_UNIT_SAFETY
#include "CompileTests.hpp"
#endif

using namespace Unit;
int main()
{

    #ifdef SEMI_UNIT_SAFETY
    test_compile_definitions();
    #endif

    print_compile_mode();
}
