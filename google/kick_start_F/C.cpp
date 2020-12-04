#include <iostream>
#include <vector>
#include <string.h>
#include <algorithm>
#include <cstdio>
using namespace std;
typedef long long ll;

const int maxn = 1e5 + 10;
vector<int> g[maxn];
ll dp[maxn][4];
ll val[maxn];
int N;

void DFS(int v , int p){
  dp[v][0] = val[v];
  dp[v][1] = val[v];
  ll S = 0;
  for(int u : g[v]){
    if(u != p){
      DFS(u , v);
      dp[v][0] += max(dp[u][0] , dp[u][1]);
      dp[v][1] += max(dp[u][0] , max(dp[u][2] , dp[u][3]));
      dp[v][3] += max(dp[u][2] , dp[u][3]);
      S += max(dp[u][0] , max(dp[u][2] , dp[u][3]));
    }
  }
  for(int u : g[v]){
    if(u != p){
      ll c = val[v] + S - max(dp[u][0] , max(dp[u][2] , dp[u][3])) + dp[u][0];
      dp[v][2] = max(dp[v][2] , c);
    }
  }
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int T;
  cin >> T;
  for(int t = 1; t <= T; ++t){
    cin >> N;
    for(int i = 1; i <= N; ++i)cin >> val[i] , g[i].clear();
    memset(dp , 0 , sizeof(dp));
    for(int i = 1; i < N; ++i){
      int x , y;
      cin >> x >> y;
      g[x].push_back(y);
      g[y].push_back(x);
    }
    DFS(1 , 1);
    cout << "Case #" << t << ": " << max(dp[1][0] , max(dp[1][3] , dp[1][2])) << endl;
  }
}
