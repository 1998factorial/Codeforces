#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

typedef long long ll;
const int maxn = 3005;
const ll mod = 998244353;
ll w[200005];
ll inv[maxn << 1];
int dp[maxn][maxn][2];
int a[200005];
int N , M;

/*
  dp[i][j][0] = the expected incremental weight on the pictures that
  we like , given that the sum of liked pic is A + i and disliked being B - j
  dp[i][j][0] = (A + i + 1) / (A + i + B - j) * dp[i + 1][j][0] + (B - j) / (A + i + B - j) * dp[i][j + 1][0]

  dp[i][j][1] is for the disliked
  similarly :
  dp[i][j][1] = (A + i) / (A + i + B - j) * dp[i + 1][j][1] + (B - j - 1) / (A + i + B - j) * dp[i][j + 1][1]
*/

ll qpow(ll x , ll n){
  if(n <= 0)return 1ll;
  ll ret = qpow(x , n >> 1);
  if(n % 2 == 1){
    return x * (ret * ret % mod) % mod;
  }
  return ret * ret % mod;
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> N >> M;
  for(int i = 1; i <= N; ++i)cin >> a[i];
  for(int i = 1; i <= N; ++i)cin >> w[i];
  ll A = 0 , tot = 0 , B = 0;
  for(int i = 1; i <= N; ++i){
    if(a[i] == 1)A += w[i];
    else B += w[i];
    tot += w[i];
  }
  for(int i = 0; i <= M * 2; ++i){
    inv[i] = qpow(tot + i - M , mod - 2);
  }
  for(int i = M; i >= 0; --i){
    dp[i][M - i][0] = dp[i][M - i][1] = 1;
    for(int j = min((ll)M - i - 1 , B); j >= 0; --j){
      dp[i][j][0] = ((A + i + 1) * dp[i + 1][j][0] % mod + (B - j) * dp[i][j + 1][0] % mod) % mod * inv[M + i - j] % mod;
      dp[i][j][1] = ((A + i) * dp[i + 1][j][1] % mod + (B - j - 1) * dp[i][j + 1][1] % mod) % mod * inv[M + i - j] % mod;
    }
  }
  for(int i = 1; i <= N; ++i){
    if(a[i] == 1){
      cout << ( w[i] * dp[0][0][0] % mod + mod ) % mod << " ";
    }
    else{
      cout << ( w[i] * dp[0][0][1] % mod + mod ) % mod << " ";
    }
  }
  cout << endl;
}
