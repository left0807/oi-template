#include <bits/stdc++.h>
using namespace std;

// abc289 G

typedef long long ll;

struct LCT{
    static const int N = 2e5+5, M = N*30, inf = 1e9;
    int rt = 1;
    struct line{ 
        ll k, b;
        line (ll kk=0, ll bb=0){
            k = kk, b = bb;
        }
        ll f(ll x){
            return x*k+b;
        }
    };

    ll inter(line aa, line bb){ // x-coor of intersection of 2 line
        return (bb.b-aa.b)/(aa.k-bb.k);
    }

    int tot = 0, ch[M][2];
    line seg[M];

    void add(int &v, int l, int r, line now){
        if(!v){
            v = ++tot;
            seg[v] = now;
            return ;
        }
        int m = (l+r)/2;
        ll la = seg[v].f(l), ra = seg[v].f(r), lb = now.f(l), rb = now.f(r);
        if(la <= lb && ra <= rb)return ;
        if(la >= lb && ra >= rb){
            seg[v] = now;
            return ;
        }

        ll it = inter(seg[v], now);
        if(la <= lb){
            if(it <= m){
                add(ch[v][0], l, m, seg[v]); // push old line as new line is stored
                seg[v] = now;
            }else add(ch[v][1], m+1, r, now);
        }else{
            if(it <= m)add(ch[v][0], l, m, now);
            else{
                add(ch[v][1], m+1, r, seg[v]);
                seg[v] = now;
            }
        }
    }    

    ll qry(int v, int l, int r, int x){
        if(!v)return (ll)inf*inf;
        int m = (l+r)/2;
        if(x <= m)return min(seg[v].f(x), qry(ch[v][0], l, m, x));
        else return min(seg[v].f(x), qry(ch[v][1],m+1,r,x));
    }
}lc;

int rt;

int main(){
    int n, m;
    cin >> n >> m;

    vector<ll>b(n), c(m);
    for(auto &e : b)cin >> e;
    for(auto &e : c)cin >> e;
    sort(b.begin(), b.end(), greater<ll>());
    for(int i=0; i<n; i++)lc.add(rt, 0, lc.inf, {-(i+1), -((i+1)*b[i])});
    for(int i=0; i<m; i++)cout << -lc.qry(rt, 0, lc.inf, c[i]) << " ";
}