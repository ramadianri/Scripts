/* Kahan Summation
 *
 * Function declarations:
 *      double kahanSum(double list_Kahan[], int listLength);
 *
 * The Kahan summation algorithm is a method of summing a series of numbers
 * represented in a limited precision in a way that minimises the loss of precision
 * in the result.
 *
 * Created on August 24, 2017
 * Author: Ramadian Ridho Illahi
 * */

#include <iostream>
#include <stdlib.h>
#include <cmath>
#include <array>

using namespace std;

double kahanSum(double list_Kahan[], int listLength){
    double sum = 0.0;

    //A running compensation for lost low-order bits
    double c = 0.0;

    for(int i=0 ; i<listLength ; i++){
        double y = list_Kahan[i] - c;
        double t = sum + y;

        c = (t - sum) - y;
        sum = t;
    }

    return sum;
}
