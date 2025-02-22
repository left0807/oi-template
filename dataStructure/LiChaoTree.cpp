#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

struct lctree{
    const double EPS = 1e-8;
    static const int N = 1e5+10; // no.of line
    int tot = 0;
    int rt = 0;
    int cnt = 0;
    int L = 0, R = 4e4+5; // bound of x 

    struct line{    
        double a, b;
    }li[N];

    struct node{
        int l, r;
        int id;
    }seg[N<<6];

    double f(int id, int x){
        return li[id].a*x + li[id].b;
    }

    bool fcmp(double a){
        return fabs(a) <= EPS ? 0 : a < 0 ? -1 : 1;
    }

    bool cmp(int id1, int id2, int x){ // 1 = id2 better (larger x/smaller id) 
        double f1 = f(id1,x), f2 = f(id2,x);
        return fcmp(f1-f2) ? f1 < f2 : id1 > id2;
    }

    void add(int &v, int l, int r, int ql, int qr, int id){
        if(!v)v = ++tot;
        if(ql <= l && r <= qr){
            if(cmp(id, seg[v].id, l) && cmp(id, seg[v].id, r))return ;
            if(cmp(seg[v].id, id, l) && cmp(seg[v].id, id, r)){
                seg[v].id = id;
                return ;
            }
            int m = (l+r)/2;
            if(cmp(seg[v].id, id, m))swap(seg[v].id, id);
            if(cmp(seg[v].id, id, l))add(seg[v].l, l, m, ql, qr, id);
            if(cmp(seg[v].id, id, r))add(seg[v].r, m+1, r, ql, qr, id);
        }else{
            int m = (l+r)/2;
            if(ql<=m)add(seg[v].l, l, m, ql, qr, id);
            if(qr>m)add(seg[v].r, m+1, r, ql, qr, id);
        }
    }

    int qry(int v, int l, int r, int x){
        if(l == x && x == r)return seg[v].id;
        else{
            int m = (l+r)/2;
            int res = (x<=m) ? qry(seg[v].l, l, m, x) : qry(seg[v].r, m+1, r, x);
            if(cmp(res, seg[v].id, x))res = seg[v].id;
            return res;
        }
    }

    void ins1(int a, int b, int id){ // insert line based on slope
        li[id] = {a,b};
        add(rt, L, R, L, R, id);
    }

    void ins2(int x0, int y0, int x1, int y1, int id){ // insert line based on 2 coor
        if(x0 > x1)swap(x0,x1), swap(y0, y1);
        if(x0 != x1){
            double s = (double)(y1-y0)/(x1-x0);
            li[id] = {s, y1-s*x1};
        }else li[id] = {0, max(y0,y1)};
        add(rt, L, R, x0, x1, id);
    }
}lc;

const int M = 39989;
const int M2 = 1e9;

int main(){
    int n;
    cin >> n;

    int lst = 0;

    auto f = [&](int v, int m){
        return (v+lst-1)%m+1;
    };

    while(n--){
        int op;
        cin >> op;

        if(!op){
            int k;
            cin >> k;
            k = f(k, M);    
            lst = lc.qry(lc.rt, lc.L, lc.R, k);
            cout << lst << "\n";
        }else{
            int x0, x1, y0, y1;
            cin >> x0 >> y0 >> x1 >> y1;
            x0 = f(x0, M), x1 = f(x1, M), y0 = f(y0, M2), y1 = f(y1, M2);
            lc.cnt++;
            lc.ins2(x0,y0,x1,y1,lc.cnt);
        }
    }
}