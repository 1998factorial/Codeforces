#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
using namespace std;
typedef pair<int , int > ii;
typedef long long ll;

int N , M , K , S;
const ll mod = 1e9 + 7;
ii pos[2005];
ll dp[2005][22];
ll npaths[2005]; //number of paths from (1 , 1) to (x[i] , y[i]) without getting through any black cells
ll fac[200005] , ifac[200005];
//dp[i][j] = the number of ways to get to the i-th black cell given that we seen at least j black cells before
bool flag;

ll qpow(ll x , ll n){
  if(n <= 0)return 1;
  ll ret = qpow(x , n / 2);
  ret = ret * ret % mod;
  if(n % 2 == 1)ret = ret * x % mod;
  return ret;
}

ll inverse(ll x){
  return qpow(x , mod - 2);
}

ll C(int n , int r){
  return (fac[n] * ifac[n - r] % mod) * ifac[r]% mod;
}

ll nC(int i , int j){
  return C(pos[i].first - pos[j].first + pos[i].second - pos[j].second , pos[i].first - pos[j].first);
}

ll solve(){ // return the expected power at position[N][M]
  for(int i = 1; i <= K; ++i){
    dp[i][0] = C(pos[i].first + pos[i].second - 2 , pos[i].first - 1);
  }
  // dp[i][j] = sum : (dp[x][j - 1] - dp[x][j]) * nC(x , i)
  for(int j = 1; j <= 20; ++j){
    for(int i = 1; i <= K; ++i){
      for(int k = 0; k < i; ++k){
        if(pos[i].second >= pos[k].second){
          ll cnt = nC(i , k) * (dp[k][j - 1] - dp[k][j]) % mod;
          dp[i][j] = (dp[i][j] + cnt) % mod;
        }
      }
    }
  }
  ll ret = 0;
  for(int i = 0; i <= 20; ++i){
    if(S < 1)S = 1;
    ret = (ret + ((dp[K][i] - dp[K][i + 1] + mod) % mod) * S % mod) % mod;
    S = (S + 1) / 2;
  }
  return ret * inverse(C(N + M - 2 , N - 1)) % mod;
}

int main(){
  cin >> N >> M >> K >> S;
  for(int i = 1; i <= K; ++i){
    cin >> pos[i].first >> pos[i].second;
  }
  sort(pos + 1 , pos + 1 + K);
  pos[++K] = make_pair(N , M);
  fac[0] = 1;
  ifac[0] = inverse(fac[0]);
  for(int i = 1; i <= N + M + 1; ++i){
    fac[i] = i * fac[i - 1] % mod;
    ifac[i] = inverse(fac[i]);
  }
  cout << (solve() + mod) % mod << endl;
}
