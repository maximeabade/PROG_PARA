#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define TOL 0.001

double randomFloat();

int main(int argc, char **argv)
{
    long int M, N, P;   /* A[M][N], B[N][P], C[M][P] */
    long int i, j, k;
    float **A, **B, **C, tmp;
    float aval, bval, cval;
    float err, errsq;
    double start_time, run_time;
    int tid, nth; // Number of threads

    nth = 4;

    M = 10;
    N = 10;
    P = 10;

    aval = 3.0;
    bval = 2.0;

    A = (float **)malloc(M * sizeof(float *));
    B = (float **)malloc(N * sizeof(float *));
    C = (float **)malloc(M * sizeof(float *));

    for (i = 0; i < M; i++)
    {
        A[i] = (float *)malloc(N * sizeof(float));
        C[i] = (float *)calloc(P, sizeof(float));
    }

    for (i = 0; i < N; i++)
    {
        B[i] = (float *)malloc(P * sizeof(float));
    }

    /* Initialise matrices */

    for (i = 0; i < M; i++)
        for (j = 0; j < N; j++)
            A[i][j] = aval;

    for (i = 0; i < N; i++)
        for (j = 0; j < P; j++)
            B[i][j] = bval;

    omp_set_num_threads(nth);

    /* Do the matrix product */

    start_time = omp_get_wtime();

#pragma omp parallel private(i, j, k, tmp)
    {
#pragma omp for
        for (i = 0; i < M; i++)
        {
            for (j = 0; j < P; j++)
            {
                tmp = 0.0;
                for (k = 0; k < N; k++)
                {
                    tmp += A[i][k] * B[k][j];
                }
                C[i][j] = tmp;
            }
        }
    }

    run_time = omp_get_wtime() - start_time;
    printf("\nTime to complete the matrix product: %lf\n", run_time);

    /* Check results */
    cval = aval * bval * (float)N;
    errsq = 0.0;
    for (i = 0; i < M; i++)
    {
        for (j = 0; j < P; j++)
        {
            err = C[i][j] - cval;
            errsq += err * err;
            printf("%.2f\t", C[i][j]);
        }
        printf("\n");
    }

    if (errsq > TOL)
        printf("\nErrors in multiplication: %f\n", errsq);
    else
        printf("\nThe result is correct\n");
}

/* Generates a double value between 0 and 1 */
double randomFloat()
{
    return (double)rand() / RAND_MAX;
}
