#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> pii;

struct node{
    ll l, r; // range
    ll ls, rs; // child 
};

const ll N = 2e5;
vector<node>seg(4*N);
ll cnt = 0; // id of node

void add_edge(ll u, ll v, ll id, ll w){
    if(id)adj[u].push_back({v,w});  // child -> parent
    else adj[v].push_back({u,w}); // parent -> child
}

ll build(ll l, ll r, ll id){
    if(l==r){
        seg[l] = {l,r};
        return l; // leaf only use [1..n]
    }
    ll u = ++cnt;
    ll m = (l+r)/2;
    seg[u] = {l, r, build(l,m,id), biuld(m+1,r,id)};
    add_edge(u, seg[u].ls,id,0);
    add_edge(u, seg[u].rs,id,0);
    return u; // return child idx to parent
}

void add(ll v, ll ql, ll qr, ll w, ll u, ll id){ 
    // 0 : u -> [l,R]
    // 1 : [L,R] -> u
    if(ql > seg[v].r || qr < seg[v].l)return ; // not related
    if(ql <= seg[v].l && seg[v].r <= qr)add_edge(u, v, id, w); // correct range -> add edge
    else{ // go to visit child 
        add(seg[v].ls, ql, qr, w, u, id);
        add(seg[v].rs, ql, qr, w, u, id);
    }
}

int main(){
    ll n, q, s;
    cin >> n >> q >> s;
    cnt = n;
    ll in = build(1,n,1); 
    ll out = build(1,n,0);

    for(ll i=0; i<q; i++){
        ll t, l, r, w, v, u;
        cin >> t;
        if(t == 1){
        cin >> u >> v >> w;
        add_edge(u,v,1,w);
        }else if(t == 2){
        cin >> u >> l >> r >> w;
        add(in,l,r,w,u,1);    
        }else{
        cin >> u >> l >> r >> w;
        add(out,l,r,w,u,0);
        }
    }
}
