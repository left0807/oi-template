#include <bits/stdc++.h>
using namespace std;

// Use double for precision, complex for standard FFT
using cd = complex<double>;
const double PI = acos(-1.0);

// Fast Fourier Transform (FFT)
// O(N log N)
void fft(vector<cd>& a, bool invert) {
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
        // Angle for roots of unity
        double angle = 2 * PI / len * (invert ? -1 : 1);
        cd wlen(cos(angle), sin(angle));
        
        for (int i = 0; i < n; i += len) {
            cd w(1, 0);
            for (int j = 0; j < len / 2; j++) {
                cd u = a[i + j];
                cd v = a[i + j + len / 2] * w;
                
                a[i + j] = u + v;
                a[i + j + len / 2] = u - v;
                w *= wlen;
            }
        }
    }

    // Scale back if inverse FFT
    if (invert) {
        for (cd& x : a) x /= n;
    }
}

// Polynomial Multiplication for Integer Coefficients
// O(N log N)
vector<long long> multiply(vector<long long> const& a, vector<long long> const& b) {
    if (a.empty() || b.empty()) return {};
    
    // Find next power of 2 bounding the degree
    int n = 1;
    while (n < a.size() + b.size()) n <<= 1;
    
    // Convert to complex numbers and pad with zeros
    vector<cd> fa(a.begin(), a.end());
    vector<cd> fb(b.begin(), b.end());
    fa.resize(n);
    fb.resize(n);

    // Transform both polynomials
    fft(fa, false); 
    fft(fb, false);
    
    // Pointwise multiplication
    for (int i = 0; i < n; i++) {
        fa[i] *= fb[i];
    }
    
    // Inverse transform
    fft(fa, true);

    // Round back to integers
    vector<long long> result(n);
    for (int i = 0; i < n; i++) {
        // std::round prevents precision errors (e.g., 2.999999 -> 3)
        result[i] = round(fa[i].real());
    }

    // Remove leading zeros
    while (result.size() > 1 && result.back() == 0) {
        result.pop_back();
    }
    
    return result;
}

// --- Example Usage ---
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // Polynomial A: 1 + 2x
    vector<long long> A = {1, 2}; 
    
    // Polynomial B: 3 + 4x
    vector<long long> B = {3, 4}; 

    // Result should be: 3 + 10x + 8x^2
    vector<long long> C = multiply(A, B);

    for (int i = 0; i < C.size(); i++) {
        cout << C[i] << (i == C.size() - 1 ? "" : " ");
    }
    cout << "\n";

    return 0;
}