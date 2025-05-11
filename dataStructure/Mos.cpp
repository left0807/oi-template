#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll,ll> pii;
const int N = 50005;
int c[N], cnt[N];
ll sum = 0;

struct qry{
    ll l, r, blk, id;
    inline bool operator<(const qry&b)const{
        return (blk^b.blk)?blk<b.blk:((blk&1)?r<b.r:r>b.r);
    }
}q[N];

void add(int i){
    sum += cnt[c[i]];
    cnt[c[i]]++;
}

void del(int i){
    cnt[c[i]]--;
    sum -= cnt[c[i]];
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n, m;
    cin >> n >> m;

    int mxn = sqrt(n);
    for(int i=1; i<=n; i++)cin >> c[i];
    for(int i=0; i<m; i++)cin >> q[i].l >> q[i].r, q[i].id = i, q[i].blk = q[i].l/mxn;
    sort(q,q+m);

    vector<pii>ans(m);

    for(int i=0, l=1, r=0; i<m; i++){
        if(q[i].l == q[i].r){
            ans[q[i].id] = {0,1};
            continue;
        }
        while(l > q[i].l)add(--l);
        while(r < q[i].r)add(++r);
        while(l < q[i].l)del(l++);
        while(r > q[i].r)del(r--);
        ll len = r-l+1;
        ans[q[i].id] = {sum,len*(len-1)/2};
    }

    for(auto [x,y] : ans){
        if(x){
            ll t = __gcd(x,y);
            x = x/t;
            y = y/t;
        }else y = 1;
        cout << x << "/" << y << "\n";
    }
}
