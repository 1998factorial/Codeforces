#include <iostream>
#include <vector>
#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long ll;
const int maxn = 3e5 + 10;
const ll inf = 1ll << 50;
int n;
ll a[maxn] , b[maxn];
ll dp[maxn][3]; // dp[i][k] = minimal cost for increasing ai by k
// we will increase k by at most 2
// a , a + 1 , a + 2 , by pigeon hole principle , one can always use one element from
// this set and make sure it is different from 2 other adjcent elements

int main(){
  int Q;
  scanf("%d" , &Q);
  for(int q = 1; q <= Q; ++q){
    scanf("%d" , &n);
    for(int i = 1; i <= n; ++i){
      scanf("%lld %lld" , &a[i] , &b[i]);
      for(int j = 0; j < 3; ++j){
        dp[i][j] = inf;
      }
    }
    dp[1][0] = 0;
    dp[1][1] = b[1];
    dp[1][2] = b[1] * 2;
    ll ret = inf;
    for(int i = 2; i <= n; ++i){
      for(int j = 0; j < 3; ++j){
        for(int k = 0; k < 3; ++k){
          if(a[i - 1] + k != a[i] + j){
            if(dp[i][j] > dp[i - 1][k] + b[i] * j){
              dp[i][j] = dp[i - 1][k] + b[i] * j;
            }
          }
        }
      }
    }
    for(int i = 0; i < 3; ++i){
      if(ret > dp[n][i])ret = dp[n][i];
    }
    printf("%lld\n" , ret);
  }
  return 0;
}
