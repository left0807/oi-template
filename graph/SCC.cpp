#include <bits/stdc++.h>
using namespace std;

const int N = 2e5+5;
vector<bool>ins(N,0);
vector<int>adj[N], st(N), low(N), scc(N), s;
int tin = 0, k = 0;

void dfs(int u){
    st[u] = low[u] = ++tin;
    s.emplace_back(u); // store descendent 
    ins[u] = 1;

    for(int v : adj[u]){
        if(!st[v]){
            dfs(v);
            low[u] = min(low[u], low[v]);
        }else if(ins[v]){ // back / forward edge
            low[u] = min(low[u], st[v]);
        }
    }
    if(st[u]==low[u]){
        ++k;
        for(int x=-1; x!=u; s.pop_back()){
            x = s.back();
            scc[x] = k;
            ins[x] = 0;
        }
    }
}