/* Runge-Kutta 4
 *
 * Function declarations:
 *      void rungeKutta4(double x_0, double y_0, double x_n, double deltaX);
 *
 * Parameters:
 *        x_0   = x init
 *        y_0   = y init
 *        x_n   = x max
 *      deltaX  = step for x
 *
 * A numerical solution for solve first order ODEs with initial value:
 *
 *      slope = y' = f(x,y)
 *      y(x_0) = y_0
 *
 * The main formula for this method was developed from slope formula (deltaY = slope * deltaX)
 * and re-arrange into:
 *
 *      y_n+1 = y_n + slope * deltaX
 *
 * RK4 is divided into 4 stages. From each stages we get temporary x, y, and slope.
 * Temporary slope is added to next stage (to be more precise), so:
 *
 *      y_n+1 = y_n + (1/6) * (k_1 + 2*k_2 + 2*k_3 + k_4)
 *
 * Data (x and y) will be stored in a file called "RK4_data.txt"
 *
 * n.b.: mind for pitfalls of this numerical solution when singularity happens
 *
 *
 * Created on July 1st, 2017
 * Author: Ramadian Ridho Illahi
 * */

#include <iostream>
#include <cmath>
#include <fstream>

using namespace std;

double slope(double x, double y){
    return (5*pow(x,2)- y) / (exp(x+y));
}

void rungeKutta4(double x_0, double y_0, double x_n, double deltaX){

    double k_1, k_2, k_3, k_4, y_1;

    //create a file to store data
    ofstream file("RK4_data.txt");

    for(x_0 ; x_0 <= x_n ; x_0 += deltaX){
        //temporary y, x, and slope
        k_1 = slope(x_0, y_0) * deltaX;
        k_2 = slope(x_0 + deltaX/2, y_0 + k_1/2) * deltaX;
        k_3 = slope(x_0 + deltaX/2, y_0 + k_2/2) * deltaX;
        k_4 = slope(x_0 + deltaX, y_0 + k_3) * deltaX;

        //y_n+1
        y_1 = y_0 + (1/6.0) * (k_1 + 2*k_2 + 2*k_3 + k_4);

        //write data to the file
        file << x_0 << "\t" << y_0 <<endl;

        cout << x_0 << "\t" << y_0 <<endl;

        y_0 = y_1;
    }
    file.close();
}
