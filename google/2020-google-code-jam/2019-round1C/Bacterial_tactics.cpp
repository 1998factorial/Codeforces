#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl
using namespace std;
typedef long long ll;
typedef pair<int , int> ii;

int T , R , C;

char grid[20][20];
int DP[20][20][20][20];
int sg[20][20][20][20];

bool check(int x1 , int y1 , int x2 , int y2){
  for(int i = x1; i <= x2; ++i)
    for(int j = y1; j <= y2; ++j)
      if(grid[i][j] == '#')
        return 0;
  return 1;
}

int solve(int x1 , int y1 , int x2 , int y2){
  if(x1 > x2 || y1 > y2)return 0;
  int& ret = sg[x1][y1][x2][y2];
  if(~ret)return ret;
  set<int> vis;
  for(int i = x1; i <= x2; ++i){
    for(int j = y1; j <= y2; ++j){
      if(grid[i][j] != '#'){
        if(check(i , y1 , i , y2)){
          int s1 = solve(x1 , y1 , i - 1 , y2);
          int s2 = solve(i + 1 , y1 , x2 , y2);
          DP[x1][y1][x2][y2] += (s1 ^ s2) == 0;
          vis.insert(s1 ^ s2);
        }
        if(check(x1 , j , x2 , j)){
          int s1 = solve(x1 , y1 , x2 , j - 1);
          int s2 = solve(x1 , j + 1 , x2 , y2);
          DP[x1][y1][x2][y2] += (s1 ^ s2) == 0;
          vis.insert(s1 ^ s2);
        }
      }
    }
  }
  // get mex
  for(int i = 0; ; ++i){
    if(!vis.count(i)){
      return ret = i;
    }
  }
  return ret = 0;
}

void answer(){
  for(int i = 1; i <= R; ++i){
    for(int j = 1; j <= C; ++j){
      cin >> grid[i][j];
    }
  }
  memset(sg , -1 , sizeof(sg));
  memset(DP , 0 , sizeof(DP));
  solve(1 , 1 , R , C);
  cout << DP[1][1][R][C] << endl;
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> T;
  for(int t = 1; t <= T; ++t){
    cin >> R >> C;
    cout << "Case #" << t << ": ";
    answer();
  }
}
