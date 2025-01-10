#include<iostream>
#include"Matrix.hpp"
#include"VectorD2.hpp"
#include"Units.hpp"
#include"Testing.hpp"


int main()
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

    /*TV<TT1> vect2;
    vect2.x = {4};
    vect2.y = {5};

    TT2 Scalar2 = {5};

    auto VectRR = vect2 * Scalar2;*/
}