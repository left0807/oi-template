#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 1e6+5;
ll c[N], cnt[N];
ll sum = 0;
int mxn, qcnt = 0, rcnt = 0;

struct qry{
    ll l, r, t, blk, id;
    inline bool operator<(const qry&b)const{
        if(blk^b.blk)return blk<b.blk;
        if((r/mxn)^(b.r/mxn))return ((blk&1)?r<b.r:r>b.r);
        return t < b.t;
    }
}q[N];

struct upd{
    ll p, x;
}R[N];

void add(int i){
    if(!cnt[i])sum++;
    cnt[i]++;
}

void del(int i){
    cnt[i]--;
    if(!cnt[i])sum--;
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n, m;
    cin >> n >> m;

    memset(cnt,0,sizeof cnt);
    mxn = pow(n, 2.0/3.0);
    for(int i=1; i<=n; i++)cin >> c[i];
    for(int i=0; i<m; i++){
        char op;
        int x, y;
        cin >> op >> x >> y;
        if(op == 'Q'){
            q[qcnt] = {x,y,rcnt,x/mxn,qcnt};
            qcnt++;
        }else{
            rcnt++;
            R[rcnt] = {x,y};
        }
    }
    sort(q,q+qcnt);

    vector<int>ans(qcnt);
    for(int i=0, l=1, r=0,t=0; i<qcnt; i++){
        while(l > q[i].l)add(c[--l]);
        while(r < q[i].r)add(c[++r]);
        while(l < q[i].l)del(c[l++]);
        while(r > q[i].r)del(c[r--]);
        while(t < q[i].t){
            t++;
            if(l <= R[t].p && R[t].p <= r){
                add(R[t].x);
                del(c[R[t].p]);
            }
            swap(c[R[t].p],R[t].x);
        }
        while(t > q[i].t){
            if(l <= R[t].p && R[t].p <= r){
                add(R[t].x);
                del(c[R[t].p]);
            }
            swap(c[R[t].p],R[t].x);
            t--;
        }
        ans[q[i].id] = sum;
    }

    for(auto e : ans)cout << e << "\n";
}

