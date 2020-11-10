#include <bits/stdc++.h>
using namespace std;

int N , M , K;
vector<int> g[505];
int dp[505][505];
int cost[505][505];
int val[505][505];
const int inf = 1e9 + 10;

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> N >> M >> K;
  for(int i = 1; i <= N; ++i){
    for(int j = 1; j <= M; ++j){
      char a; cin >> a;
      if(a != '0'){
        g[i].push_back(j);
      }
    }
  }
  for(int i = 0; i <= N; ++i)
    for(int j = 0; j <= K; ++j)
      dp[i][j] = val[i][j] = inf;

  for(int i = 1; i <= N; ++i){
    for(int k = 0; k < g[i].size(); ++k)cost[k][k] = 1;
    for(int len = 2; len <= g[i].size(); ++len){
      for(int k = 0; k + len - 1 < g[i].size(); ++k){
        int x = k + len - 1;
        cost[k][x] = g[i][x] - g[i][k] + 1;
      }
    }
    val[i][g[i].size()] = 0;
    for(int len = 0; len < g[i].size(); ++len){
      int L = g[i].size() - len;
      for(int j = 0; j + L - 1 < g[i].size(); ++j){
        val[i][len] = min(val[i][len] , cost[j][j + L - 1]);
      }
    }
  }
  dp[0][0] = 0;
  for(int i = 0; i < N; ++i){
    for(int j = 0; j <= K; ++j){
      if(dp[i][j] == inf)continue;
      if(g[i + 1].size() == 0){
        dp[i + 1][j] = min(dp[i + 1][j] , dp[i][j]);
        continue;
      }
      for(int k = 0; k <= g[i + 1].size(); ++k){
        if(j + k > K)continue;
        dp[i + 1][j + k] = min(dp[i + 1][j + k] , dp[i][j] + val[i + 1][k]);
      }
    }
  }
  int ret = inf;
  for(int i = 0; i <= K; ++i){
    ret = min(dp[N][i] , ret);
  }
  cout << ret << endl;
}
