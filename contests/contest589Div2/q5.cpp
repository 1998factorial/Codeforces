#include <iostream>
#include <cstdio>
using namespace std;
typedef long long ll;

const ll mod = 1e9 + 7;
int N;
ll K;
ll dp[255][255]; // dp[i][j] = # i good rows j good cols
ll fac[255] , ifac[255] , p[255] , p1[255];

ll qpow(ll x , ll n){
  if(n <= 0)return 1ll;
  ll ret = qpow(x , n / 2);
  if(n % 2 == 1){
    return (ret * x % mod) * ret % mod;
  }
  return ret * ret % mod;
}

ll C(int n , int r){
  return (fac[n] * ifac[r] % mod) * ifac[n - r] % mod;
}

int main(){
  cin >> N >> K;
  fac[0] = 1;
  p[0] = 1;
  p1[0] = 1;
  for(int i = 1; i <= N; ++i){
    fac[i] = fac[i - 1] * i % mod;
    p[i] = p[i - 1] * K % mod;
    p1[i] = p1[i - 1] * (K - 1) % mod;
  }
  ifac[N] = qpow(fac[N] , mod - 2);
  for(int i = N - 1; i >= 0; --i){
    ifac[i] = ifac[i + 1] * (i + 1) % mod;
  }
  for(int i = 0; i <= N; ++i){
    for(int j = 0; j <= N; ++j){
      dp[i][j] = 0;
    }
  }
  dp[0][0] = 1ll;
  for(int i = 1; i <= N; ++i){
    for(int j = 1; j <= N; ++j){ // j good cols
      for(int k = 0; k <= j; ++k){ // from k good cols
        ll c = dp[i - 1][k] * C(N - k , j - k) % mod; // we can choose j - k cols from n - k bad cols to form 1
        c = c * p1[N - j] % mod; // (K - 1) ^ (n - j) choices for the bad cols
        if(j == k)c = c * (p[k] - p1[k]) % mod; // each row must has at least 1 "1" , so if j = k , we might have the case where we have no "1" , need to subtract such case then
        else c = c * p[k] % mod;
        dp[i][j] = (dp[i][j] + c) % mod;
      }
    }
  }
  cout << (dp[N][N] + mod ) % mod << endl;
  return 0;
}
