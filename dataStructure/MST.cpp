#include <bits/stdc++.h>
using namespace std;

struct edge{
  int u;
  int v;
  int w;
};

// DSU : parent
vector<int>parent;

// sort 2 edges
bool cmp(edge a , edge b){
  return a.w < b.w;
}

// DSU : find
int find(int v){
  return ((parent[v] == v) ? v : parent[v] = find(parent[v]));
}

// DSU : merge
void merge(int a , int b){
  if(find(a) != find(b))parent[find(a)] = find(b);
}

int main() {
  int n , m;
  cin >> n >> m;

  // add edges
  edge edges[m];
  for(int i=0 ; i<m ; i++)cin >> edges[i].u >> edges[i].v >> edges[i].w;
  sort(edges , edges+m , cmp);

  // set parent of DSU
  for(int i=0 ; i<=n ; i++)parent.push_back(i);

  //kruskal algorithm
  int sum = 0;
  for(int i=0 ; i<m ; i++){
    if(find(edges[i].u) != find(edges[i].v)){
      sum += edges[i].w;
      merge(edges[i].u , edges[i].v);
    }
  }

  cout << sum;
  return 0;
}
