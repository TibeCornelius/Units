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
    Meter meter = {5};
    Meter m2 = {3};

    auto result = meter * m2;

    Vector<Meter, Meter> v1 = {{5}, {3}};
    v1.PrintVerbose();
    Vector<int, int> v2 = {5,7};
    v2.PrintVerbose();


    Unit<3,5,-2,3,-2,1,0> something = {4};
    something.PrintUnits();
    something.PrintUnitsVerbose();

    auto Vect1 = CreateVector( meter, m2 );
    auto Vect2 = CreateVector( m2, meter );

    auto V_Result = Vect1 + Vect2;
    
    V_Result.Print();

    auto VOther = Vect1 * 5;

    auto VL = meter * Vect1;

    VOther.Print();
}
