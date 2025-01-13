#include<iostream>
#include "Testing2.hpp"

int main()
{
    Meter m1 = {5};
    Meter m2 = { 10 };
    auto vect = CreateVector( m1, m2 );
    auto Vect2 = CreateVector( m2, m1 );
    auto DotProductR = vect * Vect2;

    Meter m3 = 5;

    auto Vectorr = CreateVector( 5, 3 );
}
