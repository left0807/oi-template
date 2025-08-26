#include <bits/stdc++.h>
using namespace std;

const int N = 2e5+5;
const int LG = 60;

struct linearBasis{
    int d[LG];
    int num;

    linearBasis() {clear();}

    void clear(){
        memset(d, 0, sizeof d);
        num = 0;
    }

    bool add(int x){
        for(int i=LG-1; i>=0; i--){
            if((x>>i)&&1){
                if(!d[i]){
                    d[i] = x;
                    num++;
                    for(int j=i-1; j>=0; j--)if(d[i]&(1ll<<j))d[i] ^= d[j];
                    for(int j=i+1; j<LG; j++)if(d[j]&(1ll<<i))d[j] ^= d[i];
                    return 1;
                }
                x ^= d[i];
            }
        }
        return 0;
    }

    int queryMax(){
        int res = 0;
        for(int i=LG-1; i>=0; i--)if(res^d[i]>res)res ^= d[i];
        return res;
    }

    int queryMin(){
        for(int i=0; i<LG; i++)if(d[i])return d[i];
        return 0;
    }

    vector<int> getIndependent(){
        vector<int> res;
        for(int i=0; i<LG; i++)if(d[i])res.push_back(d[i]);
        return res;
    }

    int querykth(int k){
        vector<int> vec = getIndependent();
        int sz = vec.size();
        if(k >= (1ll<<sz))return -1;
        int res = 0;
        for(int i=0; i<sz; i++)if(k&(1ll<<i))res ^= vec[i];
        return res;
    }

    friend linearBasis merge(const linearBasis &a, const linearBasis &b){
        linearBasis res = a;
        for(int i=0; i<LG; i++)if(b.d[i])res.add(b.d[i]);
        return res;
    }
};