#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> pii;

const ll N = 100001;
const ll LG = 23;
vector<int>sub(N), G[N], fa(N);
vector<bool>vis(N,0); 
vector<pii>adj[N];

// lazy tag pq 
struct que{
    priority_queue<int>x, y;
    inline void push(int a){x.push(a);}
    inline void del(int a){y.push(a);}
    inline int size(){return x.size()-y.size();}
    inline void pop(){
        while(y.size()&&x.top()==y.top())x.pop(),y.pop();
        x.pop();
    }
    inline int top(){
        while(y.size()&&x.top()==y.top())x.pop(),y.pop();
        return x.top();
    }
    inline int top2(){
        int a = top();
        pop();
        int b = top();
        push(a);
        return b;
    }
}A, B[N], C[N];

void pusha(int x){
    if(B[x].size() >= 2)A.push(B[x].top()+B[x].top2());
}

void dela(int x){
    if(B[x].size() >= 2)A.del(B[x].top()+B[x].top2());
}

// Build centroid decomposition tree
ll dfs(ll u, ll p){
    sub[u] = 1;
    for(auto [v,w] : adj[u]){
        if(v==p || vis[v])continue;
        sub[u] += dfs(v,u);
    }
    return sub[u];
}

ll centroid(ll u, ll p, ll sz){
    for(auto [v,w] : adj[u]){
        if(v==p || vis[v])continue;
        if(sub[v] > sz/2)return centroid(v,u,sz);
    }
    return u;
}

ll build(ll u, ll p){
    ll sz = dfs(u, p); // size of subtree
    ll c = centroid(u,p,sz); // centroid of subtree
    if(p)G[p].push_back(c);
    fa[c] = p;
    vis[c] = 1;
    for(auto [v,w] : adj[c]){ // split
        if(vis[v])continue;
        build(v,c); 
    }
    return c;
}

// LCA
int anc[N][LG], dep[N];
void precompute(int u, int p){
    anc[u][0] = p;
    dep[u] = dep[p]+1;
    for(int i=1; i<LG; i++)anc[u][i] = anc[anc[u][i-1]][i-1];
    for(auto [v,w] : adj[u]){
        if(v==p)continue;
        precompute(v,u);
    }
}

int lca(int u, int v){
    if(dep[u] < dep[v])swap(u,v);
    for(int i=LG-1; i>=0; i--)if(dep[anc[u][i]] >= dep[v])u = anc[u][i];
    if(u==v)return u;
    for(int i=LG-1; i>=0; i--){
        if(anc[u][i] != anc[v][i]){
            u = anc[u][i];
            v = anc[v][i]; 
        }
    }
    return anc[u][0];
}

int dis(int u, int v){
    int w = lca(u,v);
    return dep[u]+dep[v]-2*dep[w];
}

// Centroid decomposition
vector<bool>vis2(N,0);

void add(int u, int p,int rt){
    C[rt].push(dis(u,fa[rt]));
    for(auto [v,w] : adj[u]){
        if(vis2[v] || v == p)continue;
        add(v,u,rt);
    }
}


void solve(int u){
    vis2[u] = 1;
    B[u].push(0);
    add(u,fa[u],u);
    for(auto v : G[u]){
        solve(v);
        B[u].push(C[v].top());
    }
    pusha(u);
}


// Update
vector<bool>light(N,0);

void on(int x){
    dela(x);
    B[x].del(0);
    pusha(x);
    int v = x;
    while(fa[v]){
        dela(fa[v]);
        if(C[v].size())B[fa[v]].del(C[v].top()); 
        C[v].del(dis(x,fa[v]));
        if(C[v].size())B[fa[v]].push(C[v].top());
        pusha(fa[v]);
        v = fa[v];
    }
}

void off(int x){
    dela(x);
    B[x].push(0);
    pusha(x);
    int v = x;
    while(fa[v]){
        dela(fa[v]);
        if(C[v].size())B[fa[v]].del(C[v].top()); 
        C[v].push(dis(x,fa[v]));
        B[fa[v]].push(C[v].top());
        pusha(fa[v]);
        v = fa[v];
    }
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;

    for(int i=1; i<n; i++){
        int u, v;
        cin >> u >> v;
        adj[u].push_back({v,1});
        adj[v].push_back({u,1});
    }
    precompute(1,0);
    int rt = build(1,0);
    solve(rt);

    int m;
    cin >> m;
    int tot = n;
    for(int i=1; i<=m; i++){
        char c;
        int x;
        cin >> c;
        if(c=='C'){
            cin >> x;
            if(light[x]){
                tot++;
                off(x);
            }else{
                tot--;
                on(x);
            }
            light[x] = !light[x];
        }else{
            if(tot==0)cout << "-1\n";
            else if(tot==1)cout << "0\n";
            else cout << A.top() << "\n";
        }
    }
}