#include <iostream>
using namespace std;
typedef long long ll;

/*
  vertices are assigned either 1 or 0 , edges are assigned value depends on the vertices incident to it
  find # of ways st we have at at least 1 edge = 1 and 2 and 0
*/

int N , M;
int g[45][45];
int deg[45];
int col[45];
bool vis[45];
ll adj_mask[45];
ll dp[1 << 20];

void dfs(int v){
  vis[v] = true;
  for(int i = 1; i <= N; ++i){
    if(g[v][i] && !vis[i]){
      dfs(i);
    }
  }
}

void dfs2(int v , int c){
  vis[v] = true;
  col[v] = c;
  for(int i = 1; i <= N; ++i){
    if(g[v][i] && !vis[i]){
      dfs2(i , 1 - c);
    }
  }
}

bool Bipartite(){
  for(int i = 1; i <= N; ++i){
    vis[i] = false;
  }
  for(int i = 1; i <= N; ++i){
    if(!vis[i]){
      dfs2(i , 1);
    }
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

ll countIndependentSet(){
  ll ret = 0;
  int m1 = N > 20 ? 20 : N;
  int m2 = N - m1;
  for(int i = 0; i < (1 << 20); ++i)dp[i] = 0;
  for(int i = 0; i < (1 << m1); ++i){
    ll mask = 0;
    bool ok = true;
    for(int j = 0; j < m1; ++j){
      if((i & (1 << j)) == 0)continue; //if not in this subset
      if(mask & (1 << j))ok = false;
      mask |= (1 << j) | adj_mask[j]; //all nodes that are incidented to this subset
    }
    if(ok)
      ++dp[mask >> m1]; //# of independent subset in S1 st they are incident to these set of vertices from S2
  }
  for(int i = 0; i < m2; ++i)
    for(int j = 0; j < (1 << m2); ++j)
      if((1 << i) & j)
        dp[j] += dp[j ^ (1 << i)];
  //for(int j = 0; j < (1 << m2); ++j)printf("dp[%d] = %lld\n" , j , dp[j]);
  for(int i = 0; i < (1 << m2); ++i){ // find all independent subset in S2
    ll mask = 0;
    bool ok = true;
    for(int j = m1; j < N; ++j){
      if((i & (1 << (j - m1))) == 0)continue; // not in this subset
      if(mask & (1ll << j))ok = false;
      mask |= (1ll << j) | adj_mask[j];
    }
    if(ok)
      ret += dp[i ^ ((1 << m2) - 1)]; //append by the number of subsets from S2 st that are only incident to the compliment of i
  }
  return ret;
}

int main(){
  cin >> N >> M;
  for(int i = 1; i <= N; ++i){
    for(int j = 1; j <= N; ++j){
      g[i][j] = 0;
    }
    deg[i] = adj_mask[i] = 0;
  }
  for(int i = 1; i <= M; ++i){
    int x , y;
    cin >> x >> y;
    g[x][y] = g[y][x] = 1;
    ++deg[x];
    ++deg[y];
    adj_mask[x - 1] |= (1ll << (y - 1));
    adj_mask[y - 1] |= (1ll << (x - 1));
  }
  ll tot = 1ll << N;
  int cnt = 0 , isolate = 0;
  for(int i = 1; i <= N; ++i)vis[i] = false , isolate += (deg[i] == 0);
  for(int i = 1; i <= N; ++i){
    if(!vis[i]){
      ++cnt;
      dfs(i);
    }
  }
  cout << tot - 2ll * countIndependentSet() - (1ll << cnt) + 2ll * (1ll << isolate) + (Bipartite() ? 1ll << cnt : 0) - (M == 0 ? 1ll << N : 0) << endl;
  return 0;
}
