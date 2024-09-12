#include <bits/stdc++.h>
using namespace std;

const int N = 1e5+5;
vector<int>adj[N];
int f[N][3];

void dfs0(int u, int p){ // compute 2 largest child 
    for(int v : adj[u]){
        if(v==p)continue;
        dfs0(v,u);
        if(f[v][0] >= 0){
            if(f[v][0]+1 >= f[u][0]){
                f[u][1] = f[u][0];
                f[u][0] = f[v][0]+1;
            }else if(f[v][0]+1 > f[u][1]){
                f[u][1] = f[v][0]+1;
            }
        }
    }
}

void dfs1(int u, int p){ // find largest ancestor 
    for(int v : adj[u]){
        if(v==p)continue;
        int t = 0;
        if(f[u][0] == f[v][0]+1)t = max(f[u][1], f[u][2]); // can't use largest 
        else t = max(f[u][0], f[u][2]);
        if(t>=0)f[v][2] = t+1;
        dfs1(v,u);
    }
}

int main(){
    memset(f, -1, sizeof f);

    int n, m, d;
    cin >> n >> m >> d;

    for(int i=0; i<m; i++){
        int v;
        cin >> v;
        f[v][0] = f[v][2] = 0;
    }

    for(int i=0; i<n-1; i++){
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs0(1,0);
    dfs1(1,0);
    int cnt = 0;
    for(int i=1; i<=n; i++)cnt += (max(f[i][0],f[i][2]) <= d);
    cout << cnt;
}