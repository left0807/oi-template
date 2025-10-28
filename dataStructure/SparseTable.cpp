#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 10;
struct SparseTable{
	int st[N][20];
	void build(const vector<int>& sa){
		int n = sa.size();
		for(int i = 0; i < n; i++) st[i][0] = sa[i];
		for(int j = 1; j < 20; j++){
			for(int i = 0; i <= n - (1 << j); i++){
				st[i][j] = min(st[i][j - 1], st[i + (1 << j - 1)][j - 1]);
			}
		}
	}
	int query(int l, int r){
		// cout << "L, R: " << l << " " << r << endl;
		int d = __lg(r - l + 1);
		return min(st[l][d], st[r - (1 << d) + 1][d]);
	}
} ST;