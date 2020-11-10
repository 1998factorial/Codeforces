#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;
typedef long long ll;

const ll mod = 1e9 + 7;
int n;
ll K;
ll dp[255][255];
ll f[255];
ll fi[255];
ll p[255]; // qpow(K , i)
ll p1[255]; // qpow(K - 1 , i)

ll qpow(ll x , ll n){
  if(n <= 0)return 1ll;
  ll ret = qpow(x , n / 2);
  if(n % 2 == 1){
    return (x * ret % mod) * ret % mod;
  }
  return ret * ret % mod;
}

ll C(ll n , ll m){
  return (f[n] * fi[m] % mod) * fi[n - m] % mod;
}

int main(){
  cin >> n >> K;
  f[0] = 1ll;
  for(int i = 1; i <= n; ++i)f[i] = f[i - 1] * i % mod;
  fi[n] = qpow(f[n] , mod - 2);
  for(int i = n - 1; i >= 0; --i)fi[i] = fi[i + 1] * (i + 1) % mod;
  for(int i = 0; i <= n; ++i){
    p[i] = qpow(K , i);
    p1[i] = qpow(K - 1 , i);
  }
  for(int i = 0; i <= n; ++i){
    for(int j = 0; j <= n; ++j){
      dp[i][j] = 0ll;
    }
  }
  dp[0][0] = 1ll;
  for(int i = 1; i <= n; ++i){
    for(int j = 1; j <= n; ++j){ // j good cols
      for(int k = 0; k <= j; ++k){ // from k good cols
        // j - k bad to good
        ll c = dp[i - 1][k] * C(n - k , j - k) % mod;
        c = c * p1[n - j] % mod;
        ll d = (j == k) ? (p[k] - p1[k] + mod) % mod : p[k];
        c = c * d % mod;
        dp[i][j] = (dp[i][j] + c) % mod;
      }
    }
  }
  cout << (dp[n][n] + mod) % mod << endl;
  return 0;
}
