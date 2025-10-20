#include <bits/stdc++.h>
#define all(a) a.begin(), a.end()
#define sz(a) (int)a.size()
#define int long long
#define Tp template<typename T>
#define Ts template<typename T,typename... Ar>
using namespace std;

template <class T>
using vc = vector<T>;
template <class T>
using vvc = vector<vc<T>>;
template <class T>
using vvvc = vector<vvc<T>>;
template <class T>
using vvvvc = vector<vvvc<T>>;
typedef pair<int, int> pii;

template <typename T>
ostream &operator<<(ostream &os, const pair<T, T> &data) { return os << data.first << ' ' << data.second; }
template <typename T>
istream &operator>>(istream &is, pair<T, T> &data) { return is >> data.first >> data.second; }
template <typename T>
ostream &operator<<(ostream &os, const vector<T> &data)
{
        for (T x : data)
                os << x << ' ';
        return os;
}
template <typename T>
istream &operator>>(istream &is, vector<T> &data)
{
        for (T &x : data)
                is >> x;
        return is;
}
 
template<class T>inline void chmin(T &x, T y) { if (y < x) x = y; }
template<class T>inline void chmax(T &x, T y) { if (y > x) x = y; }
namespace Debug{
	Tp void _debug(char* f,T t){cerr<<f<<'='<<t<<endl;}
	Ts void _debug(char* f,T x,Ar... y){while(*f!=',') cerr<<*f++;cerr<<'='<<x<<",";_debug(f+1,y...);}
	#ifdef LOCAL
	#define err(...) _debug((char*)#__VA_ARGS__,__VA_ARGS__)
	#else 
	#define err(...) void()
	#endif
}using namespace Debug;

mt19937_64 rng(chrono::steady_clock::time_point::clock().now().time_since_epoch().count());

const int N = 5e5 + 10;
const int INF = 1e18;
const int MOD = 998244353; 
const int LOG = 20;

typedef __int128_t ll;

int solve(){
}

int32_t main()
{
  ios::sync_with_stdio(false);
  cin.tie(0);

  int tt;
  cin >> tt;
  for(int i = 1; i <= tt; i++){
	printf("Case #%d: %d\n", i, solve());
  }
}

// 0 2 1 -> 1 1 0 0 0
// 2 1 0 -> 0 0 0 0 2