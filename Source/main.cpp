#include<iostream>
#include "Unit.hpp"

int main()
{
    Radian angle = Pi;
    Meter magnitude = 5;
    auto v = CreateAngledVector2X2Vector( magnitude, angle );
}
