#include <iostream>
#include <algorithm>
using namespace std;
typedef pair<int , int> ii;
typedef long long ll;

/*
# of black cells is small , thus we should do something about it.
*/

const ll mod = 1e9 + 7;
const int maxn = 2e3 + 10;
const int maxm = 2e5 + 10;
int W , H , N;
ii black[maxn];
ll dp[maxn];
ll fac[maxm] , ifac[maxm];

ll qpow(ll x , ll n){
  if(n <= 0)return 1ll;
  ll ret = qpow(x , n / 2);
  ret = ret * ret % mod;
  if(n % 2 == 1)ret = ret * x % mod;
  return ret;
}

ll C(int n , int r){
  return (fac[n] * ifac[r] % mod) * ifac[n - r] % mod;
}

int main(){
  cin >> H >> W >> N;
  for(int i = 1; i <= N; ++i){
    cin >> black[i].first >> black[i].second;
  }
  black[N + 1].first = H , black[N + 1].second = W;
  fac[0] = 1;
  for(int i = 1; i <= H + W; ++i){
    fac[i] = fac[i - 1] * i % mod;
  }
  ifac[H + W] = qpow(fac[H + W] , mod - 2);
  for(int i = H + W - 1; i >= 0; --i){
    ifac[i] = ifac[i + 1] * (i + 1) % mod;
  }
  sort(black + 1 , black + 1 + N + 1);
  for(int i = 1; i <= N + 1; ++i){
    dp[i] = C(black[i].first - 1 + black[i].second - 1 , black[i].first - 1);
  }
  for(int i = 2; i <= N + 1; ++i){
    for(int j = 1; j < i; ++j){
      if(black[i].second < black[j].second)continue;
      ll c = dp[j] * C(black[i].first - black[j].first + black[i].second - black[j].second , black[i].first - black[j].first) % mod;
      dp[i] = (dp[i] - c + mod) % mod;
    }
  }
  cout << (dp[N + 1] + mod) % mod << endl;
}
