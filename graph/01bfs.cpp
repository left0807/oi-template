#include <bits/stdc++.h>
using namespace std;

int main(){
    int k;
    cin >> k;

    int dis[k];
    for(int i=0; i<k; i++)dis[i] = 1e9;
    dis[1] = 1;

    deque<int>dq;
    dq.push_back(1);

    while(!dq.empty()){
        int u = dq.front();
        dq.pop_front();

        // +1 
        if(dis[(u+1)%k] > dis[u]+1){
            dis[(u+1)%k] = dis[u]+1;
            dq.push_back((u+1)%k);
        }

        // *10 
        if(dis[(u*10)%k] > dis[u]){
            dis[(u*10)%k] = dis[u];
            dq.push_front((u*10)%k);
        }
    }
    cout << dis[0];
}
