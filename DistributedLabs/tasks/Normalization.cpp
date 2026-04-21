#include <bits/stdc++.h>
#include <mpi.h>
using namespace std;

int main(int argc, char** argv) {
    int size, rank;
    long long N = 0;
    double global_max, global_min;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0) cin >> N;
    MPI_Bcast(&N, 1, MPI_LONG_LONG, 0, MPI_COMM_WORLD);

    long long chunk = N / size;

    double* local_data = new double[chunk];
    double* norm_data = new double[chunk];

    double* global_data = NULL;
    if (rank == 0) {
        global_data = new double[N];
    }

    double local_max = -1e9;
    double local_min = 1e9;

    for (int i = 0; i < chunk; i++) {
        local_data[i] = (double)rank * 10.0 + (double)i;
        if (local_data[i] > local_max) local_max = local_data[i];
        if (local_data[i] < local_min) local_min = local_data[i];
    }

    MPI_Reduce(&local_max, &global_max, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);
    MPI_Reduce(&local_min, &global_min, 1, MPI_DOUBLE, MPI_MIN, 0, MPI_COMM_WORLD);

    MPI_Bcast(&global_max, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Bcast(&global_min, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    for (int i = 0; i < chunk; i++) {
        if (global_max == global_min) {
            norm_data[i] = 0.0;
        } else {
            norm_data[i] = (local_data[i] - global_min) / (global_max - global_min);
        }
    }

    MPI_Gather(norm_data, chunk, MPI_DOUBLE, global_data, chunk, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("Normalization Done! Global Min: %f, Global Max: %f\n", global_min, global_max);
    }

    MPI_Finalize();

    delete[] local_data;
    delete[] norm_data;
    if (rank == 0) delete[] global_data;

    return 0;
}