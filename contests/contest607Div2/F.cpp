#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
typedef long long ll;
typedef pair<ll , ll> ii;
const ll inf = 1e18;
const int maxn = 3e3 + 10;
vector<int> g[maxn];
ii dp[maxn][maxn] , pre[maxn];
ll B[maxn] , W[maxn];
int tsize[maxn];
int N , M;

void DFS(int v , int p){
  tsize[v] = 1;
  dp[v][1] = make_pair(0 , W[v] - B[v]);
  for(int u : g[v]){
    if(u == p)continue;
    DFS(u , v);
    for(int i = 1; i <= tsize[v] + tsize[u]; ++i)pre[i] = make_pair(0 , -inf);
    for(int i = 1; i <= tsize[v]; ++i){
      for(int j = 1; j <= tsize[u]; ++j){
        pre[i + j] = max(pre[i + j] , make_pair(dp[v][i].first + dp[u][j].first + (ll)(dp[u][j].second > 0) , dp[v][i].second));
        pre[i + j - 1] = max(pre[i + j - 1] , make_pair(dp[v][i].first + dp[u][j].first , dp[u][j].second + dp[v][i].second));
      }
    }
    tsize[v] += tsize[u];
    for(int i = 1; i <= tsize[v]; ++i)dp[v][i] = pre[i];
  }
}

int main(){
  int T; cin >> T;
  for(int t = 1; t <= T; ++t){
    cin >> N >> M;
    for(int i = 1; i <= N; ++i){
      g[i].clear(); cin >> B[i];
    }
    for(int i = 1; i <= N; ++i){
      cin >> W[i];
    }
    for(int i = 1; i < N; ++i){
      int x , y; cin >> x >> y;
      g[x].push_back(y);
      g[y].push_back(x);
    }
    DFS(1 , 1);
    int ret = dp[1][M].first + (dp[1][M].second > 0);
    cout << ret << endl;
  }
}
