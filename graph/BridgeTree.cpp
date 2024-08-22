#include <bits/stdc++.h>
using namespace std;

typedef pair<int,int> pii;
const int N = 2e5+10;
vector<int>adj[N], st(N), low(N), ecc(N), s;
int tin = 0, k = 0;

void dfs(int u, int p){
    st[u] = low[u] = ++tin; // init 
    s.emplace_back(s);

    for(int v: adj[u]){
        if(!st[v]){ // not visit -> (u-v) tree edge 
            dfs(v,u);
            low[u] = min(low[u], low[v]); 
        }else if(v != p){ 
            low[u] = min(low[u], st[v]); // only 1 back edge 
        }
    }

    if(st[u]==low[u]){ // ecc vertex are descendent 
        ++k;
        for(int x = -1; x!=u; s.pop_back()){
            x = s.back();
            ecc[x] = k;
        }
    }
}