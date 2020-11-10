#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

string str[45];
int A[45][45];
int N;
ll DP[45][45][45][45][2];

/*
DP[a][b][c][d][0] = # ways to connect points in [a , b] U [c , d] into a tree
and there is exactly one connetion from [a , b] to [c , d].
DP[a][b][c][d][1] = # ways to connect points in [a , b] U [c , d] into a forest.

DP[a][b][c][d][0] = DP[a][p - 1][p + 1][b][1] * DP[c][q - 1][q + 1][d] * [A[p][q] == 1]
// enumerate the line connecting [a , b] and [c , d]
// the remaining connections must be from [a , b] to [c , d]
// [a , p - 1] U [p + 1 , b] and [c , q - 1] U [q + 1 , d] must form forests (or a tree)

DP[a][b][c][d][1] = DP[a][p][q][d][0] * DP[p + 1][b][c][q - 1][1]
// forests is must have at least one tree, so we enumerate the range where we get a tree

*/

ll solve(int a , int b , int c , int d , int x){
  if(x == 0){ // tree
    if(a > b || c > d)return 0;
  }
  else{ // forest
    if((a > b) && (c > d))return 1;
    if((a > b) ^ (c > d))return 0;
  }
  ll& ret = DP[a][b][c][d][x];
  if(~ret)return ret;
  ret = 0;
  if(x == 0){
    for(int p = a; p <= b; ++p){
      for(int q = c; q <= d; ++q){
        if(A[p][q]){
          ret += solve(a , p - 1 , p + 1 , b , 1) * solve(c , q - 1 , q + 1 , d , 1);
        }
      }
    }
  }
  else{
    for(int p = a; p <= b; ++p){
      for(int q = c; q <= d; ++q){
        ret += solve(a , p , q , d , 0) * solve(p + 1 , b , c , q - 1 , 1);
      }
    }
  }
  return ret;
}

int main(){
  cin >> N;
  for(int i = 1; i <= 2 * N; ++i){
    cin >> str[i];
  }
  for(int i = 1; i <= 2 * N; ++i){
    for(int j = 0; j < 2 * N; ++j){
      A[i][j + 1] = str[i][j] == '1';
    }
  }
  memset(DP , -1 , sizeof(DP));
  ll ret = 0;
  for(int i = 2; i <= 2 * N; ++i){
    if(A[1][i]){
      ret += solve(2 , i - 1 , i + 1 , 2 * N , 1);
    }
  }
  cout << ret << endl;
}
