#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 105;
const ll mod = 1e9 + 7;
int N;
ll K;

struct Matrix{
  ll A[maxn][maxn];
  int n;

  Matrix(){}

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

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> N >> K;
    Matrix M = Matrix(N);
    for(int i = 0; i < N; ++i){
        for(int j = 0; j < N; ++j){
            cin >> M.A[i][j];
        }
    }
    ll ret = 0;
    M = M ^ K;
    for(int i = 0; i < N; ++i){
        for(int j = 0; j < N; ++j){
            ret = (ret + M.A[i][j]) % mod;
        }
    }
    cout << ret << endl;
}
