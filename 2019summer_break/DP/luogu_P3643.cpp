#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl
#define all(x) x.begin(), x.end()
using namespace std;
typedef long long ll;
typedef pair<int , int> ii;
const ll mod = 1e9 + 7;
const int maxn = 2000;
ll L[maxn] , R[maxn];
vector<ll> t;
int N , M;
ll DP[maxn][maxn];
ll G[maxn][maxn];
ll inv[maxn];
ll C[maxn];

ll qpow(ll x , ll n){ // quick power of x
  ll ret = 1;
  while(n){
    if(n & 1)ret = ret * x % mod;
    x = x * x % mod;
    n >>= 1;
  }
  return ret;
}

ll inverse(int x){ // find y st y * x % mod = 1
  return qpow(x , mod - 2);
}

void init(){ // init factorial and inverse
  for(int i = 1; i < maxn; ++i){
    inv[i] = inverse(i);
  }
  /*INV[1] = 1;
  for(int i = 2; i < maxn * 4; ++i){
    INV[i] = (mod - mod / i) * INV[mod % i] % mod;
  }*/
  // alternative way to get inverse
}

void discrete(){
  t.clear();
  t.push_back(0);
  for(int i = 1; i <= N; ++i){
    t.push_back(L[i]);
    t.push_back(R[i]);
  }
  sort(all(t));
  t.resize(unique(all(t)) - t.begin());
  M = t.size() - 1;
  for(int i = 1; i <= N; ++i){
    L[i] = lower_bound(all(t) , L[i]) - t.begin();
    R[i] = lower_bound(all(t) , R[i]) - t.begin();
  }
}

int main(){
  init();
  scanf("%d" , &N);
  for(int i = 1; i <= N; ++i){
    scanf("%lld %lld" , &L[i] , &R[i]);
    ++R[i];
  }
  discrete();
  C[0] = 1;
  DP[0][0] = 1;
  for(int i = 0; i <= M; ++i)G[0][i] = 1;
  for(int j = 1; j < M; ++j){
    int len = t[j + 1] - t[j];
    for(int i = 1; i <= N; ++i)
      C[i] = ((C[i - 1] * (len + i - 1)) % mod) * inv[i] % mod;
    for(int i = 1; i <= N; ++i){
      if(j >= L[i] && j < R[i]){
        ll c = len , m = 1;
        for(int p = i - 1; p >= 0; --p){
          DP[i][j] = (DP[i][j] + c * G[p][j - 1] % mod) % mod;
          if(j >= L[p] && j < R[p]){
            c = C[++m];
          }
        }
      }
    }
    for(int i = 1; i <= N; ++i){
      G[i][j] = (G[i][j - 1] + DP[i][j]) % mod;
    }
  }
  ll ret = 0;
  for(int i = 1; i <= N; ++i){
    for(int j = 1; j <= M; ++j)
    ret = (ret + DP[i][j]) % mod;
  }
  printf("%lld\n" , ret);
}
