#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 3e5+1;
typedef pair<int, int> pii;
vector<ll>p(2*N), sz(2*N, 1), val(2*N);
vector<vector<int>>G2(2*N);

struct edge{int u, v, w;};
bool cmp(edge a, edge b){return a.w < b.w;}
int find(int v){return (p[v] == v) ? v : p[v] = find(p[v]);}

int main(){
  vector<edge>E;
  for(int i=0; i<m; i++)E.push_back({u[i],v[i],t[i]});
  sort(E.begin(), E.end(), cmp);
  iota(p.begin(), p.end(), 0);
  
  int cnt = n-1;
  for(auto [a,b,w] : E){
    int x = find(a), y = find(b);
    if(x==y)continue;
    p[x] = p[y] = ++cnt;
    sz[cnt] = sz[x]+sz[y];
    val[cnt] = w;
    G2[cnt].push_back(x);
    G2[cnt].push_back(y);
  }
}