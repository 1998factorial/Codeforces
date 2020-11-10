#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
using namespace std;

const int maxn = 3e5 + 10;
int N , Q;
vector<int> g[maxn];
int deg[maxn];
int dp[maxn][2];
//0 -> ans at subtree rooted at v , 1 -> connected to its parent
/*
non leaf node can be adj to at most 2 non leaf nodes
*/

void DFS(int v , int p){
  vector<int> ans;
  dp[v][0] = deg[v] + 1;
  for(int u : g[v]){
    if(u == p)continue;
    DFS(u , v);
    dp[v][0] = max(dp[v][0] , dp[u][0]);
    ans.push_back(dp[u][1]);
    dp[v][1] = max(dp[v][1] , dp[u][1] + deg[v] - 1);
  }
  sort(ans.begin() , ans.end());
  int t = deg[v] + 1;
  for(int i = ans.size() - 1; i >= 0 && i >= ans.size() - 2; --i){
    t += ans[i];
  }
  dp[v][0] = max(dp[v][0] , t);
}

int main(){
  cin >> Q;
  for(int q = 1; q <= Q; ++q){
    cin >> N;
    for(int i = 1; i <= N; ++i)g[i].clear() , deg[i] = 0 , dp[i][0] = dp[i][1] = 0;
    for(int i = 1; i <= N - 1; ++i){
      int x , y;
      cin >> x >> y;
      g[x].push_back(y);
      g[y].push_back(x);
      ++deg[x];
      ++deg[y];
    }
    int start = 1;
    for(int i = 1; i <= N; ++i){
      if(deg[i] != 1){
        start = i;
        break;
      }
    }
    DFS(start , 0);
    cout << dp[start][0] << endl;
  }
}
