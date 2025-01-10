#include<iostream>
#include"Matrix.hpp"
#include"VectorD2.hpp"
#include"Units.hpp"
#include"Testing.hpp"
#include "Testing2.hpp"

void Test1()
{
    T1 t1 = {3};
    T1 t2 = {3};
    auto vect = MAKE_TV( t1, t2 );

    T2 Scalar = {5};

    auto VectR = vect * Scalar;

    VectR.Print();


    T1 t21 = {3};
    T1 t22 = {4};
    auto vect2 = MAKE_TV( t21, t22 );

    T3 Scalar2 = {2};

    auto VV = vect2 * Scalar2;
    VV.Print();

    T1 tt21 = {3};
    T2 tt22 = {4};
    auto vvect2 = MAKE_TV( tt21, tt22 );

    T3 Scalar22 = {2};

    auto VVV = vvect2 * Scalar22;
    VVV.Print();
}

int main()
{
    Unit<1,0> Meters = {1};
    Unit<1,0> Meters2 = {2};
    

    auto result = Meters + Meters2;

    Unit<2,0> Area = {1};

    auto r = Meters * Area;

    result.PrintType();
    r.PrintType();

}
