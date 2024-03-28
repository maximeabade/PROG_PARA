#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Taille du vecteur
    int N = 50;

    // Déclaration des variables
    float* v = malloc(N * sizeof(float));
    float sum = 0.0;

    // Processus 0 génère le vecteur
    if (rank == 0) {
        for (int i = 0; i < N; i++) {
            v[i] = i + 1;
        }
    }

    // Diffusion de la taille du vecteur
    MPI_Bcast(&N, 1, MPI_INT, 0, MPI_COMM_WORLD);

    // Déclaration du vecteur local
    float* v_local = malloc(N / size * sizeof(float));

    // Diffusion du vecteur
    MPI_Scatter(v, N / size, MPI_FLOAT, v_local, N / size, MPI_FLOAT, 0, MPI_COMM_WORLD);

    // Affichage du vecteur local
    printf("Processus %d - Vecteur local : ", rank);
    for (int i = 0; i < N / size; i++) {
        printf("%f ", v_local[i]);
    }
    printf("\n");

    // Calcul de la somme partielle
    for (int i = 0; i < N / size; i++) {
        sum += v_local[i];
    }

    // Affichage de la somme partielle
    printf("Processus %d - Somme partielle : %f\n", rank, sum);

    // Réduction de la somme
    MPI_Allreduce(MPI_IN_PLACE, &sum, 1, MPI_FLOAT, MPI_SUM, MPI_COMM_WORLD);

    // Normalisation du vecteur local
    for (int i = 0; i < N / size; i++) {
        v_local[i] /= sum;
    }

    // Rassemblement du vecteur
    MPI_Gather(v_local, N / size, MPI_FLOAT, v, N / size, MPI_FLOAT, 0, MPI_COMM_WORLD);

    // Affichage du résultat par le processus 0
    if (rank == 0) {
        printf("Résultat final : ");
        for (int i = 0; i < N; i++) {
            printf("%f ", v[i]);
        }
        printf("\n");
    }

    MPI_Finalize();
    return 0;
}
