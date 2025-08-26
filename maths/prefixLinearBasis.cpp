#include <bits/stdc++.h>
using namespace std;

#define int long long 

const int N = 2e5+5;
const int LG = 60;

struct linearBasis{
    int d[LG], pos[LG], dc[LG];

    linearBasis() {clear();}

    void clear(){
        memset(d, 0, sizeof d);
        memset(dc, 0, sizeof dc);
        memset(pos, 0, sizeof pos);
    }

    bool add(int x, int p){ // edit the add
        for(int i=LG-1; i>=0; i--){
            if((x>>i)&1){
                if(!d[i]){
                    d[i] = x;
                    pos[i] = p;
                    return 1;
                }
                if(pos[i] < p){
                    swap(pos[i], p);
                    swap(d[i], x);
                }
                x ^= d[i];
            }
        }
        return 0;
    }

	void rebuild(){
		memcpy(dc,d,sizeof d);
        for(int i=LG-1; i>=0; i--){
			if(!dc[i])continue;
            for(int j=i-1; j>=0; j--){
                if(dc[i] & (1ll<<j))dc[i] ^= dc[j];
            }
        }
	}

    int querykth(int k){
        rebuild();
        vector<int>vec;
        for(int i=0; i<LG; i++)if(dc[i])vec.push_back(dc[i]);
        int sz = vec.size();
        if(k >= (1ll<<sz))return -1;
        int res = 0;
        for(int i=0; i<sz; i++)if(k&(1ll<<i))res ^= vec[i];
        return res;
    }
};


struct prefixLinearBasis{
    vector<linearBasis> lbs;
    prefixLinearBasis() {lbs.emplace_back();}
    
    void add(int x){
        linearBasis lb = lbs.back();
        lb.add(x,lbs.size());
        lbs.emplace_back(lb);
    }

    int queryMax(int l, int r){
        int res = 0;
        for(int i=LG-1; i>=0; i--){
            if(lbs[r].pos[i]<l)continue;
            if((res^lbs[r].d[i])>res)res ^= lbs[r].d[i];
        }
        return res;
    }

    int queryMin(int l, int r){
        for(int i=0; i<LG; i++){
            if(lbs[r].pos[i]<l)continue;
            if(lbs[r].d[i])return lbs[r].d[i];
        }
        return 0;
    }
}plb;