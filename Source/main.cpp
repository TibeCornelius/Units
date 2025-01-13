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
    Meter m1 = {5};
    Meter m2 = { 10 };
    auto vect = CreateVector( m1, m2 );
    auto Vect2 = CreateVector( m2, m1 );
    auto DotProductR = vect * Vect2;
}
