#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
#include <mpi.h>
using namespace std;

int main(int argc,char** argv) {
    int size,rank;
    long long Total_tosses;
    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD,&size);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    if (rank==0) cin>>Total_tosses;
    MPI_Bcast(&Total_tosses, 1, MPI_LONG_LONG, 0, MPI_COMM_WORLD);
    if (Total_tosses <= 0) {
        if (rank == 0) cout << "Number of tosses must be greater than 0!" << endl;
        MPI_Finalize();
        return 0;
    }
    int chunk = Total_tosses/size , local_tosses = 0,end = chunk;
    if (rank == size - 1) end = chunk+(Total_tosses%size);
    srand(time(NULL) + rank);
    double x,y;
    for (int i=0;i<end;i++) {
         x = ((double)rand() / RAND_MAX) * 2.0 - 1.0;
         y = ((double)rand() / RAND_MAX) * 2.0 - 1.0;
        if (x*x+y*y<=1) local_tosses++;
    }
    printf("I am Process %d and My local tosses is %d\n",rank,local_tosses);
    int in_circle;
    MPI_Reduce(&local_tosses, &in_circle, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    if (rank==0) {
        double PI = 4.0 * (double)in_circle / (double)Total_tosses;
        printf("PI is %f\n",PI);
    }
    MPI_Finalize();

}