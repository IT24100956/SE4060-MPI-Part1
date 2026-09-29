#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TOTAL_ITERATIONS 10000000LL

int main(int argc, char** argv) {
    int rank, size;
    long long local_count = 0;
    long long total_count = 0;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    double start_time = MPI_Wtime();

    long long iterations_per_proc = TOTAL_ITERATIONS / size;
    if (rank == size - 1) {
        iterations_per_proc += (TOTAL_ITERATIONS % size);
    }

    unsigned int seed = (unsigned int)(time(NULL) ^ (rank << 16));

    for (long long i = 0; i < iterations_per_proc; i++) {
        double x = (double)rand_r(&seed) / RAND_MAX;
        double y = (double)rand_r(&seed) / RAND_MAX;
        if (x * x + y * y <= 1.0) {
            local_count++;
        }
    }

    if (rank != 0) {
        MPI_Send(&local_count, 1, MPI_LONG_LONG, 0, 0, MPI_COMM_WORLD);
    } else {
        total_count = local_count;
        MPI_Status status;

        // Receive from ANY worker on a first-come, first-served basis
        for (int i = 1; i < size; i++) {
            long long temp = 0;
            MPI_Recv(&temp, 1, MPI_LONG_LONG, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &status);
            printf("[Root] Received partial count %lld from Rank %d\n", temp, status.MPI_SOURCE);
            total_count += temp;
        }

        double pi = 4.0 * (double)total_count / (double)TOTAL_ITERATIONS;
        double end_time = MPI_Wtime();

        printf("Estimated Pi : %f\n", pi);
        printf("Elapsed Time : %f seconds (with %d processes)\n", end_time - start_time, size);
    }

    MPI_Finalize();
    return 0;
}
