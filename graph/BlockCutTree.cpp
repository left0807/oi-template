#include <bits/stdc++.h>
using namespace std;

typedef pair<int,int> pii;
const int N = 2e5+10;
const int M = 1e5;
vector<int>adj[N], st(N), low(N), s, adj2[N];
int tin = 0, k = M-1;

void dfs(int u, int p){
    st[u] = low[u] = ++tin; // init 
    s.emplace_back(s);

    for(int v: adj[u]){
        if(!st[v]){ // not visit -> (u-v) tree edge 
            dfs(v,u);
            low[u] = min(low[u], low[v]); 
            if(st[u]==low[v]){ // ecc vertex are descendent 
                ++k;
                for(int x = -1; x!=v; s.pop_back()){
                    x = s.back();
                    adj2[x].push_back(k);
                    adj2[k].push_back(x);
                }
                adj2[u].push_back(k);
                adj2[k].push_back(u);
            }
        }
        low[u] = min(low[u], st[v]); // only 1 back edge 
    }
}

/*
Create new node to connect same bcc (biconnected)
-> shrink it as a tree 
*/