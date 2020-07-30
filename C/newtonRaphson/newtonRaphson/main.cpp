#include <iostream>

using namespace std;

double roots(double x_0, double epsilon);

int main()
{
    cout << roots(1, 0.0001) << endl;
    return 0;
}
