#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl
using namespace std;
typedef long long ll;
typedef pair<int , int> ii;

const int maxn = 1e5 + 10;
ll X[maxn] , Y[maxn];
int N;
ll sum[maxn][3];//(xi * xi + yi * yi) , xi , yi

ll solve(){
  ll ret = 0;
  for(int i = 1; i <= N; ++i){
    sum[i][0] = sum[i - 1][0] + X[i] * X[i] + Y[i] * Y[i];
    sum[i][1] = sum[i - 1][1] + X[i];
    sum[i][2] = sum[i - 1][2] + Y[i];
  }
  for(int i = 1; i <= N; ++i){
    ret += (ll)(i - 1) * (X[i] * X[i] + Y[i] * Y[i]);
    ret += sum[i - 1][0];
    ret -= sum[i - 1][1] * 2ll * X[i];
    ret -= sum[i - 1][2] * 2ll * Y[i];
  }
  return ret;
}

int main(){
  scanf("%d" , &N);
  for(int i = 1; i <= N; ++i){
    scanf("%lld %lld" , &X[i] , &Y[i]);
  }
  printf("%lld\n" , solve());
}
