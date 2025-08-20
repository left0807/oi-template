#include <bits/stdc++.h>
using namespace std;

#define int long long 
typedef array<int,2>ar;

const int N = 1e5+5;
const int LG = 60;
const int LG2 = 23;

struct linearBasis{
    int d[LG];
    int num;

    linearBasis() {clear();}

    void clear(){
        memset(d, 0, sizeof d);
        num = 0;
    }

    bool add(int x){
        for(int i=LG-1; i>=0; i--){
            if((x>>i)&1){
                if(!d[i]){
                    d[i] = x;
                    num++;
                    for(int j=i-1; j>=0; j--)if(d[i]&(1ll<<j))d[i] ^= d[j];
                    for(int j=i+1; j<LG; j++)if(d[j]&(1ll<<i))d[j] ^= d[i];
                    return 1;
                }
                x ^= d[i];
            }
        }
        return 0;
    }

    int queryMax(){
        int res = 0;
        for(int i=LG-1; i>=0; i--)if((res^d[i])>res)res ^= d[i];
        return res;
    }

    int queryMin(){
        for(int i=0; i<LG; i++)if(d[i])return d[i];
        return 0;
    }

    vector<int> getIndependent(){
        vector<int> res;
        for(int i=0; i<LG; i++)if(d[i])res.push_back(d[i]);
        return res;
    }

    int querykth(int k){
        vector<int> vec = getIndependent();
        int sz = vec.size();
        if(k >= (1ll<<sz))return -1;
        int res = 0;
        for(int i=0; i<sz; i++)if(k&(1ll<<i))res ^= vec[i];
        return res;
    }

    friend linearBasis merge(const linearBasis &a, const linearBasis &b){
        linearBasis res = a;
        for(int i=0; i<LG; i++)if(b.d[i])res.add(b.d[i]);
        return res;
    }
};

int32_t main(){
	int n, q;
	cin >> n >> q;

	vector<int>a(n+1), dep(n+1), lg(n+1,0);
	for(int i=1; i<=n; i++)cin >> a[i];
    for(int i=2; i<=n; i++)lg[i] = lg[i/2]+1;

	vector<vector<int>>g(n+1);
	for(int i=1; i<n; i++){
		int u, v;
		cin >> u >> v;
		g[u].push_back(v);
		g[v].push_back(u);
	}

	vector<vector<int>>anc(n+1,vector<int>(LG2));
	vector<vector<linearBasis>>sum(n+1,vector<linearBasis>(LG2));
	
    auto dfs = [&](auto&&self, int u, int p) -> void{
        dep[u] = dep[p]+1;
        anc[u][0] = p;
        sum[u][0].add(a[u]);
        for(int i=1; i<LG2; i++){
            anc[u][i] = anc[anc[u][i-1]][i-1];
            sum[u][i] = merge(sum[u][i-1],sum[anc[u][i-1]][i-1]);
        }
        for(int v : g[u]){
            if(v==p)continue;
            self(self, v, u);
        }
    };
    dfs(dfs,1,0);

    auto lca = [&](int x, int y) -> int{
        if(dep[x] < dep[y])swap(x,y);
        for(int i=LG2-1; i>=0; i--)if(dep[anc[x][i]] >= dep[y])x = anc[x][i];
        if(x==y)return x;
        for(int i=LG2-1; i>=0; i--){
            if(anc[x][i] != anc[y][i]){
                x = anc[x][i];
                y = anc[y][i];
            }
        }
        return anc[x][0];
    };

    auto kth = [&](int x, int k) -> int{
        for(int i=LG2-1; i>=0; i--)if(k&(1ll<<i))x = anc[x][i];
        return x;
    };

    while(q--){
        int x, y;
        cin >> x >> y;
        int w = lca(x,y);

        linearBasis lb;
        lb.add(a[w]);
        int lenx = lg[dep[x]-dep[w]], leny = lg[dep[y]-dep[w]];
        lb = merge(lb,sum[x][lenx]);
        lb = merge(lb,sum[kth(x,dep[x]-dep[w]-(1ll<<lenx))][lenx]);
        lb = merge(lb,sum[y][leny]);
        lb = merge(lb,sum[kth(y,dep[y]-dep[w]-(1ll<<leny))][leny]);

        cout << lb.queryMax() << "\n";
    }
}