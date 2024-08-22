#include <bits/stdc++.h>
using namespace std;

const int N = 1e5;
vector<int>adj[N];

int main(){
    int n;
    cin >> n;

    bool flag = 1;
    vector<int>side(n,-1);
    queue<int>q;
    for(int i=0; i<n; i++){
        if(side[i] != -1)continue;
        q.push(i);
        side[i] = 0;
        while(!q.empty()){
            int u = q.front();
            q.pop();
            for(int v : adj[u]){
                if(side[v]==-1){
                    side[v] = side[u]^1;
                    q.push(v);
                }else if(side[v] == side[u])flag = 0;
            }
        }
    }
    cout << (flag ? "YES" : "NO") << endl;
}




