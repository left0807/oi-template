#include <bits/stdc++.h>
using namespace std;

#define int long long 
const int MOD = 998244353;
const int N = 1e5+1;

vector<int> precompute_phi(int n){
    vector<int>phi(n+1);
    iota(phi.begin(), phi.end(), 0);
    for(int i=2; i<=n; i++){
        if(phi[i] == i){
            for(int j=i; j<=n; j+=i){
                phi[j] -= phi[j]/i;
            }
        }
    }
    return phi;
}



int32_t main(){
    int n;
    cin >> n;

    vector<int>fact[N];
    for(int i=1; i<N; i++)for(int j=i; j<N; j+=i)fact[j].push_back(i);
    
    vector<int>a(n+1), phi = precompute_phi(N), g(N,0);
    for(int i=1; i<=n; i++)cin >> a[i];

    vector<int>po2(n+1,1);
    for(int i=1; i<=n; i++)po2[i] = (po2[i-1]*2)%MOD;

    int ans = 0;
    for(int i=1; i<=n; i++){
        ans = (ans*2)%MOD;
        for(auto d : fact[a[i]])ans = (ans+phi[d]*g[d])%MOD;
        for(auto d : fact[a[i]])g[d] = (g[d] + po2[i-1])%MOD;
        cout << ans << "\n";
    }
}