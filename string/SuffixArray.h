
template<typename T>
class SuffixArray{
public:

    vector<T> s;
    vector<int> sa, rk, oldrk;
    int n;

    SuffixArray(){}
    SuffixArray(vector<T> _s){
        n = _s.size();
        s = _s;
        s.resize(2*n);
        sa.assign(2*n, -1), rk.assign(2*n, -1), oldrk.assign(2*n, -1);
        fast_sort();
    }

    void fast_sort(){
        vector<int> cnt(n), id(n);

        for(int i = 0; i < n; i++) sa[i] = i, oldrk[i] = s[i];
        sort(sa.begin(), sa.begin()+n, [&](int x, int y){ return oldrk[x] < oldrk[y]; });
        
        rk[sa[0]] = 0;
        for(int i = 0; i + 1 < n; i++){
            if(oldrk[sa[i]] == oldrk[sa[i+1]]) rk[sa[i+1]] = rk[sa[i]];
            else rk[sa[i+1]] = rk[sa[i]] + 1;
        }

        int m = rk[sa[n-1]], p;

        for(int w = 1; w < n; w *= 2, m = p){
            int cur = 0;
            for(int i = n - w; i < n; i++) id[cur++] = i;
            for(int i = 0; i < n; i++) if(sa[i] >= w){
                id[cur++] = sa[i] - w;
            }

            for(int i = 0; i < n; i++) cnt[i] = 0;
            for(int i = 0; i < n; i++) cnt[rk[i]]++;
            for(int i = 1; i <= m; i++) cnt[i] += cnt[i-1];
            for(int i = n-1; i >= 0; i--) sa[--cnt[rk[id[i]]]] = id[i];

            for(int i = 0; i < n; i++) oldrk[i] = rk[i];
            rk[sa[0]] = p = 0;
            for(int i = 0; i+1 < n; i++){
                if(oldrk[sa[i]] == oldrk[sa[i+1]] && oldrk[sa[i] + w] == oldrk[sa[i+1] + w]){
                    rk[sa[i+1]] = p;
                } else{
                    rk[sa[i+1]] = ++p;
                }
            }

            if(p == n) break;
        }
    }

    vector<int> get_height(){
        vector<int> h(n, 0);
        for(int i = 0, k = 0; i < n; i++){
            if(rk[i] == 0) continue;
            if(k) k--;
            while(s[i+k] ==  s[sa[rk[i] - 1] + k]) k++;
            h[rk[i]] = k;
        }
        return h;
    }
};
