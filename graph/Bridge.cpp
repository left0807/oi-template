#include <bits/stdc++.h>
using namespace std;

typedef pair<int,int> pii;
const int N = 2e5+10;
vector<int>adj[N], st(N), low(N);
vector<pii>bridge;
int tin = 0;

void dfs(int u, int p){
    st[u] = low[u] = ++tin; // init 

    for(int v: adj[u]){
        if(!st[v]){ // not visit -> (u-v) tree edge 
            dfs(v,u);
            low[u] = min(low[u], low[v]); 
            if(low[v] > st[u]){ // not passing though
                bridge.emplace_back(u,v);
            }
        }else if(v != p){ 
            low[u] = min(low[u], st[v]); // only 1 back edge 
        }
    }
}