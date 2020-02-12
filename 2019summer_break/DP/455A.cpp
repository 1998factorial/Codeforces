#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 1e5 + 10;
int cnt[maxn] , N;
ll dp[maxn];

/*
  dp[i] = maximal score for all elements not greater than i
  dp[i] = max(dp[i - 1] , dp[i - 2] + cnt[i] * a[i])
*/

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> N;
  for(int i = 1; i <= N; ++i){
    int x; cin >> x; ++cnt[x];
  }
  dp[0] = 0;
  dp[1] = (ll)cnt[1]
  ;
  for(int i = 2; i < maxn; ++i){
    dp[i] = max(
      dp[i - 1],
      dp[i - 2] + (ll)cnt[i] * i
    );
  }
  cout << dp[maxn - 1] << endl;
}
