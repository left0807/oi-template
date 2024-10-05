#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll MOD = 998244353; // bruh

ll pow(ll x, ll y){
    ll res = 1;
    x = x%MOD;
    while(y > 0){
        if(y&1) res = (res*x)%MOD;
        y = y >> 1;
        x = (x*x)%MOD;
    }
    return res;
}

ll inv(ll x){
    return pow(x, MOD-2);
}

const int N = 1e7+1;
vector<ll> fact(N), invfact(N);

ll C(ll n, ll r){
    if(n < r) return 0;
    return ((fact[n]*invfact[r])%MOD*invfact[n-r])%MOD;
}

void precompute(){
    fact[0] = invfact[0] = 1;
    for(ll i = 1; i<N; i++)fact[i] = (fact[i-1]*i)%MOD;
    invfact[N-1] = inv(fact[N-1]);
    for(ll i=N-2; i>=1; i--)invfact[i] = invfact[i+1]*(i+1)%MOD;
    
}
