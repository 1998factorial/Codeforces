#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl
using namespace std;
typedef long long ll;
typedef pair<int , int> ii;

const ll mod = 998244353;
const int maxn = 2e5 + 10;

ll f[maxn];
int N , M;

ll qpow(ll x , ll n){
  if(n <= 0)return 1;
  ll ret = qpow(x , n / 2);
  ret = ret * ret % mod;
  if(n % 2)ret = ret * x % mod;
  return ret;
}

ll inverse(ll x){
  return qpow(x , mod - 2);
}

ll comb(ll n , ll r){
  return f[n] * (inverse(f[n - r]) * inverse(f[r]) % mod) % mod;
}

int main(){
  cin >> N >> M;
  f[0] = 1;
  for(int i = 1; i < maxn; ++i)f[i] = f[i - 1] * i % mod;
  ll ret = comb(M , N - 1) % mod;
  ret = ret * (N - 2) % mod;
  ret = ret * qpow(2ll , N - 3) % mod;
  cout << (ret + mod) % mod << endl;
}
