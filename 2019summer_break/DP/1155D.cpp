#include <iostream>
#include <algorithm>
using namespace std;
typedef long long ll;
/*
  let dp[i] = solution up to the i-th element
  consider a[i] , we either multiply it by X or we do not
  we either include it in our final solution or we do not
  (suggesting we need more states)

  we can multiply a[i] by X if a[i - 1] is multiplied by X
  or a[1 .. i - 1] has no element mul by X
  0 -> no previous element is mul by X
  1 -> a[i] is in the multiplied segment
  2 -> multiplied segment ends with a[i]
  3 -> multiplied segment has been closed and it is before a[i]
*/
const int maxn = 3e5 + 10;
const ll inf = 1e18;
int N , X;
ll a[maxn];
ll dp[maxn][4];

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> N >> X;
  for(int i = 1; i <= N; ++i)cin >> a[i];
  for(int i = 0; i <= N; ++i){
    for(int j = 0; j < 4; ++j){
      dp[i][j] = -inf;
    }
  }
  dp[0][0] = 0;
  ll ret = 0;
  for(int i = 1; i <= N; ++i){
    // if we multiply a[i] by X
    dp[i][1] = max(dp[i][1] , max(dp[i - 1][0] + a[i] * X , a[i] * X));
    dp[i][1] = max(dp[i][1] , max(dp[i - 1][1] + a[i] * X , a[i] * X));
    dp[i][2] = max(dp[i][2] , max(dp[i - 1][0] + a[i] * X , a[i] * X));
    dp[i][2] = max(dp[i][2] , max(dp[i - 1][1] + a[i] * X , a[i] * X));
    // if we do not
    dp[i][3] = max(dp[i][3] , max(dp[i - 1][3] + a[i] , a[i]));
    dp[i][3] = max(dp[i][3] , max(dp[i - 1][2] + a[i] , a[i]));
    dp[i][0] = max(dp[i][0] , max(dp[i - 1][0] + a[i] , a[i]));
    for(int j = 0; j < 4; ++j){
      ret = max(ret , dp[i][j]);
    }
  }
  cout << ret << endl;
}
