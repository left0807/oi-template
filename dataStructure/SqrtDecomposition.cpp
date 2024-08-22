#include <bits/stdc++.h>
using namespace std;

const int maxN = 10000,sqrtN = 100;
int arr[maxN];
int block[sqrtN];
int sz;

void preprocess(int n){
  int idx = -1;
  sz = sqrt(n);

  for(int i=0 ; i<n ; i++){
    if(i % sz == 0){
      idx++;
      block[idx] = 0;
    }
    block[idx] += arr[i];
  } 
}

// time complexity : O(1)
void update(int idx , int val){
  block[idx/sz] += val - arr[idx];
  arr[idx] = val;
}


// time complexity : O(sqrt(N))
int query(int l , int r){
  int sum = 0;

  while(l<r && l%sz != 0 && l != 0){
    sum += arr[l];
    l++;
  }

  while(l + sz -1 <= r){
    sum += block[l/sz];
    l += sz;
  }

  while(l<=r){
    sum += arr[r];
    l++;
  }

  return sum;
}

int main() {
  int n;
  cin >> n;
  for(int i=0 ; i<n ; i++)cin >> arr[i];
  preprocess(n);

  int m,l,r;
  cin >> m;
  for(int i=0 ; i<m ; i++){
    int v;
    cin >> v >> l >> r;
    if(v==1){
      cout << query(l,r) << "\n";
    }else{
      update(l,r);
    }
  }
  
  return 0;
}
