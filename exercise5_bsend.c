#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
    int rank, size;
    int data = 12345;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size < 2) {
        if (rank == 0) printf("Run with at least 2 processes.\n");
        MPI_Finalize();
        return 0;
    }

    if (rank == 0) {
        // Allocate and attach user-controlled buffer for MPI_Bsend
        int buffer_size = sizeof(int) + MPI_BSEND_OVERHEAD;
        char* bsend_buffer = (char*)malloc(buffer_size);
        MPI_Buffer_attach(bsend_buffer, buffer_size);

        printf("[Rank 0] Sending %d using MPI_Bsend\n", data);
        MPI_Bsend(&data, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);

        // Detach buffer (ensures message has left the local buffer)
        int detached_size;
        char* detached_ptr;
        MPI_Buffer_detach(&detached_ptr, &detached_size);
        free(detached_ptr);
    } else if (rank == 1) {
        int received_data = 0;
        MPI_Recv(&received_data, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("[Rank 1] Successfully received %d\n", received_data);
    }

    MPI_Finalize();
    return 0;
}
