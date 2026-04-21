#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
#include <mpi.h>
using namespace std;

int main(int argc,char** argv) {
    int size,rank;
    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD,&size);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    const int n = 12;
    int a[n+1]{},b[n+1]{};
    for (int i = 1; i <= n; ++i) {
        a[i] = i;
        b[i] = i;
    }
    int m = n/size,sum = 0;
    if (rank == size - 1) {
        int l = rank * m + 1, h= n;
        for (int i = l; i <= h; ++i) {
            sum += a[i] * b[i];
        }
    }
    else {
        int l = rank * m + 1, h= (rank + 1) * m;
        for (int i = l; i <= h; ++i) {
            sum += a[i] * b[i];
        }
    }
    cout << "My rank is: "<<rank<<" and sum is: "<<sum<<endl;



    MPI_Finalize();

}