#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h> 

#define N 4

void printMatrix(int *matrix, int rows, int cols);
void matrixMultiplication(int *matrixA, int *matrixB, int *matrixC, int rows, int cols);

int main(int argc, char *argv[]) {
    int myid, np, i, j;
    int matrixA[N][N], matrixB[N][N], matrixC[N][N];

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &myid);
    MPI_Comm_size(MPI_COMM_WORLD, &np);

    srand(time(NULL) + myid); // Seed le générateur de nombres aléatoires avec une valeur différente pour chaque processus

    if (myid == 0) {
        // Initialisation de la matrice A
        printf("Matrice A initialisée :\n");
        for (i = 0; i < N; i++) {
            for (j = 0; j < N; j++) {
                matrixA[i][j] = rand() % 11; // Nombres aléatoires entre 0 et 10 inclus
                printf("%d ", matrixA[i][j]);
            }
            printf("\n");
        }

        // Initialisation de la matrice B
        printf("Matrice B initialisée :\n");
        for (i = 0; i < N; i++) {
            for (j = 0; j < N; j++) {
                matrixB[i][j] = rand() % 11; // Nombres aléatoires entre 0 et 10 inclus
                printf("%d ", matrixB[i][j]);
            }
            printf("\n");
        }
    }

    // Diffusion de la matrice B à tous les processus
    MPI_Bcast(matrixB, N * N, MPI_INT, 0, MPI_COMM_WORLD);

    int rows_per_proc = N / np;
    int *localA = (int *)malloc(rows_per_proc * N * sizeof(int));
    MPI_Scatter(matrixA, rows_per_proc * N, MPI_INT, localA, rows_per_proc * N, MPI_INT, 0, MPI_COMM_WORLD);

    int *localC = (int *)malloc(rows_per_proc * N * sizeof(int));

    matrixMultiplication(localA, matrixB, localC, rows_per_proc, N);

    MPI_Gather(localC, rows_per_proc * N, MPI_INT, matrixC, rows_per_proc * N, MPI_INT, 0, MPI_COMM_WORLD);

    if (myid == 0) {
        printf("Matrice résultante :\n");
        printMatrix(matrixC, N, N);
    }

    MPI_Finalize();
    return 0;
}

void printMatrix(int *matrix, int rows, int cols) {
    int i, j;
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            printf("%d ", matrix[i * cols + j]);
        }
        printf("\n");
    }
}

void matrixMultiplication(int *matrixA, int *matrixB, int *matrixC, int rows, int cols) {
    int i, j, k;
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            matrixC[i * cols + j] = 0;
            for (k = 0; k < cols; k++) {
                matrixC[i * cols + j] += matrixA[i * cols + k] * matrixB[k * cols + j];
            }
        }
    }
}
