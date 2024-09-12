#include <bits/stdc++.h>
using namespace std;

int main(){
    int n;
    cin >> n;

    vector<int>a(1<<n);
    for(int i=0; i<(1<<n); i++)cin >> a[i];

    for(int i=0; i<n; i++){ // dimension 
        for(int j=0; j<(1<<n); j++){ // mask 
            if(j&(1<<i))f[j] += f[j^(1<<i)];
        }
    }
}

/*
Find subset sum
1100101 <- 1000101
 -          -
*/