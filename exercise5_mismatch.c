#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) {
    int rank, size;
    int message = 42;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size < 2) {
        if (rank == 0) printf("Run with at least 2 processes.\n");
        MPI_Finalize();
        return 0;
    }

    if (rank == 0) {
        printf("[Rank 0] Sending message to Rank 1...\n");
        // Rank 0 sends to Rank 1
        MPI_Send(&message, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
    } else if (rank == 1) {
        int received_val = 0;
        printf("[Rank 1] Waiting for message from non-existent sender Rank 2...\n");
        // Mismatch: Rank 1 waits for Rank 2, but Rank 2 never sends
        MPI_Recv(&received_val, 1, MPI_INT, 2, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("[Rank 1] Received: %d\n", received_val);
    }

    MPI_Finalize();
    return 0;
}
