#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

void printMatrix(int *matrix, int rows, int cols);
void matrixMultiplication(int *matrixA, int *matrixB, int *matrixC, int rows, int cols);

int main(int argc, char *argv[]) {
    int myid, np, i, j;
    int N = 15; // Taille des matrices
    int matrixA[N][N], matrixB[N][N], matrixC[N][N];

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &myid);
    MPI_Comm_size(MPI_COMM_WORLD, &np);

    // Initialiser la matrice B dans le processus 0
    if (myid == 0) {
        for (i = 0; i < N; i++) {
            for (j = 0; j < N; j++) {
                matrixB[i][j] = 1;
            }
        }
    }

    // Diffuser la matrice B à tous les processus
    MPI_Bcast(matrixB, N * N, MPI_INT, 0, MPI_COMM_WORLD);

    // Initialiser la matrice A dans le processus 0
    if (myid == 0) {
        for (i = 0; i < N; i++) {
            for (j = 0; j < N; j++) {
                matrixA[i][j] = i * N + j; // Exemple d'initialisation, à remplacer par votre logique
            }
        }
    }

    // Répartir la matrice A par tranches de lignes
    int rows_per_proc = N / np;
    int *localA = (int *)malloc(rows_per_proc * N * sizeof(int));
    MPI_Scatter(matrixA, rows_per_proc * N, MPI_INT, localA, rows_per_proc * N, MPI_INT, 0, MPI_COMM_WORLD);

    // Allouer la mémoire pour la matrice C locale
    int *localC = (int *)malloc(rows_per_proc * N * sizeof(int));

    // Effectuer la multiplication matricielle
    matrixMultiplication(localA, matrixB, localC, rows_per_proc, N);

    // Rassembler les résultats de tous les processus
    MPI_Gather(localC, rows_per_proc * N, MPI_INT, matrixC, rows_per_proc * N, MPI_INT, 0, MPI_COMM_WORLD);

    // Afficher la matrice résultante
    if (myid == 0) {
        printf("Matrice résultante:\n");
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
