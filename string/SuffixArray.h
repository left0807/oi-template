
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
    // Note:
    // height[i] = longest common prefix of suffix(sa[i-1]) suffix(sa[i])
    // longest common prefix(sa[i], sa[j]) = min(height[i+1]... height[j])

    // Problem 1
    // find the longest repeated (occurs at least twice) substring (can overlap)
    // max value of (height)

    // Problem 2
    // find the longest repeated substring, cannot overlap
    // binary search on answer k
    // Divide height into blocks [0...i1-1] [i1...i2-1] ...
    // height[i1] < k
    // if(max(sa[0...i]) - min(sa[0...i])) for any bock i >= k
    // => longest common prefix at least k and separate at least k apart

    // Problem 3
    // Find longest substring that repeated at least k times
    // same approac -> divide
    // Then find if exist block with at least k strings

    // Problem 4
    // ***每個字串都是某個後綴的前綴***
    // every suffix(sa[k]) contribute n - sa[k] no. of prefix
    // but height[k] of them are repeated
    // no. of distinct substring = n (n+1) / 2 - sum of height

    // Problem 5
    // Longest palindrome substring
    // find longets repeated substring of s + '# + rev(s)

    // Problem 6
    // consecutive repeated string (e.g. abababa) ab repeated R = 3 times, R is max
    // for each k from 1 to n, see if n%k == 0 and RMQ(height[rank[1]]...height[rank[k+1]]) == n - k
 
    // Problem 7
    // Find the substring with most consecutive repated string R = sqrtababababeipi => S = abababab is the answer
    // Consider repeated string of length L
    // if S consist of at least 2 L, then it must contain 2 of the R[0], R[L], R[2*L] ...
    // so just consider r[L*i] and r[L*(i+1)] can extend to where, let the length be K, ans = max(K/L + 1)

    // Problem 8
    // longest common substring of A+B
    // find Problem 1 of (A + '#' + B), but the suffix are orriginally in different string