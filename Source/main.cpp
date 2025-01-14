#include<iostream>
#include "Unitree.hpp"

int main()
{
    Radian angle = Pi;
    Meter magnitude = 5;
    auto v = CreateAngledVector2X2Vector( magnitude, angle );
}
