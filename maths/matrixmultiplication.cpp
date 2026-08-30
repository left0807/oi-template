#include <bits/stdc++.h>
using namespace std;

#define int long long 
#define sz(a) a.size()
const int MOD = 998244353;

template <class T>
using vc = vector<T>;
template <class T>
using vvc = vector<vc<T>>;
template <class T>
using vvvc = vector<vvc<T>>;
template <class T>
using vvvvc = vector<vvvc<T>>;
typedef pair<int, int> pii;

// ****** 1 base
vvc<int> m_mul(const vvc<int>& a, const vvc<int>& b){
        assert(sz(a[0]) == sz(b));
        vvc<int> r(sz(a), vc<int>(sz(b[0])));

        for(int i = 1; i < sz(a); i++){
                for(int j = 1; j < sz(b[0]); j++){
                        for(int k = 1; k < sz(b); k++){
                                r[i][j] += a[i][k] * b[k][j] % MOD;
                                r[i][j] %= MOD;
                        }
                }
        }
        return r;
}

vvc<int> mpow(vvc<int> x, int y){
        assert(sz(x) == sz(x[0]));
        vvc<int> r(sz(x), vc<int>(sz(x)));
        for(int i = 1; i < sz(x); i++) r[i][i] = 1;


        while(y){
                if(y&1) r = m_mul(r, x);
                x = m_mul(x, x);
                y >>= 1;
        }
        return r;
}