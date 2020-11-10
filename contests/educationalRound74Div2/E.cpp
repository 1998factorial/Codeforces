#include <iostream>
#include <cmath>
#include <cstring>
#include <vector>
using namespace std;

int n , m;
string a;
int g[26][26];
int dp[1 << 20][20]; // minimal cost st is placed at the end
bool vis[1 << 20][20];
const int inf = 1 << 28;

int solve(int state , int alpha , int pos){ // O(m * m * 2 ^ m)
  if(pos < 0)return 0;
  if(vis[state][alpha]){
    return dp[state][alpha];
  }
  vis[state][alpha] = true;
  int ret = inf;
  int acc = 0;
  for(int i = 0; i < m; ++i){
    acc += g[alpha][i];
    g[i][alpha] *= -1;
  }
  int next = state ^ (1 << alpha);
  for(int i = 0; i < m; ++i){
    if((next & (1 << i))){
      int tmp = acc * pos + solve(next , i , pos - 1);
      if(ret > tmp)ret = tmp;
    }
  }
  for(int i = 0; i < m; ++i){
    g[i][alpha] *= -1;
  }
  return dp[state][alpha] = ret;
}

int main(){
  scanf("%d %d", &n , &m);
  for(int i = 0; i < m; ++i){
    for(int j = 0; j < m; ++j){
      g[i][j] = 0;
    }
  }
  cin >> a;
  for(int i = 1; i < n; ++i){
    int x = a[i] - 'a';
    int y = a[i - 1] - 'a';
    if(x == y)continue;
    ++g[x][y];
    ++g[y][x];
  }

  for(int i = 0; i < m; ++i){
    for(int j = 0; j < (1 << m); ++j){
      dp[j][i] = inf;
      vis[j][i] = false;
    }
  }
  for(int i = 0; i < m; ++i){
    dp[(1 << i)][i] = 0;
    vis[(1 << i)][i] = true;
  }
  int ret = inf;
  for(int i = 0; i < m; ++i){
    int tmp = solve((1 << m) - 1 , i , m - 1);
    if(ret > tmp)ret = tmp;
  }
  cout << ret << endl;
  return 0;
}
