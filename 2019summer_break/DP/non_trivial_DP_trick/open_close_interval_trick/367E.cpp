#include <iostream>
#include <algorithm>
using namespace std;
typedef long long ll;

const ll mod = 1e9 + 7;
const int maxn = 1e5 + 10;
int N , M , X;
ll fac[maxn];
ll dp[2][350][305];

/*
  苟利国家生死以 岂因祸福避趋之
*/

ll solve(){
  dp[0][0][0] = 1;
  for(int i = 1; i <= M; ++i){
    for(int j = 0; j <= min(N , i); ++j){
      for(int k = 0; k <= j; ++k){
        dp[i % 2][j][k] = 0;
        if(i == X){
          if(j - 1 >= k)
            dp[i % 2][j][k] = (dp[i % 2][j][k] + dp[(i - 1) % 2][j - 1][k]) % mod; // place [
          if(j && k)
            dp[i % 2][j][k] = (dp[i % 2][j][k] + dp[(i - 1) % 2][j - 1][k - 1]) % mod; // place []
        }
        else{
          dp[i % 2][j][k] = (dp[i % 2][j][k] + dp[(i - 1) % 2][j][k]) % mod; // place nothing
          if(j - 1 >= k)
            dp[i % 2][j][k] = (dp[i % 2][j][k] + dp[(i - 1) % 2][j - 1][k]) % mod; // place [
          if(k)
            dp[i % 2][j][k] = (dp[i % 2][j][k] + dp[(i - 1) % 2][j][k - 1]) % mod; // place ]
          if(j && k)
            dp[i % 2][j][k] = (dp[i % 2][j][k] + dp[(i - 1) % 2][j - 1][k - 1]) % mod; // place []
        }
      }
    }
  }
  return dp[M % 2][N][N];
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  fac[0] = 1;
  for(int i = 1; i < maxn; ++i)fac[i] = fac[i - 1] * i % mod;
  cin >> N >> M >> X;
  if(N > M)cout << 0 << endl;
  else cout << (solve() * fac[N] % mod + mod) % mod << endl;
}
