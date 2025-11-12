#include <bits/stdc++.h>
#define all(a) (a).begin(), (a).end()
#define sz(a) (long long) (a).size()
using namespace std;

struct SuffixArray{
	vector<int> sa, lcp, rank;
	SuffixArray(string& s, int lim = 256){
		int n = sz(s) + 1, k = 0, a, b;
		vector<int> x(all(s) + 1), y(n), ws(max(n, lim));
		rank = vector<int>(n);
		sa = lcp = y, iota(all(sa), 0);
		for (int j = 0, p = 0; p < n; j = max(1LL, j * 2LL), lim = p) {
			p = j, iota(all(y), n - j);
			for(int i = 0; i <  n; i++) if(sa[i] >= j) y[p++] = sa[i] - j;
			fill(all(ws), 0);
			for(int i = 0; i <  n; i++) ws[x[i]]++;
			for(int i = 1; i < lim; i++) ws[i] += ws[i - 1];
			for(int i = n; i--;) sa[--ws[x[y[i]]]] = y[i];
			swap(x, y), p = 1, x[sa[0]] = 0;
			for(int i = 1; i < n; i++) a = sa[i - 1], b = sa[i], x[b]
				= (y[a] == y[b] && y[a + j] == y[b + j]) ? p - 1 : p++;
			for(int i = 1; i < n; i++) rank[sa[i]] = i;
			for(int i = 0, j; i < n - 1; lcp[rank[i++]] = k)
				for (k && k--, j = sa[rank[i] - 1];
					i + k < s.size() && j + k < s.size() && s[i + k] == s[j + k]; k++);
		}
	}
};
    // height == lcp
    // Note:
    // height[i] = longest common prefix of suffix(sa[i-1]) suffix(sa[i])
    // longest common prefix(sa[i], sa[j]) = min(height[i+1]... height[j])

    // Problem 1
    // find the longest repeated (occurs at least twice) substring (can overlap)
    // max value of (height)

    // Problem 2
    // find the longest repeated substring, cannot overlap
    // binary search on answer k
    // Divide height into blocks [0...i1-1] [i1...i2-1] ...
    // height[i1] < k
    // if(max(sa[0...i]) - min(sa[0...i])) for any bock i >= k
    // => longest common prefix at least k and separate at least k apart

    // Problem 3
    // Find longest substring that repeated at least k times
    // same approac -> divide
    // Then find if exist block with at least k strings

    // Problem 4
    // ***每個字串都是某個後綴的前綴***
    // every suffix(sa[k]) contribute n - sa[k] no. of prefix
    // but height[k] of them are repeated
    // no. of distinct substring = n (n+1) / 2 - sum of height

    // Problem 5
    // Longest palindrome substring
    // find longets repeated substring of s + '# + rev(s)

    // Problem 6
    // consecutive repeated string (e.g. abababa) ab repeated R = 3 times, R is max
    // for each k from 1 to n, see if n%k == 0 and RMQ(height[rank[1]]...height[rank[k+1]]) == n - k
 
    // Problem 7
    // Find the substring with most consecutive repated string R = sqrtababababeipi => S = abababab is the answer
    // Consider repeated string of length L
    // if S consist of at least 2 L, then it must contain 2 of the R[0], R[L], R[2*L] ...
    // so just consider r[L*i] and r[L*(i+1)] can extend to where, let the length be K, ans = max(K/L + 1)

    // Problem 8
    // longest common substring of A+B
    // find Problem 1 of (A + '#' + B), but the suffix are orriginally in different string