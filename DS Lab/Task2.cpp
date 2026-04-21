#include <iostream>
#include <mpi.h>
using namespace std;

int main(int argc,char** argv) {
    int size,myrank;
    int n=20;
    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD,&size);
    MPI_Comm_rank(MPI_COMM_WORLD,&myrank);
    printf("Processor %d display: ",myrank);
    for(int j=1;j<=5;j++) {
        printf("%d ",j+5*myrank);
    }
    printf("\n");

    MPI_Finalize();

}