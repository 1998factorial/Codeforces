#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl
using namespace std;
typedef long long ll;
typedef pair<int , int> ii;

const int mod = 998244353;
const int maxn = 55;
int N;
ll L[maxn] , R[maxn];
ll DP[maxn][10000];
/*
  DP solution:
  DP[i][j] = "number of ways to create non increasing sequence where the ith number is j"
  O(N * mod * mod)
  L[i] , R[i] <= mod
  too slow
*/
ll qpow(ll x , ll n){
  if(n <= 0)return 1ll;
  ll ret = qpow(x , n / 2);
  ret = ret * ret % mod;
  if(n & 1)ret = ret * x % mod;
  return ret;
}

ll inverse(ll x){
  return qpow(x , mod - 2);
}

int main(){
  cin >> N;
  for(int i = 1; i <= N; ++i){
    cin >> L[i] >> R[i];
  }
  for(ll i = L[1]; i <= R[1]; ++i){
    DP[1][i] = 1;
  }
  for(int i = 2; i <= N; ++i){
    for(ll j = L[i]; j <= R[i]; ++j){
      for(ll k = j; k <= R[i - 1]; ++k){
        DP[i][j] += DP[i - 1][k];
      }
    }
  }
  ll ret = 0;
  for(ll i = 0; i <= R[N]; ++i){
    ret += DP[N][i];
  }
  ll fenmu = inverse(R[1] - L[1] + 1);
  for(int i = 2; i <= N; ++i){
    fenmu = fenmu * inverse(R[i] - L[i] + 1) % mod;
  }
  cout << ret * fenmu % mod << endl;
}
