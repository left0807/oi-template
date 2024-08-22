#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll N = 2e5+1;

vector<ll>p(N), val(N,0);

int find(int v){
  if(v == p[v]){
    return v;
  }else{
    int t = p[v]; // old parent
    p[v] = find(p[v]); // compression
    val[v] += val[t]; // val + parent val
    return p[v]; // return new parent
  }
}

int main(){
  int n, q;
  cin >> n >> q;

  for(int i=1; i<=n; i++)p[i] = i;
  
  vector<int>ans;
  for(int i=0; i<q; i++){
    ll a, b, d;
    cin >> a >> b >> d;

    if(a == b){
      if(d == 0)ans.push_back(i+1);
      continue;
    }

    int x = find(a);
    int y = find(b);

    if(x == y){
      if(val[a] - val[b] == d)ans.push_back(i+1);
    }else{
      p[x] = y;
      val[x] = val[b] + d - val[a];
      ans.push_back(i+1);
    }
  }

  for(int e : ans)cout << e << " ";
}