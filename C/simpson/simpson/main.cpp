#include <iostream>

using namespace std;

double integrate(float x_0, float x_n, int n);

int main()
{
    cout << integrate(0, 6, 1000) << endl;
    return 0;
}
