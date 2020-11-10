#include <iostream>
#include <algorithm>
#include <string.h>
using namespace std;
typedef long long ll;
const ll inf = 1e18;
const int maxn = 1e5 + 10;
ll a[maxn];
ll dp[maxn];

int N;

ll solve1(){
  memset(dp , 0 , sizeof(dp));
  ll ret = -inf;
  for(int i = 1; i < N; ++i){
    if(dp[i - 1] + a[i] >= a[i])dp[i] = dp[i - 1] + a[i];
    else dp[i] = a[i];
    ret = max(dp[i] , ret);
  }
  return ret;
}

ll solve2(){
  memset(dp , 0 , sizeof(dp));
  ll ret = -inf;
  for(int i = 2; i <= N; ++i){
    if(dp[i - 1] + a[i] >= a[i])dp[i] = dp[i - 1] + a[i];
    else dp[i] = a[i];
    ret = max(dp[i] , ret);
  }
  return ret;
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int T; cin >> T;
  for(int t = 1; t <= T; ++t){
    cin >> N;
    ll A = 0;
    for(int i = 1; i <= N; ++i)cin >> a[i] , A += a[i];
    ll B = max(solve1() , solve2());
    if(A > B)cout << "YES" << endl;
    else cout << "NO" << endl;
  }
}
