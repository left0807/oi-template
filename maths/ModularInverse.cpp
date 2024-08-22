#include <bits/stdc++.h>
#define int long long
using namespace std;

const int MOD = 1e9 + 7;

int pow(int x, int y){
    int res = 1;
    x = x%MOD;

    while(y > 0){
        if(y&1) res = (res*x)%MOD;

        y = y >> 1;
        x = (x*x)%MOD;
    }
    return res;
}

int inv(int x){
    return pow(x, MOD-2);
}

vector<int> fact{1}, invfact{1};

int C(int n, int r){
    if(n < r) return 0;

    for(int i = fact.size(); i <= n; i++){
        fact.push_back((fact.back()*i)%MOD);
        invfact.push_back(inv(fact.back()));
    }

    return ((fact[n]*invfact[r])%MOD*invfact[n-r])%MOD;
}

int32_t main() 
{
    cout << C(4, 2) << '\n';
    return 0; 
} 