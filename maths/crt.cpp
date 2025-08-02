typedef long long ll;

ll exgcd(ll a, ll b, ll &x, ll &y, ll d = 0){ // a*x + b*y = d = gcd(a,b)
    if(b==0)x = 1, y = 0, d = a;
    else d = exgcd(b, a%b, y, x), y-= a/b*x;
    return d;
}

ll inv(ll a, ll m, ll x = 0, ll y = 0){
    exgcd(a,m,x,y);
    return (x%m+m)%m;
}

ll crt(vector<ll>&m, vector<ll>&a){
    int n = m.size();
    ll mul = 1;
    for(int i=0; i<n; i++)mul *= m[i];

    ll ans = 0;
    for(int i=0; i<n; i++){
        ll t = mul/m[i], c = inv(t,m[i]);
        ans = (ans+((a[i]*t)%mul)*c%mul)%mul;
    }

    return ans;
}
