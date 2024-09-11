#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll N = 2e5+5;
vector<ll>adj[N], a(N), d(N,0), sa(N);
ll ans = 0;

void dfs1(int u, int p){ // Precompute ans for root 
    sa[u] = a[u];
    for(int v : adj[u]){
        if(v==p)continue;
        dfs1(v,u);
        d[u] += d[v]+sa[v];
        sa[u] += sa[v];
    }
}

void reroot(int v, int u){ 
    d[u] -= d[v]+sa[v]; // remove v from u 
    sa[u] -= sa[v];
    d[v] += d[u]+sa[u]; // add u to v 
    sa[v] += sa[u];
}

void dfs2(int u, int p){
    ans = max(ans, d[u]);
    for(int v : adj[u]){
        if(v==p)continue;
        reroot(v,u);
        dfs2(v,u);
        reroot(u,v);
    }
}

int main(){
    int n;
    cin >> n;
    for(int i=1; i<=n; i++)cin >> a[i];
    for(int i=0; i<n-1; i++){
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs1(1,0);
    dfs2(1,0);
    cout << ans;
}