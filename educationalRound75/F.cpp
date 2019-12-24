#include <iostream>
#include <string.h>
#include <algorithm>
using namespace std;
typedef long long ll;

const ll mod = 998244353;
const int maxn = 12e5 + 10;
ll a[300005] , b[10] , cnt[300005];
ll fac[maxn] , ifac[maxn] , tp[maxn];
ll ans[maxn];
ll A[maxn] , B[maxn] , R[maxn];
int N , K , Q , len , L;

/*
  figure out what your polynomial is and use NTT to do polynomial multiplication
*/

ll qpow(ll x , ll n){
  ll ret = 1ll;
  while(n){
    if(n % 2 == 1)ret = ret * x % mod;
    x = x * x % mod;
    n >>= 1;
  }
  return ret;
}

ll C(ll n , ll r){
  return fac[n] * (ifac[r] * ifac[n - r] % mod) % mod;
}

void NTT(ll* A , int op){
  for(int i = 0; i < len; ++i)if(i < R[i])swap(A[i] , A[R[i]]);
  for(int i = 1; i < len; i <<= 1){
    ll gn = qpow(3ll , (mod - 1) / (i << 1));
    if(op == -1)gn = qpow(gn , mod - 2);
    for(int j = 0; j < len; j += (i << 1)){
      ll g = 1;
      for(int k = 0; k < i; ++k , g = g * gn % mod){
        ll x = A[j + k] , y = g * A[j + k + i] % mod;
        A[j + k] = (x + y) % mod;
        A[j + k + i] = (x - y) % mod;
      }
    }
  }
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> N >> K;
  fac[0] = 1;
  tp[0] = 1;
  memset(cnt , 0 , sizeof(cnt));
  for(int i = 1; i < maxn; ++i)fac[i] = fac[i - 1] * i % mod , tp[i] = tp[i - 1] * 2 % mod;
  ifac[maxn - 1] = qpow(fac[maxn - 1] , mod - 2);
  for(int i = maxn - 2; i >= 0; --i){
    ifac[i] = ifac[i + 1] * (i + 1) % mod;
  }
  for(int i = 1; i <= N; ++i){
    cin >> a[i];
    ++cnt[a[i]];
  }
  for(int p = 1; p <= K; ++p){
    int length; cin >> length;
    int a = 0 , b = 0;
    for(int x = 1; x < length; ++x){
      if(cnt[x] >= 2)a += 2;
      else if(cnt[x] == 1)++b;
    }
    memset(A , 0 , sizeof(A));
    memset(B , 0 , sizeof(B));
    for(int i = 0; i <= a; ++i)A[i] = C(a , i);
    for(int i = 0; i <= b; ++i)B[i] = C(b , i) * tp[i] % mod;
    L = 0;
    for(len = 1; len <= a + b; len <<= 1)++L;
    for(int i = 0; i < len; ++i)R[i] = (R[i >> 1] >> 1) | ((i & 1) << (L - 1));
    NTT(A , 1);
    NTT(B , 1);
    for(int i = 0; i < len; ++i)A[i] = A[i] * B[i] % mod;
    NTT(A , -1);
    ll inv = qpow(len , mod - 2);
    for(int i = 0; i < len; ++i)A[i] = A[i] * inv % mod;
    for(int i = 0; i <= a + b; ++i){
      ans[2 * (length + i + 1)] = (ans[2 * (length + i + 1)] + A[i]) % mod;
    }
  }
  cin >> Q;
  for(int i = 1; i <= Q; ++i){
    int qi; cin >> qi;
    cout << (ans[qi] + mod) % mod << endl;
  }
}
