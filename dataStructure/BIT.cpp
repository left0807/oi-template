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
  for( ; i<=s ; i += (i&-i)){ // row
    for(int k =j ; k<=s ; k+=(k&-k)){ // column
      BIT[i][k] += v; // update value
    }
  }
}

// query BIT
int que(int i , int j){
  if(i <=0 || j <= 0 )return 0; // avoid runtime err
  int res = 0;

  for( ; i ; i-=(i&-i)){ // row 
    for(int k = j ; k ; k-=(k&-k)){ // column
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