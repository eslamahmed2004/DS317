#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
#include <mpi.h>
using namespace std;

int main(int argc,char** argv) {
    int size,rank,n,i = 0;
    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD,&size);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);

    if (rank == 0) {
        cin>>n;
    }

    if (rank != 0) {
        i = floor(log2(rank));
        MPI_Recv(&n,1,MPI_INT,rank - pow(2,i),i,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
        i++;
        printf("I am Process %d and my Num is %d \n",rank,n);
    }

    while (i < log2(size)) {
        int dest = rank + pow(2,i);
        if (dest < size) MPI_Send(&n,1,MPI_INT,rank+pow(2,i),i,MPI_COMM_WORLD);
        i++;
    }

    MPI_Finalize();

}
/*
    2^i = size -> i = log2(size)
    R = rank + 2^i
    rank = R - 2^i
    int i = floor(log2(rank))

*/