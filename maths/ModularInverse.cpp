#include <bits/stdc++.h>
#define int long long
using namespace std;

const int MOD = 998244353; // bruh

int pow(int x, int y){
    int res = 1;
    x = x%MOD;
    while(y > 0){
        if(y&1) res = (res*x)%MOD;
        y = y >> 1;
        x = (x*x)%MOD;
    }
    return res;
}

int inv(int x){
    return pow(x, MOD-2);
}

const int N = 1e7+1;
vector<int> fact{1}, invfact{1};

int C(int n, int r){
    if(n < r) return 0;
    for(int i = fact.size(); i <= n; i++){
        fact.push_back(fact.back() * i % MOD);
        invfact.push_back(inv(fact.back()));
    }
    return ((fact[n]*invfact[r])%MOD*invfact[n-r])%MOD;
}

void precompute(){
    fact.resize(N);
    invfact.resize(N);
    fact[0] = invfact[0] = 1;
    for(int i = 1; i<N; i++)fact[i] = (fact[i-1]*i)%MOD;
    invfact[N-1] = inv(fact[N-1]);
    for(int i=N-2; i>=1; i--)invfact[i] = invfact[i+1]*(i+1)%MOD;
    
}
