#include <omp.h>
#include <mpi.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    int rank, size;
    int N = 10;
    int NC = 10;
    int R = 10;
    int A[N][R], B[R][NC], C[N][NC];
    int i, j, k;
    int chunk_size;
    int num_workers;
    int start, end;
    int worker;
    int tag = 0;
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Master
    if (rank == 0) {
        // Initialize A and B
        for (i = 0; i < N; i++) {
            for (j = 0; j < R; j++) {
                A[i][j] = 1;
            }
        }
        for (i = 0; i < R; i++) {
            for (j = 0; j < NC; j++) {
                B[i][j] = 1;
            }
        }

        // Divide the rows of A in as many chunks as workers
num_workers = size - 1;
chunk_size = N / num_workers;
int extra = N % num_workers;
start = 0;
for (worker = 1; worker <= num_workers; worker++) {
    end = start + chunk_size - 1;
    if (extra > 0) {
        end++;
        extra--;
    }
    MPI_Send(&chunk_size, 1, MPI_INT, worker, tag, MPI_COMM_WORLD);
    MPI_Send(&A[start][0], (end - start + 1) * R, MPI_INT, worker, tag, MPI_COMM_WORLD);
    MPI_Send(&B, R * NC, MPI_INT, worker, tag, MPI_COMM_WORLD);
    start = end + 1;
}

        // Receive the results from the workers
        for (worker = 1; worker <= num_workers; worker++) {
            MPI_Recv(&start, 1, MPI_INT, MPI_ANY_SOURCE, tag, MPI_COMM_WORLD, &status);
            MPI_Recv(&C[start][0], chunk_size * NC, MPI_INT, status.MPI_SOURCE, tag, MPI_COMM_WORLD, &status);
        }

        // Print the result
        for (i = 0; i < N; i++) {
            for (j = 0; j < NC; j++) {
                printf("%d ", C[i][j]);
            }
            printf("\n");
        }
    }
    // Worker
    else {
        MPI_Recv(&chunk_size, 1, MPI_INT, 0, tag, MPI_COMM_WORLD, &status);
        int chunk_A[chunk_size][R], chunk_C[chunk_size][NC];

        MPI_Recv(&chunk_A, chunk_size * R, MPI_INT, 0, tag, MPI_COMM_WORLD, &status);
        MPI_Recv(&B, R * NC, MPI_INT, 0, tag, MPI_COMM_WORLD, &status);

        // Perform matrix multiplication
        for (i = 0; i < chunk_size; i++) {
            for (j = 0; j < NC; j++) {
                chunk_C[i][j] = 0;
                for (k = 0; k < R; k++) {
                    chunk_C[i][j] += chunk_A[i][k] * B[k][j];
                }
            }
        }

        // Send the result back to the master
        MPI_Send(&start, 1, MPI_INT, 0, tag, MPI_COMM_WORLD);
        MPI_Send(&chunk_C, chunk_size * NC, MPI_INT, 0, tag, MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return 0;
}
