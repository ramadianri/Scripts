/* Pi
 *
 * Function declarations:
 *      double pi();
 *
 * Compute pi, where pi equal to area of circel unit x^2 + y^2 = 1.
 * The area of a quarter unit circle can be computed by integrating y(x) = sqrt(1-(x^2))
 * from 0 to 1.
 *
 *               1
 *               /
 *      pi = 4 * | sqrt(1-(x^2)) dx
 *               /
 *              0
 *
 * Created on March 31, 2017
 * Author: Ramadian Ridho Illahi
 * */

#include <iostream>
#include <stdlib.h>
#include <cmath>
#include <omp.h>

#define NUM_THREADS 4

using namespace std;

double pi(){
    int steps=10000000;
    float delta_x = 1/(float)steps;
    double sum=0;

    //allocate memory
    double * x, * y, *d_sum;
    x = (double*) malloc(steps*sizeof(double));
    y = (double*) malloc(steps*sizeof(double));
    d_sum = (double*) malloc(NUM_THREADS*sizeof(double));

    //compute y(x) * delta_x for each step
    #pragma omp parallel num_threads(NUM_THREADS)
    {
        int d_id = omp_get_thread_num();
        int d_numthreads = omp_get_num_threads();

        d_sum[d_id]=0;

        for(int i=d_id ; i<steps ; i+= d_numthreads){
            x[i]=i*delta_x;
            y[i]=sqrt(1-(pow(x[i],2)));

            //add y(x) * delta_x for each thread
            d_sum[d_id] += y[i]*delta_x;
        }
    }

    //add all y(x) * delta_x
    for(int i=0 ; i<NUM_THREADS ; i++) sum += d_sum[i];

    free(x);
    free(y);
    free(d_sum);

    //compute pi
    return 4*sum;
}
