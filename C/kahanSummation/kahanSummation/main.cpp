#include <iostream>
#include <stdlib.h>
#include <array>
#include <cmath>

using namespace std;

double kahanSum(double list_Kahan[], int listLength);

int main()
{
    double a,b,c;
    a = 10000.0;
    b = 3.14159;
    c = 2.71828;

    int listLength = 3;
    double myList[listLength];
    myList[0] = a;
    myList[1] = b;
    myList[2] = c;

    double exact = (a+b);

    float nearest = roundf(exact * 10) / 10;

    exact = nearest;
    exact += c;

    nearest = roundf(exact * 10) / 10;
    //cout <<  nearest<<endl;

    cout << "kahan sum: " << kahanSum(myList, listLength) <<endl;

    return 0;
}
