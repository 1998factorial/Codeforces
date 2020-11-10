#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl
using namespace std;
typedef long long ll;
typedef pair<int , int> ii;
/*
  if a block can be merged into one element
  say a[i..j], then there exist a[i..k] and a[k+1..j]
  where these 2 blocks can be merged into 2 elements with same value
  then we know what blocks can be merged into 1
  so we can use another dp, ans[i] = minimal number of blocks we can shrink
  up to the ith element
*/
int a[505];
int N;
const int inf = 1e9 + 10;

int dp[505][505];
int ans[505];

int main(){
  cin >> N;
  for(int i = 1; i <= N; ++i)cin >> a[i];
  for(int i = 1; i <= N; ++i){
    dp[i][i] = a[i];
  }
  for(int len = 2; len <= N; ++len){
    for(int i = 1; i + len - 1 <= N; ++i){
      int j = i + len - 1;
      dp[i][j] = -1;
      for(int k = i; k < j; ++k){
        if(dp[i][k] != -1 && dp[i][k] == dp[k + 1][j]){
          dp[i][j] = dp[i][k] + 1;
          break;
        }
      }
    }
  }
  for(int i = 1; i <= N; ++i){
    ans[i] = inf;
    for(int j = 1; j <= i; ++j){
      if(dp[j][i] != -1){
        ans[i] = min(ans[i] , ans[j - 1] + 1);
      }
    }
  }
  cout << ans[N] << endl;
}
