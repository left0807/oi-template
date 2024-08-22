#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 1e5+10;

struct node{
    int idx, val, par, ch[2];
    friend bool operator<(node a, node b) { return a.idx < b.idx; }
    void init(int _idx, int _val, int _par){
        idx = _idx, val = _val, par = _par, ch[0] = ch[1] = 0;
    }
}tree[N];

int root, top, stk[N];

int build(int n){
    for(int i=1; i<=n; i++){
        int k = i-1; 
        while(tree[k].val > tree[i].val)k = tree[k].par; // push upward
        tree[i].ch[0] = tree[k].ch[1]; 
        tree[k].ch[1] = i;
        tree[i].par = k;
        tree[tree[i].ch[0]].par = i;
    }
    return tree[0].ch[1];
}

int main(){
    int n;
    cin >> n;
    tree[0].init(0, 0, 0);
    for(int i=1; i<=n; i++){
        int w;
        cin >> w;
        tree[i].init(i,w,0);
    }
    root = build(n);
}