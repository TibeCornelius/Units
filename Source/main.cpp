#include<iostream>
#include"Matrix.hpp"
#include"VectorD2.hpp"
#include"Units.hpp"
#include"Testing.hpp"


int main()
{
    TV<T1> vect;
    vect.x = {4};
    vect.y = {4};

    T2 Scalar = {5};

    auto VectR = vect * Scalar;

    /*TV<TT1> vect2;
    vect2.x = {4};
    vect2.y = {5};

    TT2 Scalar2 = {5};

    auto VectRR = vect2 * Scalar2;*/
}