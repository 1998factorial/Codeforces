#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl
using namespace std;
typedef long long ll;
typedef pair<int , int> ii;

const int maxn = 1e3 + 10;
const ll inf = 1e18;
int N;
ll A[maxn];
ll M;
const int f = 1 << 8;

ll solve(){
  ll ret = -1;
  for(int s = f - 1; s >= 0; --s){
    ll sum = 0;
    for(int i = 1; i <= N; ++i){
      sum += s ^ A[i];
    }
    if(sum <= M)return s;
  }
  return ret;
}

int main(){
  int T; scanf("%d" , &T);
  for(int t = 1; t <= T; ++t){
    scanf("%d %lld" , &N , &M);
    for(int i = 1; i <= N; ++i){
      scanf("%lld" , &A[i]);
    }
    printf("Case #%d: %lld\n" , t , solve());
  }
}
