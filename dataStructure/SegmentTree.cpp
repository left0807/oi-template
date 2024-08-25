#include <bits/stdc++.h>
using namespace std;

const int N = 2e5+5;

struct Node{ // value stored in each node 
    int cnt, mn, lazy;
};

vector<Node>seg(4*N);

void merge(int v){ // combine 2 child 
    int c1 = seg[v*2].cnt, c2 = seg[v*2+1].cnt;
    int m1 = seg[v*2].mn, m2 = seg[v*2+1].mn;
    if(m1==m2)seg[v].cnt = c1+c2, seg[v].mn = m1;
    else if(m1 < m2)seg[v].cnt = c1, seg[v].mn = m1;
    else seg[v].cnt = c2, seg[v].mn = m2;
}

void apply(int v, int val){ // update value 
    seg[v].mn += val;
    seg[v].lazy += val;
}

void push(int v, int l, int r){ // lazy propagation update child 
    if(seg[v].lazy!=0){
        int m = (l+r)/2;
        apply(v*2, seg[v].lazy);
        apply(v*2+1, seg[v].lazy);
        seg[v].lazy = 0;
    }
}

void build(int v, int l, int r){ // Initialize tree 
    if(l==r){
        seg[v] = {1,0,0};
    }else{
        int m = (l+r)/2;
        build(v*2, l, m);
        build(v*2+1, m+1, r);
        seg[v].lazy = 0;
        merge(v);
    }
}

void update(int v, int l, int r, int ql, int qr, int val){ // Update range
    if(ql > r || qr < l)return ;
    if(ql <= l && r <= qr){
        apply(v,val);
        return ;
    }
    push(v,l,r);
    int m = (l+r)/2;
    update(v*2,l,m,ql,qr,val);
    update(v*2+1,m+1,r,ql,qr,val);
    merge(v);
}

void add(int a, int b, int n, int val){  
    if(a!=1)update(1,1,n,1,a-1, val); // 1->a 
    update(1,1,n,b,n,val); // b->n
    update(1,1,n,a,b-1,-val); // a->b
}

void solve(){
    int n, m, a, b;
    cin >> n >> m;
    build(1,1,n);
    vector<int>st[n+1], ed[n+1];
    for(int i=0; i<m; i++){
        cin >> a >> b;
        st[a].push_back(b);
        ed[b].push_back(a);
        update(1,1,n,a,b-1,1);
    }
    int mn = n;
    for(int i=1; i<=n; i++){
        for(int b : st[i])add(i,b,n,1);
        for(int a : ed[i])add(a,i,n,-1);
        if(seg[1].mn == 0)mn = min(mn, n-seg[1].cnt);
    }
    cout << mn << "\n";
}

int main(){
    int t;
    cin >> t;
    while(t--)solve();
}