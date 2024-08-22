#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

struct line{
  ll l, r, y, v;
};

struct node{
  ll sum, lazy;
};

vector<ll>arr; // idx -> val 

const ll N = 200000;
vector<node>seg(4*N);

void update(ll v, ll l, ll r,ll ql, ll qr, ll val){
  if(ql > r || qr < l )return ;
  if(ql <= l && r <= qr){
    seg[v].lazy += val;
  }else{
    ll m = (l+r)>>1;
    update(v*2, l, m, ql, qr, val);
    update(v*2+1,m+1,r,ql,qr, val);
  }
  if(seg[v].lazy > 0){
    // cout << arr[r+1] << ' ' << arr[l] << " " << l << ' ' << r <<  "\n";
    seg[v].sum = arr[r+1] - arr[l];
  }else{
    if(l==r){
      seg[v].sum = 0;
    }else{
      seg[v].sum = seg[v*2].sum + seg[v*2+1].sum;
    }
  }
  // cout << seg[v].sum << ' ' << l << " " << r << "\n";
}

bool cmp(line a, line b){
  if(a.y == b.y)return a.v > b.v;
  else return a.y < b.y;
}

int main(){
  ll n;
  cin >> n;

  // discretization how???
  ll lx[n], ly[n], hx[n], hy[n];
  
  for(ll i=0; i<n; i++){
    cin >> lx[i] >> ly[i] >> hx[i] >> hy[i];
    arr.push_back(lx[i]);
    arr.push_back(hx[i]);
  }

  sort(arr.begin(), arr.end());
  ll cnt = unique(arr.begin(),arr.end())-arr.begin();

  unordered_map<ll,ll>mp; // val -> idx
  for(ll i=0; i<cnt; i++){
    mp[arr[i]] = i;
  }

  vector<line>lines(2*n);
  for(ll i=0; i<n; i++){
    lines[2*i] = {mp[lx[i]],mp[hx[i]],ly[i],1};
    lines[2*i+1] = {mp[lx[i]],mp[hx[i]],hy[i],-1};
  }

  sort(lines.begin(), lines.end(), cmp);
  ll ans = 0, y = 0;

  for(ll i=0; i<2*n; i++){
    // cout << seg[1].sum << " " << lines[i].y-y << "\n";
    ans += seg[1].sum*(lines[i].y-y);
    update(1,0,cnt-1,lines[i].l,lines[i].r-1,lines[i].v);
    y = lines[i].y;
  }

  cout << ans;
}