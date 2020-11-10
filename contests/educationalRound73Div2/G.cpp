#include <iostream>
#include <algorithm>
#include <cstdio>
#include <vector>
using namespace std;
typedef long long ll;

int g[45][45];
ll deg[45];
int N , M;
bool vis[45];
int col[45];
ll incident_mask[45];
ll dp[1 << 20];

/*
  #(at least 1 "1" edge & at least 1 "0" edge & at least 1 "2" edge)
  = total - #(no "1" edge) - #(no "0" edge) - #(no "2" edge)
  + #(no "1" and "0") + #(no "1" and "2") + #(no "0" and "2")
  - #(no "1" and "0" and "2")

  total = 2 ^ N
  #(no "1" edge) = 2 ^ (number of connected component)
  #(no "2" edge) = # of independent set
  #(no "0" edge) = # of independent set
  #(no "1" and "0") = 2 ^ (number of isolated points (deg[i] = 0))
  #(no "1" and "2") = 2 ^ (number of isolated points (deg[i] = 0))
  #(no "2" and "0") = if bipartite -> 2 ^ (number of connected component) else -> 0
  #(no "1" and "0" and "2") = if m = 0 -> 2 ^ N , else -> 0
*/

void dfs2(int v , int c){
  vis[v] = true;
  col[v] = c;
  for(int i = 1; i <= N; ++i){
    if(!vis[i] && g[v][i]){
      dfs2(i , 1 - c);
    }
  }
}

bool Bipartite(){
  for(int i = 1; i <= N; ++i)vis[i] = false , col[i] = 0;
  for(int i = 1; i <= N; ++i){
    if(!vis[i])
      dfs2(i , 1);
  }
  for(int i = 1; i <= N; ++i){
    for(int j = 1; j <= N; ++j){
      if(g[i][j] && col[i] == col[j]){
        return false;
      }
    }
  }
  return true;
}

void dfs(int v){
  vis[v] = true;
  for(int i = 1; i <= N; ++i){
    if(!g[v][i])continue;
    if(!vis[i]){
      dfs(i);
    }
  }
}

ll countIndependentSet(){
  ll ret = 0;
  int m1 = min(20 , N);
  int m2 = N - m1;
  for(int i = 0; i < (1 << 20); ++i)dp[i] = 0;
  for(int i = 0; i < (1 << m1); ++i){
    ll cur_mask = 0;
    bool check = true;
    for(int j = 0; j < m1; ++j){
      if((i & (1 << j)) == 0)continue;
      if(cur_mask & (1 << j))check = false;
      cur_mask |= (1 << j) | incident_mask[j];
    }
    if(check)++dp[cur_mask >> m1]; // not choosing this set of vertices in S2
  }
  for(int i = 0; i < m2; ++i){
    for(int j = 0; j < (1 << m2); ++j){
      if((1 << i) & j){
        dp[j] += dp[j ^ (1 << i)];
      }
    }
  }
  for(int i = 0; i < (1 << m2); ++i){
    ll cur_mask = 0;
    bool check = true;
    for(int j = m1; j < N; ++j){
      if((i & (1 << (j - m1))) == 0)continue;
      if(cur_mask & (1ll << j))check = false;
      cur_mask |= (1ll << j) | incident_mask[j];
    }
    if(check){
      ret += dp[i ^ ((1 << m2) - 1)];
    }
  }
  return ret;
}

int main(){
  cin >> N >> M;
  for(int i = 1; i <= N; ++i){
    for(int j = 1; j <= N; ++j){
      g[i][j] = 0;
    }
    deg[i] = 0;
    incident_mask[i] = 0;
  }
  for(int i = 1; i <= M; ++i){
    int x , y;
    cin >> x >> y;
    g[x][y] = 1;
    g[y][x] = 1;
    ++deg[x];
    ++deg[y];
    incident_mask[x - 1] |= (1ll << (y - 1));
    incident_mask[y - 1] |= (1ll << (x - 1));
  }
  ll tot = (1ll << N);
  // count connected component
  int cnt = 0;
  for(int i = 1; i <= N; ++i)vis[i] = false;
  for(int i = 1; i <= N; ++i){
    if(!vis[i]){
      ++cnt;
      dfs(i);
    }
  }
  bool isBipartite = Bipartite();
  int isolated = 0;
  for(int i = 1; i <= N; ++i){
    isolated += (deg[i] == 0);
  }
  ll ret = tot - (1ll << cnt) - 2ll * countIndependentSet() + 2ll * (1ll << isolated) + (isBipartite ? (1ll << cnt) : 0) - (M == 0 ? 1ll << N : 0);
  cout << ret << endl;
  return 0;
}
