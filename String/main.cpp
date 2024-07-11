#include <iostream>
#include "myString.h"
using namespace std;

int main()
{

    myString a = "string a.";
    myString b = "string b";
    a = a + " this is additional text";
    a[3] = 'O';
    b.replace("string", "char array");
    cout << a << endl;
    cout << b << endl;
    b.clear();
    cout << b.isEmpty() << endl;
    b.append("appended Text");

    b.append(" in", 8);
    cout << b << endl;

    myString c = "c", d = "d";
    bool k = c < d;
    cout << k << endl;

    return EXIT_SUCCESS;
}