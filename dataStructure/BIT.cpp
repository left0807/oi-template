#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 10;

int BIT[N];
void add(int x, int v){
    for(int i = x; i < N; i += i&-i) BIT[i] += v;
}
int qry(int x){
    int res = 0; for(int i = x; i > 0; i -= i&-i) res += BIT[i]; return res;
}

int kth(int k){
    int sum = 0, x = 0;
    for(int i = __lg(N); i >= 0; i--){
        x += 1 << i;
        if(x >= N || sum + BIT[x] >= k)
            x -= 1 << i;
        else
            sum += BIT[x];
    }
    return x + 1;
}

// BIT range add, range query
int t1[N], t2[N];
void add(int x, int v){
    int v1 = x * v;
    for(int i = x; i < N; i += i&-i) t1[i] += v, t2[i] += v1;
}

int getsum(int *t, int x){
    int res = 0; for(int i = x; x > 0; i -= i&-i) res += t[i]; return res;
}

void range_add(int l, int r, int v){
    add(l, v), add(r + 1, -v);
}

int range_sum(int l, int r) {
  return (r + 1ll) * getsum(t1, r) - 1ll * l * getsum(t1, l - 1) -
         (getsum(t2, r) - getsum(t2, l - 1));
}