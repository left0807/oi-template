#include <bits/stdc++.h>
using namespace std;

vector<int> prefix_func(string s){
    int n = s.length();
    vector<int>pi(n);
    for(int i=1, m=0; i<n; i++){
        while(m > 0 && s[i] != s[m])m = pi[m-1];
        if(s[i] == s[m])m++;
        pi[i] = m;  
    }
    return pi;
}

vector<int> kmp(string s, string t){
    vector<int> pi = prefix_func(t);
    vector<int> res;
    int n = s.length(), n2 = t.length();
    for(int i=0, m=0; i<n; i++){
        while(m > 0 && s[i] != t[m])m = pi[m-1];
        if(s[i] == t[m])m++;
        if(m==n2){
            res.push_back(i-n2+1);
            m = pi[m-1];
        }
    }
    return res;
}