#include <iostream>
using namespace std;
typedef long long ll;

const int maxn = 1e2 + 10;
const ll mod = 1e9 + 7;
int N , K;
int a[maxn];
ll dp[maxn][10000]; // to be determined
ll comb[maxn][maxn];
// K is up to 1e9 so we might use matrices
// but need to get DP done first
ll qpow(ll x , ll n){
  if(n <= 0)return 1ll;
  ll ret = qpow(x , n / 2);
  if(n % 2 == 1)return ret * ret % mod * x % mod;
  return ret * ret % mod;
}

ll inverse(ll x){
  return qpow(x , mod - 2);
}

ll add(ll x , ll y){
  return (x + y) % mod;
}

ll mul(ll x , ll y){
  return x * y % mod;
}

ll solve(){
  int cnt[2];
  for(int i = 1; i <= N; ++i){
    cnt[0] += a[i] == 0;
    cnt[1] += a[i] == 1;
  }
  int nzero = 0;
  for(int i = 1; i <= cnt[0]; ++i){
    nzero += a[i] == 0;
  }
  dp[nzero][0] = 1;
  for(int j = 1; j <= K; ++j){
    for(int i = 0; i <= cnt[0]; ++i){
      dp[i][j] += (comb[cnt[0]][2] + comb[cnt[1]][2]) * dp[i][j - 1];
      dp[i][j] += ((cnt[0] - i) * (i) + (cnt[0] - i) * (cnt[1] - cnt[0] + i)) * dp[i][j - 1];
      if(i + 1 <= cnt[0])
        dp[i][j] += (i + 1) * (cnt[1] - cnt[0] + i + 1) * dp[i + 1][j - 1];
      if(i - 1 >= 0)
        dp[i][j] += (cnt[0] - i + 1) * (cnt[0] - i + 1) * dp[i - 1][j - 1];
      dp[i][j] = dp[i][j] * inverse(comb[N][2]) % mod;
    }
  }
  return dp[cnt[0]][K];
}

int main(){
  cin >> N >> K;
  for(int i = 1; i <= N; ++i)cin >> a[i];
  comb[0][0] = 1;
  for(int i = 1; i <= N; ++i){
    for(int j = 0; j <= i; ++j){
      if(j - 1 >= 0)
      comb[i][j] = (comb[i - 1][j - 1] + comb[i - 1][j]) % mod;
      else
      comb[i][j] = comb[i - 1][j] % mod;
    }
  }
  cout << (solve() + mod) % mod << endl;
}
