#include <bits/stdc++.h>
using namespace std;

const int N = 2e5+5;

struct AhoCorasick{
    struct node{
        int son[26];
        int fail;
        int deg;
        int idx;
        int ans = 0;

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

    void insert(string s, int& idx){
        int u = 0;
        for(char c : s){
            int &son = tr[u].son[c-'a'];
            if(!son)son = ++tot, tr[son].init();
            u = son;
        }
        if(!tr[u].idx)tr[u].idx = ++pidx;
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

int main(){
    int n;
    cin >> n;

    vector<int>idx(n);

    AC.init();
    for(int i=0; i<n; i++){
        string s;
        cin >> s;
        AC.insert(s,idx[i]);
        AC.ans[idx[i]] = 0; 
    }
    AC.build();
    string t;
    cin >> t;
    AC.query(t);
    AC.topu();
    for(int i=0; i<n; i++)cout << AC.ans[idx[i]] << "\n";

}
