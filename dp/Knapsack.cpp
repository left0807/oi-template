/*

Knapsack 9 talk

*/

/*
1. 0-1 knapsack 

Problem statement:
- N item V size knapsack 
- c[i] cost w[i] value
- put 1 max 

use rolling array for O(n) space complexity

Trick:
- must fillin -> set f[1..v] as -inf, f[0] as 0 
- not mist fillin -> set[0..v] as 0
- set bound : max(v - c[i+1..n], c[i])
  -> can't contribute ans below bound 

Formula:
for(int i=1; i<=n; i++){ // item 1 -> iten n
  for(int j=v; j>=0; j--){ // j-c[i] is still in prev state
    f[j] = max(f[j], f[j-c[i]]+w[i]); // from 2 subproblem 
  }
}
*/




/*
2. Complete knapsack

Problem statement:
- N item V size knapsack
- c[i] cost w[i] value
- no max limit

Trick:
- maintrain monotonic (remove price larger but value smaller)
- use pow to represent (1,2,4,8) -> O(V) to O(log(V))

Formula:
for(int i=1; i<=n; i++){
  for(int j=c[i]; j<=v; j++){
    f[j] = max(f[j], f[j-c[i]]+w[i]); // best f[j-c[i]] with item i is found already
  }
}
*/




/*

3. Multiple knapsack(多重背包)

Problem statement:
- N item V size knapsack 
- C[i] cost W[i] value 
- N[i] max amount 

1. ith item -> N[i] item 
- 0-1 knapsack 
- 1 item -> N[i] item

2. ith item -> 1,2,4..2^(k-1),N[i]-2^(k-1)+1
- 1 item -> log(N[i]) item

Formula:
for(int i=1; i<=n; i++){
  int c = 1, k = N[i];
  while(k > c){
    k -= c; // divide item
    // 0-1 knapsack
    c *= 2;
  }

  if(k > 0){ // remain item
    // 0-1 knapsack
  }
}

3. Montonic optimization
- ref : https://zhuanlan.zhihu.com/p/379510583
- F[i] = max(F[i], F[i-C[i]]+W[i], ...., F[i-C[i]*N[i]]+W[i]*N[i])
- E.g. V = 10, C = 2, N = 3
  - F[10] <- max(F[8],F[6],F[4])
  - F[8] <- (F[6],F[4],F[2])
- Sliding window! 
- for each i%C[i] same, we can maintain a queue to find max
- why need 2 array? 
  - otherwise use more then N item (E.g. F[2] -> F[8] - > F[10], but F[2] can't reach F[10]!) 
  
Formula:
for(int i=0; i<c[i]; i++){ // mod 
  deque<int>dq;
  for(int k=i; k<=V; k+=c[i]){
    dp[k] = f[k];
    if(!dq.empty() && dq.front < k-c[i]*n[i])dq.pop_front(); // out of bound (E.g. F[2] can't transfer to F[10])
    if(!dq.empty()){
      dp[k] = max(dp[k], f[dq.front()]+(k-dq.front())/c[i]*w[i] ); // current max in queue
    }
    
    while(!dq.empty() && f[dq.back()]-(dq.back()-j)/c[i]*w[i] <= f[k]-(k-j)/c[i]*w[i] )dq.pop_back(); // (F[k] is larger -> pop useless out)
    dq.push(k); // add F[k] into queue
  }
}
*/




/*

4. Mix knapsack

Problem statement: 
Some items only take once
some items inf take
some items limit take 

mix 0-1 knapsack , Complete knapsack and mutiple knapsack together

Formula:
for(int i=0; i<n; i++){
    int w,v,p;
    cin >> w >> v >> p;
    if(p==0){ // complete
      for(int j=w; j<=t; j++)dp[j] = max(dp[j], dp[j-w]+v);
    }else if(p == 1){ // 0-1
      for(int j=t; j>=w; j--)dp[j] = max(dp[j], dp[j-w]+v);
    }else{ // multiple
      int cnt = p;
      int c = 1;
      while(cnt > c){
        cnt -= c;
        for(int j=t; j>=c*w; j--)dp[j] = max(dp[j], dp[j-c*w]+c*v);
        c *= 2;
      }
      if(cnt != 0){
        for(int j=t; j>=cnt*w; j--)dp[j] = max(dp[j], dp[j-cnt*w]+cnt*v);
      }
    }   
  }
*/





/*

5. 2 dimension cost knapsack (二维费用背包)

Problem statement:
- Each item has 2 different cost (C[i], G[i])
- each cost has its own maximum (V, M)

Add one more dimension for cost 
The second dimension maybe hidden (E.g. Limit total amount of item can take -> cost)

Formula:
for(int i=0; i<n; i++){
  for(int j=v; j>=c[i]; j--){
    for(int k=m; k>=g[i]; k--){
      dp[j][k] = max(dp[j][k], dp[j-c[i]][k-g[i]]+w[i]);
    }
  }
}

*/





/*

6. Group knapsack (分组背包)

Problem statement: 
- Items are divided into groups
- Each group only can pick 1 item

For each gp , either we choose 1 or no choose 

F[k][j] = max(F[k][j], F[k-1][j-w[i]]+v[i]) // item i belongs to gp k 

Group : choose the 0,1,2...th item in gp 
Multiple : choose 0,1,2... item 

limit max item -> 1 gp 

Formula: 

for(int i=1 ; i<=n; i++){
  cin >> s; // no.of item in gp
  for(int j=0; j<s; j++)cin >> w[j] >> v[j];
  for(int j=v; j>=0; j--){ // set 0 to min w for optimization
    for(int k=0; k<s; k++){
      dp[j] = max(dp[j] , dp[j-w[k]]+v[k]);
    }
  }
}


*/





/*

7. Dependency knapsack(有依赖的背包)

Problem statement: 
- item has some relationship
- if we choose item i, we must choose item j 


Assume one parent , with n child 
-> we have 2^n + 1 options 

We can only choose 1 option -> transfer it to a group knapsack
For options with same value -> only leave largest value one 

0-1 knapsack -> get F[0...V-c[i]] 
-> change it to V - c[i] +1 item -> c[i] + k item value = F'[k] + w[i]


Formula: 
for(int p : gp[0]){
  memcpy(dp2,dp,sizeof dp2);
  for(int j : gp[p]){
    for(int i=n-w[p]; i>=w[j];i--)dp2[i] = max(dp2[i], dp2[i-w[j]]+w[j]*v[j]); // knapsack on gp
  }
  for(int i= w[p]; i<=n; i++)dp[i] = max(dp[i], dp2[i-w[p]]+w[p]*v[p]); // + parent item 
}


Tree:
void dfs(int u){
  for(int v : adj[u]){ // each child in v
    dfs(v); // transfer it into item

    for(int i=m; i>=0; i--){// 0-1 knapsack
      for(int j=i; j>=1; j--){ // subtree v pick how many
        dp[u][i] = max(dp[u][i], dp[v][j]+dp[u][i-j]);
      }
    }
  }

  // dp[u][i] contain max with only child -> parent also needed!
  for(int i=m; i>=1; i--)dp[u][i] = dp[u][i-1]+s[u];
}

*/


#include <bits/stdc++.h>
using namespace std;

int main(){
    int n, m;
    cin >> n >> m;

    vector<int>gp[m+1], w(m+1), v(m+1);

    for(int i=1; i<=m; i++){
        int p;
        cin >> w[i] >> v[i] >> p;
        gp[p].push_back(i);
    }

    int dp[n+1], dp2[n+1];
    memset(dp,0, sizeof dp);

    for(int p : gp[0]){
        memcpy(dp2,dp,sizeof dp2);
        for(int j : gp[p]){
            for(int i=n-w[p]; i>=w[j];i--)dp2[i] = max(dp2[i], dp2[i-w[j]]+w[j]*v[j]);
        }
        for(int i= w[p]; i<=n; i++)dp[i] = max(dp[i], dp2[i-w[p]]+w[p]*v[p]);
    }

    cout << dp[n];
}
