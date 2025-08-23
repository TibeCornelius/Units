#include<iostream>
#include <print>
#include "Tests.hpp"
#ifdef SEMI_UNIT_SAFETY
#include "CompileTests.hpp"
#endif

int main()
{

    #ifdef SEMI_UNIT_SAFETY
    test_compile_definitions();
    #endif
    //test_base_units();
    //print_compile_mode();
    if( Eidos::esTestUnitSingleton() == false )
    {
        std::println("Test failed");
    }


}
