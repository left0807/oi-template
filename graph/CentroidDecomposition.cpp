#include <bits/stdc++.h>
using namespace std;

const int N = 1e6+1;
set<int>adj[N];
vector<int>sub(N), fa(N);

int dfs(int u, int p){
    sub[u] = 1;
    for(int v : adj[u]){
        if(v==p)continue;
        sub[u] += dfs(v,u);
    }
    return sub[u];
}

int centroid(int u, int p, int sz){
    for(int v : adj[u]){
        if(v==p)continue;
        if(sub[v] > sz/2)return centroid(v,u,sz);
    }
    return u;
}

void build(int u, int p){
    int sz = dfs(u, p); // size of subtree
    int c = centroid(u,p,sz); // centroid of subtree
    if(p==-1) p = c;
    fa[c] = p; // root of centroid

    for(int v : adj[c]){ // split
        adj[c].erase(v); 
        adj[v].erase(c);
        build(v,c); 
    }
}

int main(){
    int n;
    cin >> n;

    for(int i=0; i<n-1; i++){
        int u, v;
        cin >> u >> v;
        adj[u].insert(v);
        adj[v].insert(u);
    }

    build(1,-1);
}