#include <bits/stdc++.h>
using namespace std;

const int MOD = 998244353;
const int G = 3; // Primitive root of 998244353

// Fast modular exponentiation
long long power(long long base, long long exp) {
    long long res = 1;
    base %= MOD;
    while (exp > 0) {
        if (exp % 2 == 1) res = (res * base) % MOD;
        base = (base * base) % MOD;
        exp /= 2;
    }
    return res;
}

// Modular inverse
long long modInverse(long long n) {
    return power(n, MOD - 2);
}

// Number Theoretic Transform (NTT)
// O(N log N)
void ntt(vector<long long>& a, bool invert) {
    int n = a.size();
    
    // Bit-reversal permutation
    for (int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1) j ^= bit;
        j ^= bit;
        if (i < j) swap(a[i], a[j]);
    }

    // Cooley-Tukey iterative algorithm
    for (int len = 2; len <= n; len <<= 1) {
        // wlen = G^((MOD-1)/len)
        long long wlen = power(G, (MOD - 1) / len);
        if (invert) wlen = modInverse(wlen);
        
        for (int i = 0; i < n; i += len) {
            long long w = 1;
            for (int j = 0; j < len / 2; j++) {
                long long u = a[i + j];
                long long v = (a[i + j + len / 2] * w) % MOD;
                
                a[i + j] = u + v < MOD ? u + v : u + v - MOD;
                a[i + j + len / 2] = u - v >= 0 ? u - v : u - v + MOD;
                w = (w * wlen) % MOD;
            }
        }
    }

    // Scale back if inverse NTT
    if (invert) {
        long long n_inv = modInverse(n);
        for (long long& x : a) x = (x * n_inv) % MOD;
    }
}

// Polynomial Multiplication
// O(N log N) where N is the combined degree
vector<long long> multiply(vector<long long> const& a, vector<long long> const& b) {
    if (a.empty() || b.empty()) return {};
    
    vector<long long> fa(a.begin(), a.end());
    vector<long long> fb(b.begin(), b.end());
    
    // Find next power of 2 that bounds the new polynomial degree
    int n = 1;
    while (n < a.size() + b.size()) n <<= 1;
    
    fa.resize(n); 
    fb.resize(n);

    // Transform both polynomials
    ntt(fa, false); 
    ntt(fb, false);
    
    // Pointwise multiplication
    for (int i = 0; i < n; i++) {
        fa[i] = (fa[i] * fb[i]) % MOD;
    }
    
    // Inverse transform
    ntt(fa, true);

    // Remove leading zeros (highest degree terms that are 0)
    while (fa.size() > 1 && fa.back() == 0) {
        fa.pop_back();
    }
    
    return fa;
}

// --- Example Usage ---
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // Polynomial A: 1 + 2x
    vector<long long> A = {1, 2}; 
    
    // Polynomial B: 3 + 4x
    vector<long long> B = {3, 4}; 

    // Result should be: (1*3) + (1*4 + 2*3)x + (2*4)x^2 = 3 + 10x + 8x^2
    vector<long long> C = multiply(A, B);

    for (int i = 0; i < C.size(); i++) {
        cout << C[i] << (i == C.size() - 1 ? "" : " ");
    }
    cout << "\n";

    return 0;
}