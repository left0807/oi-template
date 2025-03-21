#include <bits/stdc++.h>
using namespace std;

const int N = 250005;
vector<int>a(N), ans(N), L(N), R(N), qry[N];

struct T1{ // range add/ min
    struct Node{
        int mn, lazy;
    }seg[4*N];

    void clear(int n){
        for(int i=1; i<=4*n; i++)seg[i] = {0,0};
    }


    void merge(int v){
        seg[v].mn = min(seg[v*2].mn, seg[v*2+1].mn);
    }

    void apply(int v, int val){
        seg[v].mn += val;
        seg[v].lazy += val;
    }

    void push(int v, int l, int r){
        if(seg[v].lazy != 0){
            apply(v*2, seg[v].lazy);
            apply(v*2+1, seg[v].lazy);
            seg[v].lazy = 0;
        }
    }

    void build(int v, int l, int r){
        if(l==r){
            seg[v] = {a[l],0};
        }else{
            int m = (l+r)/2;
            build(v*2, l, m);
            build(v*2+1, m+1, r);
            seg[v].lazy = 0;
            merge(v);
        }
    }

    void upd(int v, int l, int r, int ql, int qr, int val){
        if(ql > r || qr < l)return ;
        if(ql <= l && r <= qr){
            apply(v,val);
            return ;
        }
        int m = (l+r)/2;
        push(v,l,r);
        upd(v*2,l,m,ql,qr,val);
        upd(v*2+1,m+1,r,ql,qr,val);
        merge(v);
    }

    int qry(int v, int l, int r, int ql, int qr){
        if(ql > r || qr < l)return 1e9;
        if(ql <= l && r <= qr)return seg[v].mn;
        int m = (l+r)/2;
        push(v,l,r);
        return min(qry(v*2,l,m,ql,qr), qry(v*2+1,m+1,r,ql,qr));
    }
}mnT;

struct T2{ // query max node
    struct Node{
        int id, mx;
        friend Node operator + (Node A, Node B){
            if(A.mx > B.mx)return A;
            else if(A.mx < B.mx)return B;
            else return ((Node){min(A.id, B.id), A.mx});
        }
    }seg[4*N];
    
    void merge(int v){
        seg[v] = seg[v*2]+seg[v*2+1];
    }

    void build(int v, int l, int r){
        if(l==r){
            seg[v] = {l, a[l]};
            return ;
        }
        int m = (l+r)/2;
        build(v*2, l, m);
        build(v*2+1, m+1, r);
        merge(v);
    }

    Node qry(int v, int l, int r, int ql, int qr){
        if(ql > r || qr < l)return {0,(int)-1e9};
        if(ql <= l && r <= qr)return seg[v];
        int m = (l+r)/2;
        return qry(v*2,l,m,ql,qr)+qry(v*2+1,m+1,r,ql,qr);
    }
}mxT;

void f(int n, int q){
    mnT.clear(n);
    for(int i=1; i<=n; i++)qry[i].clear();
    for(int i=1; i<=q; i++)qry[R[i]].push_back(i);
    vector<int>sk(n+1);
    sk[0] = 1;
    int top = 0;
    
    for(int i=1; i<=n; i++){
        while(top && a[i] >= a[sk[top]]){
            mnT.upd(1,1,n,sk[top-1],sk[top]-1,a[i]-a[sk[top]]);
            top--;
        }
        sk[++top] = i;
        if(i>1)mnT.upd(1,1,n,i-1,i-1,a[i-1]+a[i]);
        for(int e : qry[i]){
            auto [id, mx] = mxT.qry(1,1,n,L[e], R[e]);   
            if(id+1<=R[e]-1)ans[e] = min(ans[e], mx+mnT.qry(1,1,n,id+1,R[e]-1));
        }
    }
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n, q;
    cin >> n >> q;

    for(int i=1; i<=n; i++)cin >> a[i];
    for(int i=1; i<=q; i++){
        cin >> L[i] >> R[i];
        ans[i] = 1e9;
    }

    mxT.build(1,1,n);

    // front
    f(n,q);

    // mid
    for(int i=1; i<=q; i++)ans[i] = min(ans[i], a[L[i]]+a[R[i]]+mxT.qry(1,1,n,L[i]+1,R[i]-1).mx);

    // back
    reverse(a.begin()+1,a.begin()+n+1);
    for(int i=1; i<=q; i++){
        int l = L[i], r = R[i];
        L[i] = n-r+1;
        R[i] = n-l+1;
    }
    mxT.build(1,1,n);
    f(n,q);

    for(int i=1; i<=q; i++)cout << ans[i] << "\n";
}