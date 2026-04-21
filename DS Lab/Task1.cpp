#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
#include <mpi.h>
using namespace std;

int main(int argc,char** argv) {
    int size,myrank;
    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD,&size);
    MPI_Comm_rank(MPI_COMM_WORLD,&myrank);
    if(myrank==0) {
        printf("Master Node and myRank is %d\n",myrank);
    }
    else if(myrank%2==0) {
        printf("Even Node and myRank is %d\n",myrank);
    }
    else {
        printf("Odd Node and myRank is %d\n",myrank);
    }
    MPI_Finalize();

}