#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

template <class T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

int main() {
  int n;
  cin >> n;
  vector<int> a(n);
  for (int i=0; i<n; i++) cin >> a[i];
  vector<int>b(n, a[0]);
  ordered_set<pair<int, int>> os;
  os.insert(pair(a[0], 0));
  function<int(int)> rank;
  rank = [&] (int x) {
    return 1LL + os.order_of_key(pair(x, 0));
  };

  cout << "1\n";
  for (int i=1; i<n; i++) {
    b[i] = a[i] + rank(b[i-1]);
    os.insert(pair(b[i], i));
    cout << rank(b[i]) << "\n";
  }
}