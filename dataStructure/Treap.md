#include <bits/stdc++.h>
using namespace std;

mt19937 mt(hash<string>()(":poop:")); // randomizer for heap 
struct node{
    node *l, *r; // subtree 
    int tr, he; // tree key & heap key
    node(int x):tr(x), he(mt()){ // init 
        l = r = nullptr;
    }
}

node* merge(node* a, node* b){ // assumption : a tree key smaller than b 
    if(!a)return b;
    if(!b)return a;
    if(a->he < b->he){ // a head 
        a->r = merge(a->r, b);
        return a;
    }
    b->l = merge(a, b->l); // b head    
    return b;
}

pair<node*, node*> split(node* cur, int k){
    if(!cur){
        return {nullptr, nullptr};
    }
    if(cur->tr <= k){ // split right subtree
        auto [l, r] = split(a->r, k);
        cur->r = l;
        return {cur, r};
    }else{ // split left subtree 
        auto [l, r] = split(b->l, k);
        cur->l = r;
        return {l,cur};
    }
}

node *insert(node* t, int k){
    auto [a, b] = split(t, k);
    return merge(merge(a,new node(k)), b); // order!!! 
}

node *erase(node* t, int k){
    auto [a, b] = split(t, k);
    auto [c, d] = split(a, k-1);
    return meger(c,b);
}