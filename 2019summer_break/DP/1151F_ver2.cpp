#include <iostream>
using namespace std;
typedef long long ll;

const int maxn = 1e2 + 10;
const ll mod = 1e9 + 7;
int N , K;
int a[maxn];
ll comb[maxn][maxn];
ll start[maxn] , finish[maxn];

struct Matrix{
  static const int maxn = 105;
  ll A[maxn][maxn];
  int n;

  Matrix(int n_): n(n_) {
    for(int i = 0; i < n; ++i)
      for(int j = 0; j < n; ++j)
        A[i][j] = 0;
  }

  Matrix operator * (const Matrix& o) const {
    Matrix ret(n);
    for(int i = 0; i < n; ++i)
      for(int j = 0; j < n; ++j)
        for(int k = 0; k < n; ++k){
          ll c = A[i][k] * o.A[k][j] % mod;
          ret.A[i][j] = (ret.A[i][j] + c) % mod;
        }
    return ret;
  }

  static Matrix identity(int n){
    Matrix ret(n);
    for(int i = 0; i < n; ++i)
      ret.A[i][i] = 1;
    return ret;
  }

  Matrix operator ^ (long long k) const {
    Matrix ret = identity(n);
    Matrix a = *this;
    while(k){
      if(k & 1)ret = ret * a;
      a = a * a;
      k /= 2;
    }
    return ret;
  }
};

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
  // think about the transition in matrices
  start[nzero] = 1;
  Matrix P(N + 1);
  for(int i = 0; i <= N; ++i){
    for(int j = 0; j <= N; ++j){
      if(j == i - 1){
        P.A[i][j] = mul(mul(cnt[0] - i + 1 , cnt[0] - i + 1) , inverse(comb[N][2]));
      }
      else if(j == i){
        ll val = add(comb[cnt[0]][2] , comb[cnt[1]][2]);
        val = add(val , mul(cnt[0] - i , i));
        val = add(val , mul(cnt[0] - i , cnt[1] - cnt[0] + i));
        P.A[i][j] = mul(val , inverse(comb[N][2]));
      }
      else if(j == i + 1){
        P.A[i][j] = mul(mul((ll)i + 1 , cnt[1] - cnt[0] + i + 1) , inverse(comb[N][2]));
      }
      else{
        P.A[i][j] = 0;
      }
    }
  }
  P = P ^ K;
  for(int i = 0; i <= N; ++i){
    for(int j = 0; j <= N; ++j){
      finish[i] = (finish[i] + P.A[i][j] * start[j] % mod) % mod;
    }
  }
  return finish[cnt[0]];
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
