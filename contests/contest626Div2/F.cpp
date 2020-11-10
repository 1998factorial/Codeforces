#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl
using namespace std;
typedef long long ll;
typedef pair<int , int> ii;

const int maxn = 2e3 + 10;
const ll inf = 1e18 + 10;
ll l[maxn] , s[maxn] , profit[maxn + maxn];
ll dp[maxn * 2][maxn];
// dp[i][j][k] = maximal profit for the first i ppl if the maximal l = j , and its number = k
int N , M;

int main(){
  scanf("%d %d" , &N , &M);
  // reverse the list of candidates
  for(int i = N; i >= 1; --i){
    scanf("%lld" , &l[i]);
  }
  for(int i = N; i >= 1; --i){
    scanf("%lld" , &s[i]);
  }
  for(int i = 1; i <= N + M; ++i){
    scanf("%lld" , &profit[i]);
  }
  for(int i = 1; i <= N + M; ++i){
    for(int j = 1; j <= N; ++j){
      dp[i][j] = -inf;
    }
  }
  for(int i = 1; i <= N; ++i){
    int x = l[i];
    for(int j = i; j >= 1; --j){
      dp[x][j] = max(dp[x][j] , dp[x][j - 1] + profit[x] - s[i]);
    }
    for(int j = x; j <= N + M; ++j){
      //for(int k = 0; k <= i >> (j - x); ++k){
      for(int k = i >> (j - x); k >= 0; --k){ // either direction works
        dp[j + 1][k / 2] = max(dp[j + 1][k / 2] , dp[j][k] + (k / 2) * profit[j + 1]);
      }
    }
  }
  ll ans = 0;
  for(int i = 1; i <= N + M + 1; ++i){
    ans = max(ans , dp[i][0]);
  }
  printf("%lld\n" , ans);
}
