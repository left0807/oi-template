#include <bits/stdc++.h>
using namespace std;

// lazy tag pq 
struct que{
    priority_queue<int>x, y;
    inline void push(int a){x.push(a);}
    inline void del(int a){y.push(a);}
    inline int size(){return x.size()-y.size();}
    inline void pop(){
        while(y.size()&&x.top()==y.top())x.pop(),y.pop();
        x.pop();
    }
    inline int top(){
        while(y.size()&&x.top()==y.top())x.pop(),y.pop();
        return x.top();
    }
    inline int top2(){
        int a = top();
        pop();
        int b = top();
        push(a);
        return b;
    }
};
