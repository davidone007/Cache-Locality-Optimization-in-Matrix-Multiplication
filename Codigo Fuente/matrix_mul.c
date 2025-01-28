#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>

// Función para multiplicar matrices con bloques
void multMatConBloques(int n, int l1_cache_size, float* A, float* B, float* C) {
    const int ELEMENT_SIZE = sizeof(float);  // Tamaño de un elemento en bytes
    int BLOCK_SIZE = l1_cache_size / ELEMENT_SIZE;  // Tamaño del bloque en elementos

    if (BLOCK_SIZE > n) {
        BLOCK_SIZE = n;
    }

    int i, j, k, jj, kk;

    for (jj = 0; jj < n; jj += BLOCK_SIZE) {
        for (kk = 0; kk < n; kk += BLOCK_SIZE) {
            for (j = jj; j < jj + BLOCK_SIZE && j < n; j++) {
                for (k = kk; k < kk + BLOCK_SIZE && k < n; k++) {
                    for (i = 0; i < n; i++) {
                        C[i + j * n] += A[i + k * n] * B[k + j * n];
                    }
                }
            }
        }
    }
}

int main(int argc, char* argv[]) {
    FILE* fp;

    errno_t err;
    err = fopen_s(&fp, "C:/Users/1126844663/Desktop/Report.txt", "a+");
    if (err != 0) {
        printf("The file 'Report.txt' was not opened\n");
        return 0;
    }

    if (argc >= 3) {
        int BLOCK_SIZE = atoi(argv[1]); // Tamaño del bloque
        int N = atoi(argv[2]); // Tamaño de la matriz
        int samples = 10; // 10 muestras

        float* A = (float*)malloc(N * N * sizeof(float));
        float* B = (float*)malloc(N * N * sizeof(float));
        float* C = (float*)malloc(N * N * sizeof(float));

        for (int i = 0; i < N * N; i++) A[i] = (float)rand() / RAND_MAX;
        for (int i = 0; i < N * N; i++) B[i] = (float)rand() / RAND_MAX;
        for (int i = 0; i < N * N; i++) C[i] = 0.0;

        printf("version        #sample   N    BLOCK_SIZE    time(s)      Normalized(ns)\n");

        for (int s = 0; s < samples; s++) {
            // Start measuring time
            clock_t start = clock();
            multMatConBloques(N, BLOCK_SIZE, A, B, C);
            // Stop measuring time and calculate the elapsed time
            clock_t end = clock();

            double seconds = (double)(end - start) / CLOCKS_PER_SEC;
            double N_n = N;
            double timeNormalized = (seconds * 1.0e9) / (N_n * N_n * N_n); // ns

            printf("%-14s %03d       %04d  %05d           %2.4f       %2.4f\n", "verBlockMulf", s, N, BLOCK_SIZE, seconds, timeNormalized);
            fprintf(fp, "%-14s %03d       %04d  %05d           %2.4f       %2.4f\n", "verBlockMulf", s, N, BLOCK_SIZE, seconds, timeNormalized);
        }

        free(A);
        free(B);
        free(C);
        fclose(fp);
    }
    else {
        printf("Usage: %s <BLOCK_SIZE> <N>\n", argv[0]);
    }

    printf("\n");
    return 0;
}