#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> pii;

int main(){
    ll h, x, y, z;
    cin >> h >> x >> y >> z;

    ll dis[x];
    for(int i=0; i<x; i++)dis[i] = 1e18;
    dis[0] = 0;

    priority_queue<pii, vector<pii>, greater<pii>>pq;
    pq.push({0,0});

    bool vis[x];
    memset(vis, 0, sizeof vis);

    while(!pq.empty()){
        ll w = pq.top().first;
        ll u = pq.top().second;
        pq.pop();
        if(vis[u])continue;
        vis[u] = 1;

        // use y
        if(dis[(u+y)%x] > dis[u]+y){
            dis[(u+y)%x] = dis[u]+y;
            pq.push({dis[(u+y)%x],(u+y)%x});
        }

        // use z
        if(dis[(u+z)%x] > dis[u]+z){
            dis[(u+z)%x] = dis[u]+z;
            pq.push({dis[(u+z)%x],(u+z)%x});
        }
    } 

    ll ans = 0;
    for(int i=0; i<x; i++)if(h>=dis[i])ans += (h-dis[i])/x+1;
    cout << ans;
}