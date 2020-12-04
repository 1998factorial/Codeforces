#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl
using namespace std;
typedef long long ll;
typedef pair<int , int> ii;

int T , R , C;
int DP[20][20][20][20];
int SG[20][20][20][20];
char g[20][20];

/*
  when placing either H or V , we can divide our current board into 2 seperate boards
  thus, creating 2 individual games
  To check if we can win both these 2 individual games, we just need to take the xor of
  the SG value of these 2 games. We can win iff the xor sum is 0.
  The SG value of current game state is mex of SG values of all possible reachable game states
*/

int mex(unordered_map<int , int>& vis){
  int ret = 0;
  for(int i = 0; i <= vis.size(); ++i){
    if(vis[i] == 0){
      ret = i;
      break;
    }
  }
  return ret;
}

int check(int x1 , int y1 , int x2 , int y2){
  for(int i = x1; i <= x2; ++i){
    for(int j = y1; j <= y2; ++j){
      if(g[i][j] == '#')return 0;
    }
  }
  return 1;
}

int solve(int x1 , int y1 , int x2 , int y2){
  if(x1 > x2 || y1 > y2 || x1 < 1 || y1 < 1 || x2 > R || y2 > C)return 0; //lost
  int& ret = SG[x1][y1][x2][y2];
  if(~ret)return ret; // already computed
  unordered_map<int , int> vis;
  for(int i = x1; i <= x2; ++i){
    for(int j = y1; j <= y2; ++j){
      if(g[i][j] == '#')continue;
      if(check(i , y1 , i , y2)){ // can place H at (i , j)
        int sg1 = solve(x1 , y1 , i - 1 , y2);
        int sg2 = solve(i + 1 , y1 , x2 , y2);
        if((sg1 ^ sg2) == 0)++DP[x1][y1][x2][y2]; // means this is a winning move
        ++vis[sg1 ^ sg2];
      }
      if(check(x1 , j , x2 , j)){ // can place V at (i , j)
        int sg1 = solve(x1 , y1 , x2 , j - 1);
        int sg2 = solve(x1 , j + 1 , x2 , y2);
        if((sg1 ^ sg2) == 0)++DP[x1][y1][x2][y2];
        ++vis[sg1 ^ sg2];
      }
    }
  }
  return ret = mex(vis);
}

void answer(){
  for(int i = 1; i <= R; ++i)
    for(int j = 1; j <= C; ++j)
      cin >> g[i][j];
  memset(DP , 0 , sizeof(DP));
  memset(SG , -1 , sizeof(SG));
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
