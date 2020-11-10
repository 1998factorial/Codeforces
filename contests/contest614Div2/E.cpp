#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;

const int maxn = 3e3 + 10;
int N;
vector<int> g[maxn];
int sub[maxn][maxn] , fa[maxn][maxn];
ll dp[maxn][maxn];

void DFS1(int anc , int v , int p){
  sub[anc][v] = 1;
  for(int u : g[v]){
    if(u != p){
      fa[anc][u] = v;
      DFS1(anc , u , v);
      sub[anc][v] += sub[anc][u];
    }
  }
}

ll DFS2(int v , int u){
  if(v == u)
    return 0;
  if(dp[v][u] != -1)
    return dp[v][u];
  dp[v][u] = (ll)sub[v][u] * sub[u][v] + max(DFS2(v , fa[v][u]) , DFS2(fa[u][v] , u));
  return dp[v][u];
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> N;
  for(int i = 1; i <= N - 1; ++i){
    int u , v;
    cin >> u >> v;
    g[u].push_back(v);
    g[v].push_back(u);
  }
  for(int i = 1; i <= N; ++i){
    fa[i][i] = i;
    DFS1(i , i , i);
  }
  ll ret = 0;
  for(int i = 1; i <= N; ++i){
    for(int j = 1; j <= N; ++j){
      dp[i][j] = -1;
    }
  }
  for(int i = 1; i <= N; ++i){
    for(int j = 1; j <= N; ++j){
      ret = max(ret , DFS2(i , j));
    }
  }
  cout << ret << endl;
}
