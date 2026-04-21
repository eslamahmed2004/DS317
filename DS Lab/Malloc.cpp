#include <iostream>
#include <cstdlib>
#include <chrono>
using namespace std;
using namespace std::chrono;

int** allocate_matrix(int M, int N) {
    int** mat = (int**)malloc(M * sizeof(int*));
    for(int i = 0; i < M; i++) {
        mat[i] = (int*)malloc(N * sizeof(int));
    }
    return mat;
}

void init_matrix(int** mat, int M, int N) {
    for(int i = 0; i < M; i++) {
        for(int j = 0; j < N; j++) {
            mat[i][j] = rand() % 100;
        }
    }
}

void add_matrix1(int** A, int** B, int** C, int M, int N) {
    for(int i = 0; i < M; i++) {
        for(int j = 0; j < N; j++) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
}

void free_matrix(int** mat, int M) {
    for(int i = 0; i < M; i++) {
        free(mat[i]);
    }
    free(mat);
}

int main() {
    int M = 1000;
    int N = 1000;

    int** A = allocate_matrix(M, N);
    int** B = allocate_matrix(M, N);
    int** C = allocate_matrix(M, N);

    init_matrix(A, M, N);
    init_matrix(B, M, N);

    auto start = high_resolution_clock::now(); // Start your Timer

    add_matrix1(A, B, C, M, N);

    auto stop = high_resolution_clock::now(); // End your Timer

    auto duration = duration_cast<microseconds>(stop - start);
    printf("Execution TIME: %.4f seconds\n", (double)(duration.count() / 1000000.0));

    free_matrix(A, M);
    free_matrix(B, M);
    free_matrix(C, M);

    return 0;
}