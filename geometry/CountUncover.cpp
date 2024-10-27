#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main(){
    ll n, m;
    cin >> n >> m;

    set<ll>horz, vert, slash, bslash;
    for(int i=0; i<m; i++){
        ll x, y;
        cin >> x >> y;
        horz.insert(x);
        vert.insert(y);
        slash.insert(x+y);
        bslash.insert(x-y);
    }

    ll ans = (n-horz.size())*(n-vert.size());

    for(auto d : slash){
        set<ll>cross;
        for(auto x : horz)if(1 <= d-x && d-x <= n)cross.insert(x);
        for(auto y : vert)if(1 <= d-y && d-y <= n)cross.insert(d-y);
        if(d-1 <= n)ans -= d-1-cross.size();
        else ans -= 2*n-(d-1)-cross.size();
    }

    for(auto d : bslash){
        set<ll>cross;
        for(auto x : horz)if(1 <= x-d && x-d <= n)cross.insert(x);
        for(auto y : vert)if(1 <= y+d && y+d <= n)cross.insert(y+d);
        for(auto e : slash)if((d+e)%2 == 0 && 1 <= (d+e)/2 && (d+e)/2 <= n && 1 <= (e-d)/2 && (e-d)/2 <= n)cross.insert((d+e)/2);
        if(1-d >= 1)ans -= n+d-cross.size();
        else ans -= n-d-cross.size();
    }

    cout << ans << "\n";
}

/*
d = x-y 
e = x+y
x = (d+e)/2, y = (e-d)/2
*/