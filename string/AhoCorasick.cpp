#include <bits/stdc++.h>
using namespace std;

const int N = 2e5+5;
const int MOD = 998244353;

struct AhoCorasick{
    struct node{
        int son[26];
        int fail;
        int deg;
        int idx;
        int ans = 0;
        int lst = 0;

        void init(){
            memset(son, 0, sizeof son); 
            ans = fail = idx = 0;
        }
    }tr[N];

    int ans[N];
    int tot, pidx;

    void init(){
        tot = pidx = 0;
        tr[0].init();
    }

    void insert(string s, int& idx, int id){
        int u = 0;
        for(char c : s){
            int &son = tr[u].son[c-'a'];
            if(!son)son = ++tot, tr[son].init();
            u = son;
        }
        if(!tr[u].idx)tr[u].idx = ++pidx;
        tr[u].lst |= 1 << id;
        idx = tr[u].idx;
    }

    void build(){
        queue<int>q;
        for(int i=0; i<26; i++)if(tr[0].son[i])q.push(tr[0].son[i]);
        while(q.size()){
            int u = q.front();
            q.pop();
            for(int i=0; i<26; i++){
                if(tr[u].son[i]){
                    tr[tr[u].son[i]].fail = tr[tr[u].fail].son[i];
                    tr[tr[tr[u].fail].son[i]].deg++;
                    q.push(tr[u].son[i]);
                }else{
                    tr[u].son[i] = tr[tr[u].fail].son[i];
                }
            }
        }
    }

    void query(string t){
        int u = 0;
        for(char c : t){
            u = tr[u].son[c-'a'];
            tr[u].ans++;
        }
    }

    void topu(){
        queue<int>q;
        for(int i=0; i<=tot; i++)if(!tr[i].deg)q.push(i);
        while(q.size()){
            int u = q.front();
            q.pop();
            ans[tr[u].idx] = tr[u].ans;
            int v = tr[u].fail;
            tr[v].ans += tr[u].ans;
            if(!--tr[v].deg)q.push(v);
        }
    }
}AC;

int dp[2][1<<8][N];

int main(){
    int n, l;
    cin >> n >> l;

    vector<int>idx(n);
    AC.init();
    for(int i=0; i<n; i++){
        string s;
        cin >> s;
        AC.insert(s,idx[i], i);
        AC.ans[idx[i]] = 0; 
    }
    AC.build();

    dp[1][0][0] = 1;
    for(int i = 0; i < l; i++){
        for(int bit = 0; bit < (1<<n); bit++){
            for(int v = 0; v < AC.tot; v++){
                for(int k = 0; k < 26; k++){
                    int to = AC.tr[v].son[k];
                    int nbit = bit | AC.tr[to].lst;
                    dp[i&1][nbit][to] = (dp[i&1^1][bit][v] + dp[i&1][nbit][to]) % MOD;
                }
            }
        }

        for(int bit = 0; bit < (1<<n); bit++){
            for(int v = 0; v <= AC.tot; v++){
                dp[i&1^1][bit][v] = 0;
            }
        }
    }

    int ans = 0;
    for(int i = 0; i <= AC.tot; i++) ans = (ans + dp[l&1^1][(1<<n)-1][i]);
    cout << ans << '\n';
}
