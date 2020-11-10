#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;
const int maxn = 1e5 + 10;
ll dp[maxn][3][3];
bool vis[maxn][3][3];
bool seen[maxn];
ll c[3][maxn];
int N;
vector<int> g[maxn];
int col[maxn];
ll inf = 1ll << 55;
int deg[maxn];

ll DFS(int v , int i , int j){
  seen[v] = true;
  if(vis[v][i][j]){
    return dp[v][i][j];
  }
  ll ret = c[i][v];
  for(int u : g[v]){
    if(seen[u])continue;
    ll ans = DFS(u , 3 - j - i , i);
    ret += ans;
  }
  vis[v][i][j] = true;
  return dp[v][i][j] = ret;
}

void init(){
  for(int i = 0; i <= N; ++i){
    seen[i] = false;
    for(int j = 0; j < 3; ++j){
      for(int k = 0; k < 3; ++k){
        dp[i][j][k] = inf;
        vis[i][j][k] = false;
      }
    }
  }
}

void DFS2(int v , int i , int j){
  seen[v] = true;
  col[v] = i + 1;
  for(int u : g[v])
    if(!seen[u])
      DFS2(u , 3 - i - j , i);
}

int main(){
  cin >> N;
  for(int i = 1; i <= N; ++i)cin >> c[0][i];
  for(int i = 1; i <= N; ++i)cin >> c[1][i];
  for(int i = 1; i <= N; ++i)cin >> c[2][i];
  for(int i = 1; i <= N; ++i)deg[i] = 0;
  for(int i = 1; i < N; ++i){
    int x , y;
    cin >> x >> y;
    g[x].push_back(y);
    g[y].push_back(x);
    deg[x]++;
    deg[y]++;
    if(deg[x] > 2 || deg[y] > 2){
      cout << -1 << endl;
      return 0;
    }
  }
  init();
  ll ret = inf;
  int x = 0 , y = 0;
  for(int i = 0; i < 3; ++i){
    for(int j = 0; j < 3; ++j){
      for(int k = 1; k <= N; ++k)seen[k] = false;
      if(i == j)continue;
      ll ans = DFS(1 , i , j);
      if(ret > ans){
        ret = ans;
        x = i;
        y = j;
      }
    }
  }
  if(ret >= inf){
    cout << -1 << endl;
    return 0;
  }
  cout << ret << endl;
  for(int i = 1; i <= N; ++i)seen[i] = false;
  DFS2(1 , x , y);
  for(int i = 1; i <= N; ++i){
    cout << col[i] << " ";
  }
  cout << endl;
  return 0;
}
