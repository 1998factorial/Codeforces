#include <bits/stdc++.h>
using namespace std;

int N , M , K;
vector<int> g[505];
int dp[505][505];
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
      dp[i][j] = inf;
  dp[0][0] = 0;
  for(int i = 0; i < N; ++i){
    for(int j = 0; j <= K; ++j){
      if(dp[i][j] == inf)continue;
      for(int k = 0 , l = 0 , r = g[i + 1].size() - 1; k <= g[i + 1].size(); ++k){ // skip k classes at i + 1 day
        if(j + k > K)break;
        int cost = (l <= r) ? g[i + 1][r] - g[i + 1][l] + 1 : 0;
        dp[i + 1][j + k] = min(dp[i + 1][j + k] , dp[i][j] + cost);
        int c1 = inf , c2 = inf;
        if(l + 1 <= r)
          c1 = min(c1 , g[i + 1][r] - g[i + 1][l + 1] + 1);
        if(r - 1 >= l)
          c2 = min(c2 , g[i + 1][r - 1] - g[i + 1][l] + 1);
        //cout << l << " " << r << " " << c1 << " " << c2 << endl;
        if(c1 < c2)++l;
        else --r;
      }
    }
  }
  for(int i = 0; i <= N; ++i){
    for(int j = 0; j <= K; ++j){
      if(dp[i][j] < inf)printf("dp[%d][%d] = %d\n" , i , j , dp[i][j]);
    }
  }
  int ret = inf;
  for(int i = 0; i <= K; ++i){
    ret = min(dp[N][i] , ret);
  }
  cout << ret << endl;
}
