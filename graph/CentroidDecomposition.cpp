#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> pii;

const ll N = 2e5+1;

vector<int>sub(N), G[N];
vector<bool>vis(N,0); 
vector<pii>adj[N];

vector<bool>isP(N,1);
vector<int>pri;
vector<int>facts[N];

void init(){
    for(ll i=2; i<N;i++){
        if(isP[i]){
            pri.push_back(i);
            for(ll j=i*i; j<N; j+=i)isP[j] = 0;
        }
    }
    for(int p : pri)for(int i=p; i<N; i+= p)facts[i].push_back(p);
}


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
    if(p!=-1)G[p].push_back(c);
    vis[c] = 1;
    for(auto [v,w] : adj[c]){ // split
        if(vis[v])continue;
        build(v,c); 
    }
    return c;
}

vector<ll>a(N);
vector<bool>vis2(N,0);
ll ans = 0, len2 = 0;

void add(int u, int p, int f, ll dis){
    len2 = max(len2, dis);
    for(auto [v,w] : adj[u]){
        if(vis2[v] || v == p || a[v]%f)continue;
        add(v,u,f,dis+1);
    }
}

bool cmp(pii a, pii b){
    return a.first < b.first;
}

void calc(int u){
    ans = max(ans, (ll)(a[u]!=1));
    for(int f : facts[a[u]]){
        ll len1 = 0;
        for(auto [v,w] : adj[u]){
            if(vis2[v] || a[v]%f)continue;
            len2 = 0;
            add(v,u,f,1);
            ans = max(len1+len2+1, ans);
            len1 = max(len1, len2);
        }
    }
}

void solve(int u){
    vis2[u] = 1;
    calc(u);
    for(auto v : G[u])solve(v);
}

int main(){
    init();
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;

    for(int i=1; i<=n; i++)cin >> a[i];
    for(int i=1; i<n; i++){
        int u, v;
        cin >> u >> v;
        adj[u].push_back({v,1});
        adj[v].push_back({u,1});
    }   
    int rt = build(1,-1);
    solve(rt);
    cout << ans;
}