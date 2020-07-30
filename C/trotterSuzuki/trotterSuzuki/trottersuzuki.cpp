/* Trotter Suzuki Method
 *
 * Function declarations:
 *      void trotterSuzuki(int boundary, double delta_x, double time);
 *
 * Parameters:
 *   boundary   = batas
 *    delta_x   = step untuk x
 *       time   = waktu yang dicari
 *
 *
 * Created on April 1st, 2018
 * Author: Ramadian Ridho Illahi
 * */

#include <iostream>
#include <cmath>
#include <fstream>
#include <complex>

using namespace std;

double PI = M_PI;

void trotterSuzuki(int boundary, double delta_x, double time){
    //batas
    double right_boundary = boundary;
    double left_boundary = -boundary;

    //variabel
    double delta_t = 0.1;
    double W = 1.0/(2.0*PI*delta_x);
    int N = abs((right_boundary - left_boundary) / delta_x);

    cout << "W : " << W <<endl;

    cout << "batas kanan : " << right_boundary <<endl;
    cout << "batas kiri : " << left_boundary <<endl;
    cout << "jumlah cacah : " << N <<endl;

    //deklarasi fungsi gelombang awal
    std::complex<double> psi_0[N];
    for(int i=0 ; i < N ; i++){
        double x_psi_0 = left_boundary+(i*((right_boundary-left_boundary)/(N-1)));
        psi_0[i] = std::complex<double> (sqrt(2.0/boundary)*sin(PI*x_psi_0/boundary),0);
        //psi_0[i] = std::complex<double> (sqrt(sqrt(1.0/(PI*20*delta_x*20*delta_x)))*exp(-pow((x_psi_0-(0)),2)/(2*20*delta_x*20*delta_x)),0);
        //psi_0[i] = std::complex<double> (0,2.0/sqrt(boundary)*sin(x_psi_0*PI/boundary));

        cout << i << "\t" << x_psi_0 << "\t" << psi_0[i] <<endl;
    }

    //normalisasi vektor masukan
    double sum_norm = 0;
    for(int i=0 ; i < N ; i++){
        sum_norm += norm(psi_0[i]);
    }

    cout << "sum_norm : " << sum_norm <<endl;
    cout << "sqrt(sum_norm) : " << sqrt(sum_norm) <<endl;

    std::complex<double> psi_0_normalisasi[N];
    for(int i=0 ; i < N ; i++){
        //double x_psi_0 = left_boundary+(i*((right_boundary-left_boundary)/(N-1)));
        psi_0_normalisasi[i] = std::complex<double> (real(psi_0[i])/sqrt(sum_norm),imag(psi_0[i])/sqrt(sum_norm));

        //cout << i << "\t" << x_psi_0 << "\t" << psi_0_normalisasi[i] <<endl;
    }


    //Menghitung perkalian dari algoritma Trotter-Suzuki
    std::complex<double> psi_3_normalisasi[N];
    double tau = 0;
    double t_pi = time*PI;
    do{
        cout << "tau : " << tau <<endl;

        //deklarasi matriks potensial
        std::complex<double> potential[N][N];
        for(int i=0 ; i < N ; i++){
            for(int j=0 ; j < N ; j++){
                double x_potential = left_boundary+(i*((right_boundary-left_boundary)/(N-1)));
                if(i==j){
                    double pot_x = 0;
                    //double pot_x = 0.5*x_potential*x_potential;
                    double cos_pot = cos(tau*pot_x);
                    double sin_pot = sin(tau*pot_x);

                    potential[i][j] = std::complex<double> (cos_pot,-sin_pot);
                }
                else potential[i][j] = std::complex<double> (0,0);

                //cout << potential[i][j] << "\t";
            }
            //cout <<endl;
        }

        //deklarasi matriks M (2x2)
        std::complex<double> M[2][2];
        M[0][0] = std::complex<double> (cos(abs(tau*W)),0);
        M[0][1] = std::complex<double> (0,-sin(abs(tau*W)));
        M[1][0] = std::complex<double> (0,-sin(abs(tau*W)));
        M[1][1] = std::complex<double> (cos(abs(tau*W)),0);

        cout << "00" << M[0][0] <<endl;
        cout << "01" << M[0][1] <<endl;
        cout << "10" << M[1][0] <<endl;
        cout << "11" << M[1][1] <<endl;

        //perkalian matriks exp(-i*tau*H_2) * psi_0_normalisasi
        std::complex<double> psi_1[N];
        std::complex<double> psi_0_reduce[2];
        for(int i=0 ; i < N ; i+=2){
            psi_0_reduce[0] = psi_0_normalisasi[i];
            psi_0_reduce[1] = psi_0_normalisasi[i+1];

            psi_1[i] = M[0][0]*psi_0_reduce[0] + M[0][1]*psi_0_reduce[1];
            psi_1[i+1] = M[1][0]*psi_0_reduce[0] + M[1][1]*psi_0_reduce[1];

            cout << i << "\t" << psi_1[i] <<endl;
            cout << i+1 << "\t" << psi_1[i+1] <<endl;

        }

        //perkalian matriks exp(-i*tau*H_1) * psi_1
        std::complex<double> psi_2[N];
        psi_2[0] = std::complex<double> (0,0);
        psi_2[N-1] = std::complex<double> (0,0);

        for(int i=1 ; i < N-1 ; i+=2){
            psi_0_reduce[0] = psi_1[i];
            psi_0_reduce[1] = psi_1[i+1];

            psi_2[i] = M[0][0]*psi_0_reduce[0] + M[0][1]*psi_0_reduce[1];
            psi_2[i+1] = M[1][0]*psi_0_reduce[0] + M[1][1]*psi_0_reduce[1];

            cout << i << "\t" << psi_2[i] <<endl;
            cout << i+1 << "\t" << psi_2[i+1] <<endl;

        }

        //perkalian matriks exp(-i*tau*H_0) * psi_2
        std::complex<double> psi_3[N];
        for(int i=0 ; i < N ; i++){
            psi_3[i] = potential[i][i] * psi_2[i];

            cout << i << "\t" << psi_3[i] <<endl;

        }

        //normalisasi psi_3
        sum_norm = 0;
        for(int i=0 ; i < N ; i++){
            sum_norm += norm(psi_3[i]);
        }

        cout << "sum_norm : " << sum_norm <<endl;
        cout << "sqrt(sum_norm) : " << sqrt(sum_norm) <<endl;


        for(int i=0 ; i < N ; i++){
            psi_3_normalisasi[i] = std::complex<double> (real(psi_3[i])/sqrt(sum_norm),imag(psi_3[i])/sqrt(sum_norm));
            cout << i << "\t" << psi_3_normalisasi[i] <<endl;
        }

        tau += delta_t*PI;
    }while(tau < t_pi);


    //simpan data psi(x) di file
    ofstream fileOutput("data_psi.txt");
    for(int i=0 ; i < N ; i++){
        fileOutput << left_boundary+(i*((right_boundary-left_boundary)/(N-1))) << "\t" << real(psi_3_normalisasi[i]) <<endl;
    }
    fileOutput.close();

    //menghitung kebolehjadian dan menyimpan datanya ke file
    std::complex<double> probability[N];
    ofstream fileOutput2("data_psi_prob.txt");
    for(int i=0 ; i < N ; i++){
        probability[i] = norm(psi_3_normalisasi[i]);
        fileOutput2 << left_boundary+(i*((right_boundary-left_boundary)/(N-1))) << "\t" << real(probability[i]) <<endl;
        cout << i << "\t" << probability[i] <<endl;
    }
    fileOutput2.close();

}
