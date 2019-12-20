#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
typedef long long ll;
typedef pair<ll , ll> ii;
/*
  dp[x][i] = (maximal number of winning region exclueding the part where x is in ,
  maximal advantage of the part where x is in)
  greedy observation + cool complexity analyze
*/
const int maxn = 3e3 + 10;
const ll inf = 1e18;
vector<int> g[maxn];
ii dp[maxn][maxn] , pre[maxn];
int N , M;
ll B[maxn] , W[maxn] , tsize[maxn];

void DFS(int x , int p){
  tsize[x] = 1;
  dp[x][1] = make_pair(0 , W[x] - B[x]);
  for(int y : g[x]){
    if(y != p){
      DFS(y , x);
      for(int i = 1; i <= tsize[x] + tsize[y]; ++i)pre[i] = make_pair(0 , -inf);
      for(int i = 1; i <= tsize[x]; ++i){
        for(int j = 1; j <= tsize[y]; ++j){
          // y does not join x
          pre[i + j] = max(
            pre[i + j] ,
            make_pair(dp[x][i].first + dp[y][j].first + (dp[y][j].second > 0) , dp[x][i].second)
          );
          // y join x
          pre[i + j - 1] = max(
            pre[i + j - 1] ,
            make_pair(dp[x][i].first + dp[y][j].first , dp[x][i].second + dp[y][j].second)
          );
        }
      }
      tsize[x] += tsize[y];
      for(int i = 1; i <= tsize[x]; ++i)dp[x][i] = pre[i];
    }
  }
}

int main(){
  int T; cin >> T;
  for(int t = 1; t <= T; ++t){
    cin >> N >> M;
    for(int i = 1; i <= N; ++i)cin >> B[i] , g[i].clear();
    for(int i = 1; i <= N; ++i)cin >> W[i];
    for(int i = 1; i < N; ++i){
      int x , y; cin >> x >> y;
      g[x].push_back(y);
      g[y].push_back(x);
    }
    DFS(1 , 1);
    cout << dp[1][M].first + (ll)(dp[1][M].second > 0) << endl;
  }
}
