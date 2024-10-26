#include <bits/stdc++.h>
using namespace std;

#pragma comment(linker, "/stack:200000000")
#pragma GCC optimize("Ofast,no-stack-protector")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma G++ optimize(2)
#pragma G++ optimize(3)

typedef long long ll;
typedef tuple<int,int,int> tii;

const int N = 5e4+10;
const ll M = 1e9+7;
vector<int>a(N), ans(N);
vector<tii>upd(N), qry1[N], qry2[N];

inline int Mod(ll x, ll y){return (x+y) > M ? x+y-M : x+y;} // why negative : (

struct mat{ // matrix 
    int a[4][4];
    mat(){memset(a,0,sizeof a);}
    inline void reset(){
        memset(a,0, sizeof a);
        for(int i=0; i<=3; i++)a[i][i] = 1;
    }
    inline mat operator*(const mat &rhs)const{ // multiply
        mat r;
        for(int k=0; k<=3; k++){
            for(int i=0; i<=3; i++){
                for(int j=0; j<=3; j++){
                    r.a[i][j] = Mod(r.a[i][j],(1ll*a[i][k]*rhs.a[k][j])%M);
                }
            }
        }
        return r;
    }
    inline mat operator+(const mat &rhs)const{ // addition
        mat r;
        for(int i=0; i<=3; i++){
            for(int j=0; j<=3; j++){
                r.a[i][j] = Mod(a[i][j] , rhs.a[i][j]);
            }
        }
        return r;
    }
};

struct Node{
    mat x, lazy;
};

vector<Node>seg(4*N);

void merge(int v){
    seg[v].x = seg[v*2].x+seg[v*2+1].x;
}

void apply(int v, mat &k){
    seg[v].x = seg[v].x*k;
    seg[v].lazy = seg[v].lazy*k;
}

void push(int v){
    apply(v*2, seg[v].lazy);
    apply(v*2+1, seg[v].lazy);
    seg[v].lazy.reset();
}

void build(int v, int l, int r){
    seg[v].lazy.reset();
    if(l==r){
        seg[v].x.a[0][0] = Mod(a[l],M); // range sum
        seg[v].x.a[0][1] = (1LL*a[l]*a[l])%M; // range square sum
        seg[v].x.a[0][2] = 1; // range len
        return ;
    }
    int m = (l+r)/2;
    build(v*2,l,m);
    build(v*2+1,m+1,r);
    merge(v);
}

void update(int v, int l, int r, int ql, int qr, mat k){
    if(ql > r || qr < l)return ;
    if(ql <= l && r <= qr){
        apply(v, k);
        return ;
    }
    push(v);
    int m = (l+r)/2;
    update(v*2, l, m, ql, qr, k);
    update(v*2+1, m+1, r, ql, qr, k);
    merge(v);
}

int query(int v, int l, int r, int ql, int qr){
    if(ql > r || qr < l)return 0;
    if(ql <= l && r <= qr)return seg[v].x.a[0][3]; // history square sum 
    push(v);
    int m = (l+r)/2;
    return Mod(query(v*2,l,m,ql,qr) , query(v*2+1,m+1,r,ql,qr));
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n, m, q;
    cin >> n >> m >> q;
    m++;
    for(int i=1; i<=n; i++)cin >> a[i];
    for(int i=2; i<=m; i++){
        int l, r, x;
        cin >> l >> r >> x;
        upd[i] = {l,r,x};
    }
    for(int i=1; i<=q; i++){
        int l, r, x, y;
        cin >> l >> r >> x >> y;
        qry1[x].push_back({l,r,i});
        qry2[y+1].push_back({l,r,i});
    }
    build(1,1,n);
    upd[1] = {1,1,0};
    mat tmp;
    for(int i=1; i<=m; i++){
        tmp.reset();
        auto [l,r,x] = upd[i];
        tmp.a[0][0] = 1;
        tmp.a[0][1] = Mod((2LL*x)%M,M);
        tmp.a[1][1] = 1;
        tmp.a[2][0] = Mod(x,M);
        tmp.a[2][1] = (1LL*x*x)%M;
        tmp.a[2][2] = 1;
        tmp.a[3][3] = 1;
        update(1,1,n,l,r,tmp); // update range 
        tmp.reset();
        tmp.a[1][3] = 1;
        apply(1,tmp); // update everything 
        for(auto [l,r,j] : qry1[i])ans[j] = Mod(ans[j],Mod(M,-query(1,1,n,l,r)));
        for(auto [l,r,j] : qry2[i])ans[j] = Mod(ans[j],Mod(M,query(1,1,n,l,r)));
    }   
    for(int i=1; i<=q; i++)cout << ans[i] << "\n";
}
