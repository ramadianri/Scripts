/* Euler Method
 *
 * Function declarations:
 *      void euler(double x_0, double y_0, double x_n, double deltaX);
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
 * The main formula for this method was developed from slope formula (deltaY = slope * deltaX) into:
 *
 *      y_n+1 = y_n + slope * deltaX
 *
 * Data (x and y) will be stored in a file called "euler_data.txt"
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

void euler(double x_0, double y_0, double x_n, double deltaX){
    //create a file to store data
    ofstream file("euler_data.txt");

    for(x_0 ; x_0 <= x_n ; x_0 += deltaX){
        //y_n+1
        double y_1 = y_0 + slope(x_0, y_0) * deltaX;

        //write data to the file
        file << x_0 << "\t" << y_0 <<endl;

        cout << x_0 << "\t" << y_0 <<endl;

        y_0 = y_1;
    }
    file.close();
}
