#include <iostream>
#include <cstring>
using namespace std;

const int maxn = 20;
const int inf = 1 << 28;
int N , M;
int dp[1 << maxn]; //O(2 ^ m)
bool vis[1 << maxn];
int g[maxn][maxn];
string a;

int solve(int state , int pos){
  if(vis[state]){
    return dp[state];
  }
  int ret = inf;
  for(int i = 0; i < M; ++i){
    if(state & (1 << i)){
      int cnt = 0;
      for(int j = 0; j < M; ++j){
        if(j != i){
          cnt += g[i][j];
          g[j][i] *= -1;
        }
      }
      int tmp = cnt * pos + solve(state ^ (1 << i) , pos - 1);
      if(ret > tmp)ret = tmp;
      for(int j = 0; j < M; ++j){
        if(j != i){
          g[j][i] *= -1;
        }
      }
    }
  }
  vis[state] = true;
  return dp[state] = ret;
}

int main(){
  cin >> N >> M;
  cin >> a;
  for(int i = 0; i < M; ++i){
    for(int j = 0; j < M; ++j){
      g[i][j] = 0;
    }
  }
  for(int i = 1; i < N; ++i){
    if(a[i - 1] != a[i]){
      int x , y;
      x = a[i - 1] - 'a';
      y = a[i] -'a';
      ++g[x][y];
      ++g[y][x];
    }
  }
  for(int i = 0; i < (1 << M); ++i){
    vis[i] = false;
    dp[i] = inf;
  }
  for(int i = 0; i < M; ++i){
    dp[(1 << i)] = 0;
    vis[(1 << i)] = true;
  }
  printf("%d\n" , solve((1 << M) - 1, M - 1));
  return 0;
}
