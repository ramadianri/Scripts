#include <iostream>

using namespace std;

int main()
{
    //dimensi matrix NxN
    int N = 10;

    //komponen tridiagonalmatrix A
    int a = 1;
    int b = -2;
    int c = 1;

    //deklarasi tridiagonal matrix A
    int A[N][N];

    //mengkonstruksi tridiagonal matrix A
    for(int i=0 ; i < N ; i++){
        for(int j=0 ; j < N ; j++){
            //memasukkan komponen a, b, c
            if(j== i-1)
                A[i][j] = a;
            else if(j==i)
                A[i][j] = b;
            else if(j== i+1)
                A[i][j] = c;

            //komponen sisanya bernilai 0
            else A[i][j] = 0;

            cout << A[i][j] << "\t";
        }
        cout <<endl;
    }

    return 0;
}
