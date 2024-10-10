#include <bits/stdc++.h>
using namespace std;

const int N = 300001;
vector<int>adj[N], ans(N), p(N), sz(N), w(N);

void dfs(int u){
    sz[u] = 1;
    ans[u] = u;
    for(int v : adj[u]){
        dfs(v);
        sz[u] += sz[v]; // subtree u size 
        w[u] = max(w[u], w[v]); // max child subtree 
    }

    for(int v : adj[u]){
        int x = ans[v];
        while(x != u){
            /*
                Tree = subtree of u 
                total size = sz[u]
                max subtree size at x = max(w[x], sz[u]-sz[x])    
            */
            if(max(w[x], sz[u]-sz[x]) <= sz[u]/2){
                ans[u] = x;
                break;
            }else x = p[x];
        }
    }
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n, q;
    cin >> n >> q;

    for(int i=2; i<=n; i++){
        cin >> p[i];
        adj[p[i]].push_back(i);
    }

    dfs(1);
    while(q--){
        int u;
        cin >> u;
        cout << ans[u] << "\n";
    }
}

// finding centroid for every subtree
