#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>


// -------------------------------------------------------------------------------
void multMat1(int n, double* A, double* B, double* C) {
    int i, j, k;
    float sum = 0.0;
    /* This is ijk loop order. */
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++) {
            for (k = 0; k < n; k++)
                C[i + j * n] += A[i + k * n] * B[k + j * n]; // C[i][j] += A[i][k] * B[k][j]; (a)Version ij k
        }
}

void multMat2(int n, double* A, double* B, double* C) {
    int i, j, k;
    //float r;
    /* This is ikj loop order. */
    for (i = 0; i < n; i++)
        for (k = 0; k < n; k++) {
            for (j = 0; j < n; j++)
                C[i + j * n] += A[i + k * n] * B[k + j * n]; //C[i][j] += A[i][k]*B[k][j]; // (f) Version ikj
        }
}

void multMat3(int n, double* A, double* B, double* C) {
    int i, j, k;
    /* This is jik loop order. */
    for (j = 0; j < n; j++)
        for (i = 0; i < n; i++) {
            for (k = 0; k < n; k++)
                C[i + j * n] += A[i + k * n] * B[k + j * n]; //C[i][j] += [i][k]*B[k][j]; (b) Version jik
        }

}


void multMat4(int n, double* A, double* B, double* C) {
    int i, j, k;
    /* This is jki loop order. */
    for (j = 0; j < n; j++)
        for (k = 0; k < n; k++) {
            for (i = 0; i < n; i++)
                C[i + j * n] += A[i + k * n] * B[k + j * n]; //C[i][j] += A[i][k]*B[k][j]; (c) Version jki
        }

}


void multMat5(int n, double* A, double* B, double* C) {
    int i, j, k;
    /* This is kij loop order. */
    for (k = 0; k < n; k++)
        for (i = 0; i < n; i++) {
            for (j = 0; j < n; j++)
                C[i + j * n] += A[i + k * n] * B[k + j * n];   //C[i][j] += A[i][k]*B[k][j]; (e) Version kij
        }

}

void multMat6(int n, double* A, double* B, double* C) {
    int i, j, k;
    /* This is kji loop order. */
    for (k = 0; k < n; k++)
        for (j = 0; j < n; j++) {
            for (i = 0; i < n; i++)
                C[i + j * n] += A[i + k * n] * B[k + j * n];    //C[i][j] += A[i][k]*B[k][j];   (d) Version kji
        }

}
//****************************************************************************************************/
void PrintMat(int n, double* M) {
    int i, j;

    for (j = 0; j < n; j++) {
        //printf("; \n");
        for (i = 0; i < n; i++)
            printf("%.3f ", M[i + j * n]);
        printf("; \n");
    }
    printf("\n\n");
}


//****************************************************************************************************/
FILE* fp;

int main(int argc, char *argv[]) {

    errno_t err;
    err = fopen_s(&fp, "D:/lab_105/ReportS16_double.txt", "a+");
   // err = fopen_s(&fp, "items.txt", "w+");

    if (err != 0)
    {
        printf("The file 'ReportS16_double' was not opened\n");
        //err = fclose(fp);
        return 0;
    }
   
if (argv[1]) {
 //printf( " input arg = %s " , argv[1]);
  int n= atoi(argv[1]); //se ingresa el tamaño de la matriz
 // printf( " input n = %d " , n);
  int samples=10; //5 muestras y se ignora la primera

    double* A = (double*)malloc(n*n* sizeof(double));
    double* B = (double*)malloc(n*n * sizeof(double));
    double* C = (double*)malloc(n*n * sizeof(double));
         
    for (int i = 0; i < n * n; i++) A[i] = (double)rand()/100;//;
    for (int i = 0; i < n * n; i++) B[i] = (double)rand()/100;//;
    for (int i = 0; i < n * n; i++) C[i] =(double)0;//;

    printf("version TypeData   #sample    n    time(s)        Normalized(ns)\n");
  for(int s=0;s<samples;s++){
    // Start measuring time
            clock_t start = clock();
            multMat6(n, A, B, C);     //select multMatv1, multMatv2, multMatv3, multMatv4
    // Stop measuring time and calculate the elapsed time
            clock_t end = clock();

           double seconds = (double)(end - start) / CLOCKS_PER_SEC;
           double N = n;
           double timeNormalized = (seconds * 1.0e9) / (N*N*N ); //ns
 
    printf( "%s\t  %03d\t %05d\t  %2.4f\t   %2.4f \n" , "ver6 \t d ", s,n, seconds, timeNormalized);
    fprintf_s(fp, "%s\t %03d\t %05d  %2.4f\t   %2.4f \n" , "ver6 \t d ",s, n, seconds, timeNormalized);    /* write data to the file */
  }
  //PrintMat(n, A);
  //PrintMat(n, B);
  //PrintMat(n, C);
   free(A);
   free(B);
   free(C);
   fclose(fp); /* close the file*/
}
    printf("\n");
    return 0;
}
