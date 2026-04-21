#include <bits/stdc++.h>
#include <mpi.h>
using namespace std;

int main(int argc, char** argv) {
    int size, rank;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int N = 0;
    if (rank == 0) cin >> N;

    MPI_Bcast(&N, 1, MPI_INT, 0, MPI_COMM_WORLD);

    int chunk = N / size;

    int start_index = rank * chunk;

    int end_index;
    if (rank == size - 1) {
        end_index = N;
    } else {
        end_index = start_index + chunk;
    }

    int iterations = end_index - start_index;

    double x = (2 * start_index) + 1;
    double d = (start_index % 2 == 0) ? 1 : -1;

    double partial_sum = 0;

    for (int i = 0; i < iterations; i++) {
        partial_sum += (d / x);
        x += 2;
        d *= -1;
    }

    printf("I am Process %d and my Partial Sum is %f\n", rank, partial_sum);

    double total_sum = 0;
    MPI_Reduce(&partial_sum, &total_sum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        double PI = 4 * total_sum;
        printf("PI is %f\n", PI);
    }

    MPI_Finalize();
    return 0;
}