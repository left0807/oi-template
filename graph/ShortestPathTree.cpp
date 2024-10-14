#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> pii;

const int N = 2e5+10;
vector<pii>adj[N];

struct edge{
    int u, v, w;
};
vector<edge>E(2*N);

vector<ll>dij1(int s, int n){
    vector<bool>vis(n+1,0);
    vector<ll>d(n+1,1e18);
    d[s] = 0;
    priority_queue<pii, vector<pii>, greater<pii>>pq;
    pq.push({d[s],s});
    while(!pq.empty()){
        int u = pq.top().second;
        pq.pop();
        if(vis[u])continue;
        vis[u] = 1;
        for(auto [v,i] : adj[u]){
            ll w = E[i].w;
            if(d[v] > d[u]+w){
                d[v] = d[u]+w;
                pq.push({d[v],v});
            }
        }
    }
    return d;
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n, m;
    cin >> n >> m;

    for(int i=1; i<=m; i++){
        cin >> E[i].u >> E[i].v >> E[i].w;
        adj[E[i].u].push_back({E[i].v, i});
        adj[E[i].v].push_back({E[i].u, i});
    }

    vector<ll>d1 = dij1(1,n), d2 = dij1(n,n);
    vector<int>l(n+1,1e9), r(n+1,0);
    vector<bool>used(m+1,0);

    // l[i] = first edge not in 1->i
    // r[i] = last edge not in i->n
    l[1] = 1; 
    int tot = 0;
    vector<int>E2(m+1,0);
    for(int u=1; u!=n;){    
        for(auto [v,i] : adj[u]){
            ll w = E[i].w;
            if(d2[v]+w == d2[u]){
                E2[tot+1] = i;
                u = v;
                used[i] = 1;
                break;
            }
        }
        r[u] = ++tot;
        l[u] = tot+1;
    }

    vector<int>ord(n);
    iota(ord.begin(), ord.end(),1);

    sort(ord.begin(), ord.end(), [&](int x, int y){
        return d1[x] < d1[y];
    });
    for(int u : ord){
        for(auto [v,i] : adj[u]){
            if(used[i])continue;
            ll w = E[i].w;
            if(d1[v]==d1[u]+w)l[v] = min(l[v],l[u]);
        }
    }

    sort(ord.begin(), ord.end(), [&](int x, int y){
        return d2[x] < d2[y];
    });
    for(int u : ord){
        for(auto [v,i] : adj[u]){
            if(used[i])continue;
            ll w = E[i].w;
            if(d2[v] == d2[u]+w)r[v] = max(r[v],r[u]);
        }
    }

    vector<ll>p1[tot+1], p2[tot+1];
    for(int i=1; i<=m; i++){
        if(used[i])continue;
        auto [u,v,w] = E[i];
        if(l[u] <= r[v]){
            p1[l[u]].push_back(d1[u]+d2[v]+w);
            p2[r[v]].push_back(d1[u]+d2[v]+w);
        }
        if(l[v] <= r[u]){
            p1[l[v]].push_back(d1[v]+d2[u]+w);
            p2[r[u]].push_back(d1[v]+d2[u]+w);
        }
    }

    multiset<ll>s;
    for(int i=1; i<=tot; i++){
        for(ll w : p1[i])s.insert(w);
        if(*s.begin() == d1[n])used[E2[i]] = 0;
        for(ll w : p2[i])s.erase(s.find(w));
    }

    for(int i=1; i<=m; i++){
        if(used[i])cout << "Yes\n";
        else cout << "No\n";
    }

    // if(ans == d1[n])cnt = m;
    // cout << ans << " " << cnt;
}

/*
1. dijkstra shortest path
2. Build shortest path tree
3. Check each shortest path edge when removed have what answer 
4. Observe that new path = 1 -> l[u] -> (u,v) -> r[v] -> n
5. (u,v) will be used only if removed edge [l[u],r[v]]
6. use multiset to maintain ans when edge i is removed 
*/