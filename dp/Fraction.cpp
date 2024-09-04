#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main(){
    ll n, k;
    cin >> n >> k;

    vector<ll>a(n+1), b(n+1);
    for(ll i=1; i<=n; i++)cin >> a[i];
    for(ll i=1; i<=n; i++)cin >> b[i];

    ll dp[n+1][20100];
    ll off = 10000;
    for(ll i=0; i<=n; i++)for(ll j=0; j<20100; j++)dp[i][j] = -1e9;
    dp[0][off] = 0;
    for(ll i=1; i<=n; i++){
        ll w = a[i]-k*b[i];
        for(ll j=0; j<20100; j++){ // from j -> ? 
            if(dp[i-1][j] < 0)continue;
            dp[i][j] = max(dp[i][j], dp[i-1][j]);
            ll t = j+w;
            if(t < 0 || t > 20100)continue;
            dp[i][t] = max(dp[i][t],dp[i-1][j]+a[i]);
        }
    }

    if(dp[n][off])cout << dp[n][off];
    else cout << -1;
}

/*
sum(a)/sum(b) = k , find maximum sum(a)
-> sum(a) = sum(b)*k

dp[i][j] = use i element, diff between sum(a)-sum(b)*k = j 
ans : dp[n][0]

* maybe -ve, require shifting
*/