#include <bits/stdc++.h>
#include <mpi.h>
using namespace std;

int main(int argc, char** argv) {
    int size, rank;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int N = 100;
    int chunk = N / size;

    int *a = NULL;
    int *b = NULL;
    if (rank == 0) {
        a = new int[N];
        b = new int[N];
        for (int i = 0; i < N; i++) {
            a[i] = i + 1;
            b[i] = i + 1;
        }
    }

    int *local_a = new int[chunk];
    int *local_b = new int[chunk];

    MPI_Scatter(a, chunk, MPI_INT, local_a, chunk, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Scatter(b, chunk, MPI_INT, local_b, chunk, MPI_INT, 0, MPI_COMM_WORLD);

    int local_sum = 0;
    for (int i = 0; i < chunk; i++) {
        local_sum += local_a[i] * local_b[i];
    }

    printf("I am Processor %d and My Local Sum is %d\n", rank, local_sum);

    int dot_product = 0;
    MPI_Reduce(&local_sum, &dot_product, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("Dot Product is %d\n", dot_product);
    }

    delete[] local_a;
    delete[] local_b;
    if (rank == 0) {
        delete[] a;
        delete[] b;
    }

    MPI_Finalize();
    return 0;
}