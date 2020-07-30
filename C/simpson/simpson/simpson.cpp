/* Simpson's Rule
 *
 * Function declarations:
 *      double integrate(float x_0, float x_n, int n);
 *
 * Parameters:
 *      x_0 = lower boundary
 *      x_n = upper boundary
 *       n  = amount of sliced area under curve (n must be even)
 *
 * Integrate a function by sliced area under curve into n pieces (n mmust be even). Take 2 pieces
 * and compute area under parabola (approximation) :
 *
 *                   y_0 + 4*y_1 + y_2
 * Average height = -------------------       Base = 2 * delta_x      Area = Average height * Base
 *                           6
 *
 * Sum all areas to get :
 *
 *      delta_x
 *      ------- (y_0 + 4*y_1 + 2*y_2 + 4*y_3 + ... + 2*y_n-2 + 4*y_n-1 + y_n)
 *         3
 *
 *
 * Created on June 24, 2017
 * Author: Ramadian Ridho Illahi
 * */

#include <iostream>
#include <cmath>
#include <cassert>

using namespace std;

double function(double x){
    return 2*x;
}

double integrate(float x_0, float x_n, int n){
    //n must be even
    assert(n % 2 == 0 && "n must be even" );

    //base for each pieces
    float delta_x = (x_n - x_0) / n;

    //edges
    double y_0 = function(x_0);
    double y_n = function(x_n);

    //odd part
    double summOdd = 0;
    for(float x_odd = x_0 + delta_x ; x_odd < x_n ; x_odd += 2*delta_x){
        summOdd += 4*(function(x_odd));
    }

    //even part
    double summEven = 0;
    for(float x_even = x_0 + (2*delta_x) ; x_even < x_n ; x_even += 2*delta_x){
        summEven += 2*(function(x_even));
    }

    //sum all pieces (area)
    double area;
    area = (delta_x/3)*(y_0 + summOdd + summEven + y_n);

    return area;
}
