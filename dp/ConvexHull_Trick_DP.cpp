#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#define int long long
#define double long double
#define pb push_back
#define eb emplace_back
#define pp pop_back
#define fi first
#define se second
#define all(a) a.begin(), a.end()

using namespace std;

// input vector and pair
template <typename T> ostream &operator<<(ostream &os, const pair<T, T> &data) { return os << data.first << ' ' << data.second; }
template <typename T> istream &operator>>(istream &is, pair<T, T> &data) { return is >> data.first >> data.second; }
template <typename T> ostream &operator<<(ostream &os, const vector<T> &data) { for (T x : data) os << x << ' '; return os; }
template <typename T> istream &operator>>(istream &is, vector<T> &data) { for (T &x : data) is >> x; return is; }

// helper function
template<class T, class U> inline bool chmin(T& a, const U& b){ if(a > b){ a = b; return true; } return false; }
template<class T, class U> inline bool chmax(T& a, const U& b){ if(a < b){ a = b; return true; } return false; }

const long long INF = numeric_limits<long long>::max();
const long long MOD = 1e9 + 7;
const int N = 1e6 + 10;
const int M = 200;
const int LOG = 30;
const double EPS = 1e-8;

typedef vector<int> vi;
typedef vector<vi> vii;
typedef vector<vii> viii;
typedef vector<char> vc;
typedef vector<vc> vcc;
typedef pair<int, int> pii;

void solve(){
  int n, L;
  cin >> n >> L;
  L++;

  vi s(n+1);
  for(int i = 1; i <= n; i++){
    cin >> s[i];
    s[i] += s[i-1] + 1;
  }

  vi dp(n+1);

  auto P = [&](int j) -> int
  {
    return dp[j] + 2*s[j]*L + s[j]*s[j];
  };
  auto slope = [&](int i, int j) -> double
  {
    return (double)(P(j) - P(i)) / (s[j] - s[i]);
  };

  /* 
  dp[i] = min(dp[j] + (S[i] - L - S[j])^2)
  dp[i] - (Si - L)^2 = min(dp[j] - 2SjSi + 2SjL + Sj^2)

  Assume j1 < j2, and j2 is better than j1

   - 2S(j2)Si + (dp[j2] + 2S(j2)L + S(j2)^2) <  - 2S(j1)Si + (dp[j1] + 2S(j1)L + S(j1)^2)
    P(j2) - P(j1) < 2Si(S(j2) -S(j1))

    (P(j2) - P(j1)) / (S(j2) - S(j1)) < 2Si
  */

  vi q(n+1);
  int t = 0, h = 0;

  for(int i = 1; i <= n; i++){
    while(t > h && slope(q[h], q[h+1]) <= 2*s[i]) h++; // because s[i] is increasing, therefore, slope <= s[i] will not be used in the future
    dp[i] = dp[q[h]] + (s[i] - L - s[q[h]])*(s[i] - L - s[q[h]]); // the slope of (head, head + 1) is the first slope > 2s[i] -> hence head is the optimal point
    while(t > h && slope(q[t], i) <= slope(q[t-1], q[t])) t--; // erase until the new point form a downward convex hull
    q[++t] = i;
  }
  cout << dp[n] << '\n';
} 

int32_t main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  srand(time(0));


  int tt = 1;
  // cin >> tt;
  
  for (int i = 1; i <= tt; i++) {
#ifndef ONLINE_JUDGE
    cout << "===============================================\n";
    cout << "Case #" << i << ":\n";
#endif
    solve();
  }
}