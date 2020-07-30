/* Autocorrelation Function
 *
 * Function declarations:
 *      void Autocorrelation(const std::string& fileInputName, int tau_n);
 *
 * Parameters:
 *        fileInputName  = file input name in string
 *               tau_n   = number of maximum tau
 *
 * The correlation between two functions (or time series) is a measure of how similarly they behave.
 * The idea behind the concept of autocorrelation is to calculate the correlation coefficient of
 * a time series with itself, shifted in time. If the data has a periodicity, the correlation coefficient
 * will be higher when those two periods resonate with each other.
 *
 * Created on November 15, 2017
 * Author: Ramadian Ridho Illahi
 * */

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

//rerata
double Mean(double u[], int NN){
    double sum = 0.0;
    for(int j=0 ; j<NN ; j++){
        sum += u[j];
    }
    return sum/NN;
}

void Autocorrelation(const std::string& fileInputName, int tau_n){
    //menentukan jumlah data (N) pada file input
    int numberOfLines = 0;
    string line;
    ifstream fileInput(fileInputName);
    while (std::getline(fileInput, line))
        ++numberOfLines;
    int N = numberOfLines;
    cout << "Number of lines in text file: " << N <<endl;
    fileInput.close();

    //deklarasi array untuk menyimpan data
    double t[N]; //data x pada file input
    double u[N]; //data y pada file input
    double Q[N]; //array untuk menyimpan hasil autocorrelation

    //membaca data pada file input dan menyimpannya di array t & u
    fileInput.open(fileInputName);
    int index = 0;
    while( index < N && fileInput >> t[index] >> u[index] ){
        //cout << t[index]<< "\t" << u[index] <<endl;
        index++;
    }
    fileInput.close();

    //menghitung rerata u
    double uMean = Mean(u,N);

    //menghitung denominator
    double denominator = 0.0;
    for(int t=0 ; t < N ; t++){
        denominator += (u[t] - uMean) * (u[t] - uMean);
    }

    ofstream fileOutput("data_autocorr.txt");

    //menghitung numerator
    double numerator = 0.0;
    for(int tau=0 ; tau < tau_n ; tau++){
        for(int t = 0; t < N ; t++){
            numerator += ((u[t+tau] - uMean)  * (u[t] - uMean));
        }

        //menghitung Q[tau] untuk setiap tau
        Q[tau] = (numerator/N) / (denominator/N);

        cout << tau << "\t" << N << "\t" << numerator << "\t" << denominator << "\t" << Q[tau] <<endl;
        fileOutput << tau << "\t" << Q[tau] <<endl;

        //reset nilai numerator
        numerator = 0.0;
    }

    fileOutput.close();
}




