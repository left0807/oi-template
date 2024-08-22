#include <bits/stdc++.h>
using namespace std;

typedef pair<int,int> pii;
const int N = 2e5+10;
vector<int>adj[N], st(N), low(N);
vector<bool>ap(N);
int tin = 0;

void dfs(int u, int p){
    st[u] = low[u] = ++tin; // init 
    int cnt = 0;
    for(int v: adj[u]){
        if(!st[v]){ // not visit -> (u-v) tree edge 
            dfs(v,u);
            cnt++;
            low[u] = min(low[u], low[v]); 
            if(low[v] >= st[u] && p!=0){ // not passing though + not root 
                ap[u] = 1;
            }
        }else if(v != p){ 
            low[u] = min(low[u], st[v]); // only 1 back edge 
        }
    }
    if(p==0 && cnt > 1)ap[u] = 1; // root has more than 1 child 
}

/*
Def : vertex which del will increase component

no back edge passing over node u 
-> even reach u still split when del
*/