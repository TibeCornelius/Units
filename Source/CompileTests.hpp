#include "Unitree.hpp"
using namespace Unit;
void test_compile_definitions()
{
    Meter m1 = 5;
    double d = 4;
    auto result = m1 + d;
    result.print_units();
    if( m1 == d )
    {
        std::cout<<"Semi unit safety\n";
    }
    else
    {
        std::cout<<"Equality not reached\n";
    }
}
