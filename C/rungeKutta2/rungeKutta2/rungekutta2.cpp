/* Runge-Kutta 2
 *
 * Function declarations:
 *      void rungeKutta2(double x_0, double y_0, double x_n, double deltaX);
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
 * RK2 is divided into 2 stages. From 1st stage we get temporary x, y, and slope.
 * Temporary slope is added to 2nd stage (to be more precise), so:
 *
 *      y_n+1 = y_n + ((slope + temporary slope)/2) * deltaX
 *
 * Data (x and y) will be stored in a file called "RK2_data.txt"
 *
 * n.b.: mind for pitfalls of this numerical solution when singularity happens
 *
 *
 * Created on March 31, 2017
 * Author: Ramadian Ridho Illahi
 * */

#include <iostream>
#include <cmath>
#include <fstream>

using namespace std;

double slope(double x, double y){
    return (5*pow(x,2)- y) / (exp(x+y));
}

void rungeKutta2(double x_0, double y_0, double x_n, double deltaX){
    //create a file to store data
    ofstream file("RK2_data.txt");

    for(x_0 ; x_0 <= x_n ; x_0 += deltaX){
        //temporary y, x, and slope: y(xTemp) = yTemp
        double xTemp = x_0 + deltaX;
        double yTemp = y_0 + slope(x_0, y_0) * deltaX;
        double slopeTemp = slope(xTemp, yTemp);

        //y_n+1
        double y_1 = y_0 + ((slope(x_0, y_0) + slopeTemp) / 2) * deltaX;

        //write data to the file
        file << x_0 << "\t" << y_0 <<endl;

        cout << x_0 << "\t" << y_0 <<endl;

        y_0 = y_1;
    }
    file.close();
}
