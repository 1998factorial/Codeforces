#include <iostream>
#include <algorithm>
#include <string.h>
using namespace std;

int dp[105][105][105];
int a[105];
int inf = 1e9;
int N , K;

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int T;
  cin >> T;
  for(int t = 1; t <= T; ++t){
    cin >> N >> K;
    for(int i = 1; i <= N; ++i)cin >> a[i];
    for(int i = 1; i <= N; ++i)
      for(int j = 1; j <= N; ++j)
        for(int k = 0; k <= K; ++k)
          dp[i][j][k] = inf;
    for(int i = 1; i <= N; ++i){
      if(a[i] != a[1])dp[1][i][0] = 1;
      else dp[1][i][0] = 0;
    }
    for(int i = 2; i <= N; ++i){
      for(int j = 1; j <= N; ++j){
        for(int k = 0; k <= K; ++k){
          for(int x = 1; x <= N; ++x){
            if(a[j] == a[x]){
              if(a[i] != a[j])dp[i][j][k] = min(dp[i][j][k] , dp[i - 1][x][k] + 1);
              else dp[i][j][k] = min(dp[i][j][k] , dp[i - 1][x][k]);
            }
            else{
              if(a[i] != a[j] && k)
                dp[i][j][k] = min(dp[i][j][k] , dp[i - 1][x][k - 1] + 1);
              else if(a[i] == a[j] && k)
                dp[i][j][k] = min(dp[i][j][k] , dp[i - 1][x][k - 1]);
            }
          }
        }
      }
    }
    int ret = N;
    for(int i = 1; i <= N; ++i)
      for(int j = 0; j <= K; ++j)
        ret = min(ret , dp[N][i][j]);
    cout << "Case #" << t << ": " << ret << endl;
  }
}
