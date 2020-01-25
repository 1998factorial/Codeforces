#include <iostream>
#include <algorithm>
using namespace std;
typedef long long ll;

const int mod = 1e9 + 7;
int N , K , a[205];
int dp[205][205][1005];
// dp[pos][number of open interval][total imbalance] : total number of ways to achieve this

int main(){
  cin >> N >> K;
  for(int i = 1; i <= N; ++i)cin >> a[i];
  sort(a + 1 , a + 1 + N);
  dp[0][0][0] = 1;
  for(int i = 0; i < N; ++i){
    for(int j = 0; j <= i; ++j){
      for(int k = 0; k <= K; ++k){
        int nk = k + (a[i + 1] - a[i]) * j;
        if(nk > K)continue;
        dp[i + 1][j + 1][nk] = (dp[i + 1][j + 1][nk] + dp[i][j][k]) % mod;
        dp[i + 1][j][nk] = (dp[i + 1][j][nk] + dp[i][j][k]) % mod;
        if(j > 0)dp[i + 1][j - 1][nk] = (dp[i + 1][j - 1][nk] + (ll)dp[i][j][k] * j % mod) % mod;
        dp[i + 1][j][nk] = (dp[i + 1][j][nk] + (ll)dp[i][j][k] * j % mod) % mod;
      }
    }
  }
  ll ret = 0;
  for(int i = 0; i <= K; ++i){
    ret = (ret + dp[N][0][i]) % mod;
  }
  cout << (ret + mod) % mod << endl;
}
