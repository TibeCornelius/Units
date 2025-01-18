#include<iostream>
#include "Unitree.hpp"

using namespace Unit;
int main()
{
    Scalar s = 5;
    auto Vect = create_vector_2x2(s,s);
    Radian angle = Vect.get_angle_x_axis();
    std::cout<<"Angle --> "<< angle<<"\n";
}
