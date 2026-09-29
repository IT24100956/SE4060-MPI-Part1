#include <mpi.h>
#include <stdio.h>

#define LIMIT 10000000LL

int main(int argc, char** argv) {
    int rank, size;
    long long local_sum = 0;
    long long global_sum = 0;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    double start_time = MPI_Wtime();

    // Divide range evenly across processes
    long long chunk_size = LIMIT / size;
    long long start = rank * chunk_size + 1;
    long long end = (rank == size - 1) ? LIMIT : (rank + 1) * chunk_size;

    for (long long i = start; i <= end; i++) {
        local_sum += i;
    }

    // Aggregate local sums to root process (rank 0)
    MPI_Reduce(&local_sum, &global_sum, 1, MPI_LONG_LONG, MPI_SUM, 0, MPI_COMM_WORLD);

    double end_time = MPI_Wtime();

    if (rank == 0) {
        long long expected = (LIMIT * (LIMIT + 1)) / 2;
        printf("Calculated Sum : %lld\n", global_sum);
        printf("Expected Sum   : %lld\n", expected);
        printf("Elapsed Time   : %f seconds (with %d processes)\n", end_time - start_time, size);
    }

    MPI_Finalize();
    return 0;
}
