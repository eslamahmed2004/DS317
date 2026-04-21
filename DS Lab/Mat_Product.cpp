#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
using namespace std;

int main() {
    int m=3,n=3;
    ifstream fm("mat.txt");
    ifstream fv("vec.txt");
    int mat[m][n];
    int vec[n];
    int res[m];
    for (int i=0;i<m;i++) {
        res[i]=0;
    }
    for(int i=0;i<m;i++) {
        for(int j=0;j<n;j++) {
            fm >> mat[i][j];
        }
    }
    for(int i=0;i<n;i++) {
        fv >> vec[i];
    }
    fm.close();
    fv.close();
    for(int i=0;i<m;i++) {
        for(int j=0;j<n;j++) {
            res[i]+=mat[i][j]*vec[j];
        }
    }
    ofstream fo("out.txt");
    for(int i=0;i<m;i++) {
        fo << res[i] << endl;
    }
    fo.close();
}


