#include <bits/stdc++.h>
using namespace std;

int BIT[1100][1100];
int s;

void init(int S) {
  for(int i=0 ; i<=S ; i++)
    for(int j=0 ; j<=S ; j++)
      BIT[i][j] = 0;

  s = S;
}

// update BIT
void update(int i , int j , int v){
  i++;
  j++;
  for( ; i<=s ; i += i&-i){ // row
    for(int k =j ; k<=s ; k+=k&-k){ // column
      BIT[i][k] += v; // update value
    }
  }
}

// query BIT
int que(int i , int j){
  if(i <=0 || j <= 0 )return 0; // avoid runtime err
  int res = 0;

  for( ; i ; i-=i&-i){ // row 
    for(int k = j ; k ; k-=k&-k){ // column
      res += BIT[i][k]; // val
    }
  }
  
  return res;
}

// sum of range
int sum(int i , int j , int x , int y){
  i++;j++;x++;y++;
  return que(x,y) - que(x , j-1) - que(i-1 , y) + que(i-1 , j-1); // 2d prefix sum
}


// range update
// build difference array d[i][j]
const int N = 1010;
int t1[N][N], t2[N][N], t3[N][N], t4[N][N];

void add(int x, int y, int z) {
  for (int X = x; X < N; X += X&-X)
    for (int Y = y; Y < N; Y += Y&-Y) {
      t1[X][Y] += z;
      t2[X][Y] += z * x;  // 注意是 z * x 而不是 z * X，后面同理
      t3[X][Y] += z * y;
      t4[X][Y] += z * x * y;
    }
}

void range_add(int xa, int ya, int xb, int yb,
               int z) {  //(xa, ya) 到 (xb, yb) 子矩阵
  add(xa, ya, z);
  add(xa, yb + 1, -z);
  add(xb + 1, ya, -z);
  add(xb + 1, yb + 1, z);
}

int ask(int x, int y) {
  int res = 0;
  for (int i = x; i; i -= i&-i)
    for (int j = y; j; j -= j&-j)
      res += (x + 1) * (y + 1) * t1[i][j] - (y + 1) * t2[i][j] -
             (x + 1) * t3[i][j] + t4[i][j];
  return res;
}

int range_ask(int xa, int ya, int xb, int yb) {
  return ask(xb, yb) - ask(xb, ya - 1) - ask(xa - 1, yb) + ask(xa - 1, ya - 1);
}