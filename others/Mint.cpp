#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll MOD = 998244353;

class Mint {
public:
    ll value;

    Mint(ll v = 0) : value((v % MOD + MOD) % MOD) {}

    Mint operator+(const Mint &other) const {
        return Mint(value + other.value);
    }

    Mint operator-(const Mint &other) const {
        return Mint(value - other.value);
    }

    Mint operator*(const Mint &other) const {
        return Mint(value * other.value);
    }

    Mint operator/(const Mint &other) const {
        return *this * other.inverse();
    }

    Mint inverse() const {
        ll a = value, b = MOD, u = 1, v = 0;
        while (b) {
            ll q = a / b;
            a -= q * b; swap(a, b);
            u -= q * v; swap(u, v);
        }
        return Mint(u);
    }

    Mint pow(ll exp) const {
        Mint result = 1, base = *this;
        while (exp) {
            if (exp % 2) result = result * base;
            base = base * base;
            exp /= 2;
        }
        return result;
    }

    friend ostream &operator<<(ostream &os, const Mint &m) {
        return os << m.value;
    }
};

Mint f(ll x, ll y, ll m) {
    Mint res = 0;
    if (x == 0 || y == 0) return 0;

    { // odd row
        ll r = (x + 1) / 2, c = (y + 1) / 2;
        res = res + Mint(c) * m * r * (r - 1);
        res = res + Mint(r) * c * c;
    }

    { // even row 
        ll r = x / 2, c = y / 2;
        res = res + Mint(c) * m * r * r;
        res = res + Mint(r) * c * (c + 1);
    }

    return res;
}

int main() {
    ll n, m;
    cin >> n >> m;

    int q;
    cin >> q;

    while (q--) {
        ll a, b, c, d;
        cin >> a >> b >> c >> d;
        cout << (f(b, d, m) - f(b, c - 1, m) - f(a - 1, d, m) + f(a - 1, c - 1, m)).value << "\n";
    }
}