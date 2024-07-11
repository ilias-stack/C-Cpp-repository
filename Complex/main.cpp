#include <iostream>
#include "c_arithmetics.h"

using namespace std;

int main()
{
    Complex c1(1, -3), c2(12);
    cout << c1 + c2 - 4;
    return EXIT_SUCCESS;
}