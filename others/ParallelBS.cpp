#include <bits/stdc++.h>
using namespace std;

typedef pair<int,int> pii;

const int N = 2e5+5;
const int M = 1e6+5;
const int S = 505;

int f[S][S];
int a[N], b[N], y[N], c[N], d[N], z[N], l[N], r[N], ans[N];
vector<pii>g[M];
vector<int>qry[M];

int par[S*S];

int find(int v){
    return (par[v] == v) ? v : par[v] = find(par[v]);
}

void merge(int x, int y){
    int fx = find(x), fy = find(y);
    if(fx != fy)par[fx] = fy;
}

int main(){
    int h, w;
    cin >> h >> w;

    for(int i=1; i<=h; i++)for(int j=1; j<=w; j++)cin >> f[i][j];

    int q;
    cin >> q;
    for(int i=1; i<=q; i++)cin >> a[i] >> b[i] >> y[i] >> c[i] >> d[i] >> z[i];

    for(int i=1; i<=h; i++){
        for(int j=1; j<=w; j++){
            if(i+1<=h)g[min(f[i][j],f[i+1][j])].push_back({i*w+j,(i+1)*w+j});
            if(j+1<=w)g[min(f[i][j],f[i][j+1])].push_back({i*w+j,i*w+(j+1)});
        }
    }

    const int lim = 1e6;
    for(int i=1; i<=q; i++)l[i] = 1, r[i] = lim;

    while(1){
        bool fg = 1;
        for(int i=0; i<=lim; i++)qry[i].clear();
        for(int i=1; i<=q; i++){
            if(l[i] > r[i])continue;
            int m = (l[i]+r[i])/2;
            qry[m].push_back(i);
            fg = 0;
        }
        if(fg)break;
        for(int i=0; i<S*S; i++)par[i] = i;
        for(int i=lim; i>=0; i--){
            for(auto [u,v] : g[i])merge(u,v);
            for(auto id : qry[i]){
                int u = a[id]*w+b[id], v = c[id]*w+d[id];
                if(find(u) == find(v)){
                    ans[id] = i;
                    l[id] = i+1;
                }else r[id] = i-1;
            }
        }
    }

    for(int i=1; i<=q; i++)cout << y[i]+z[i]-2*min({y[i],z[i],ans[i]}) << "\n";
}
