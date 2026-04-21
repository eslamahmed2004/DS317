#include <iostream>
#include <mpi.h>

using namespace std;

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);


    int N = 20;

    int chunk_size = N / size;

    int start = (rank * chunk_size) + 1;
    int end = (rank + 1) * chunk_size;

    if (rank == size - 1) {
        end = N;
    }

    long long local_sum = 0;
    for (int i = start; i <= end; i++) {
        local_sum += i;
    }
    cout << "Process " << rank << " calculated sum from " << start
         << " to " << end << " = " << local_sum << endl;

    MPI_Finalize();

    return 0;
}