#include<iostream>
#include "Unitree.hpp"
#include "Rational.hpp"

int main()
{
    Scalar s = 5;
    auto Vect = CreateVector2X2(s,s);
    Radian angle = Vect.GetAngleXaxis();
    std::cout<<"Angle --> "<< angle<<"\n";
}
