#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl
using namespace std;
typedef long long ll;
typedef pair<int , int> ii;


const int maxn = 55;
int S[maxn][35];
int sum[maxn][35]; // sum[i][j] = S[i][1] + .. + S[i][j]
int N , P , K;
int dp[maxn][1505];

int solve(){
  scanf("%d %d %d" , &N , &K , &P);
  for(int i = 1; i <= N; ++i){
    for(int j = 1; j <= K; ++j){
      scanf("%d" , &S[i][j]);
    }
  }
  for(int i = 1; i <= N; ++i){
    sum[i][0] = 0;
    for(int j = 1; j <= K; ++j){
      sum[i][j] = sum[i][j - 1] + S[i][j];
    }
  }
  memset(dp , 0 , sizeof(dp));
  for(int i = 1; i <= N; ++i){
    for(int j = 1; j <= P; ++j){
      dp[i][j] = max(dp[i][j] , dp[i - 1][j]);
      for(int k = 1; k <= K; ++k){
        if(k > j)break;
        dp[i][j] = max(dp[i][j] , dp[i - 1][j - k] + sum[i][k]);
      }
    }
  }
  int ret = 0;
  for(int i = 1; i <= N; ++i)ret = max(ret , dp[i][P]);
  return ret;
}

int main(){
  int t; scanf("%d" , &t);
  for(int x = 1; x <= t; ++x){
    printf("Case #%d: %d\n" , x , solve());
  }
}
