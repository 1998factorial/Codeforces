#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl
using namespace std;
typedef long long ll;
typedef pair<int , int> ii;

const int mod = 998244353;
const int maxn = 550;
int N , M;
ll L[maxn] , R[maxn];
ll INV[maxn];
ll F[maxn];
ll DP[maxn][maxn];
/*
  DP[i][j] = number of ways to place the first i elements in some of the last j segments
*/
vector<ll> t;

ll qpow(ll x , ll n){
  ll ret = 1ll;
  while(n){
    if(n & 1)ret = ret * x % mod;
    x = x * x % mod;
    n >>= 1;
  }
  return ret;
}

ll inverse(ll x){
  return qpow(x , mod - 2);
}

ll C(ll n , ll r){
  ll ret = 1ll;
  for(ll i = n; i > n - r; --i){
    ret = ret * i % mod;
  }
  return ret * INV[r] % mod;
}

int main(){
  F[0] = 1;
  for(int i = 1; i < maxn; ++i){
    F[i] = F[i - 1] * i % mod;
  }
  INV[maxn - 1] = inverse(F[maxn - 1]);
  for(int i = maxn - 2; i >= 0; --i){
    INV[i] = INV[i + 1] * (i + 1) % mod;
  }
  cin >> N;
  for(int i = 1; i <= N; ++i){
    cin >> L[i] >> R[i];
    ++R[i];
    t.push_back(L[i]);
    t.push_back(R[i]);
  }
  t.push_back(-1);
  sort(t.begin() , t.end());
  t.resize(unique(t.begin() , t.end()) - t.begin());
  M = t.size() - 1;
  for(int i = 1; i <= N; ++i){
    L[i] = lower_bound(t.begin() , t.end() , L[i]) - t.begin();
    R[i] = lower_bound(t.begin() , t.end() , R[i]) - t.begin();
  }
  for(int i = 1; i <= M; ++i)DP[0][i] = 1;
  for(int i = 1; i <= N; ++i){
    for(int j = L[i]; j < R[i]; ++j){
      for(int k = 1; k <= i; ++k){
        if(j < L[k] || j >= R[k])continue;
        DP[i][j] = (DP[i][j] + (DP[k - 1][j + 1] * C(t[j + 1] - t[j] + i - k , i - k + 1) % mod)) % mod;
      }
    }
    for(int j = M - 1; j >= 1; --j){
      DP[i][j] = (DP[i][j + 1] + DP[i][j]) % mod;
    }
  }
  ll fenmu = 1ll;
  for(int i = 1; i <= N; ++i){
    fenmu = fenmu * inverse(t[R[i]] - t[L[i]]) % mod;
  }
  cout << DP[N][1] * fenmu % mod << endl;
}
