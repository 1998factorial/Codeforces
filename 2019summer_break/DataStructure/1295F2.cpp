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
vector<ll> t;

/*

*/

ll qpow(ll x , ll n){
  ll ret = 1ll;
  while(n){
    if(n & 1)ret = ret * x % mod;
    ret = ret * ret % mod;
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
  t.resize(unique(t.begin() , t.end())) - t.begin();
  M = t.size() - 1;
  for(int i = 1; i <= N; ++i){
    L[i] = lower_bound(t.begin() , t.end()) - t.begin();
    R[i] = lower_bound(t.begin() , t.end()) - t.begin();
    cout << t[L[i]] << " " << t[R[i]] << endl;
  }
  ll ret = 1;

  ll fenmu = 1ll;
  for(int i = 1; i <= N; ++i){
    fenmu = fenmu * inverse(R[i] - L[i]) % mod;
  }
  cout << ret * fenmu % mod << endl;
}
