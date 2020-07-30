/* Newton-Raphson Method
 *
 * Function declarations:
 *      double roots(double x_0, double epsilon);
 *
 * Parameters:
 *      x_0     = guess value for x
 *      epsilon = tolerance for x_1 ~ x_0
 *
 * Finding successively better approximations to the roots (or zeroes) of a real-valued functions.
 *
 *                 y(x_0)
 *      x_1 = x_0 - -------
 *                 y'(x_0)
 *
 * Iterate until x_1 ~ x_0
 *
 *
 * Created on June 23, 2017
 * Author: Ramadian Ridho Illahi
 * */

#include <iostream>
#include <cmath>
#include <cassert>

using namespace std;

double function(double x){
    return pow(x,4) - 16;
}

double funcDerivative(double x){
    return 4 * pow(x,3);
}

double roots(double x_0, double epsilon)
{
    //max iterations
    int i_max = 10000000;

    //y'(x) must not equal to zero
    assert(funcDerivative(x_0) != 0);

    double x;
    for(int i = 0; i < i_max ; i++){
        x = x_0 - (function(x_0)/funcDerivative(x_0));
        //cout << x_0 << "\t" << x << endl;

        if(abs(x - x_0) < epsilon){
            break;
        }
        x_0 = x;
    }

    return x;
}
