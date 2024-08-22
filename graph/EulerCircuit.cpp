#include <bits/stdc++.h>
using namespace std;

const int N = 2e5+5;
vector<int>adj[N];

void circuit(int n){
    if(n==0)return ;

    vector<int>s, ans; 
    s.push_back(0);

    while(!s.empty()){
        int u = s.back();
        if(!adj[u].empty()){ // need to continue visit 
            int v = adj[u].back();
            adj[u].pop_back();
            s.push_back(v);
        }else{
            ans.push_back(u);
            s.pop_back();
        }   
    }

    // reverse
    reverse(ans.begin(), ans.end());
}