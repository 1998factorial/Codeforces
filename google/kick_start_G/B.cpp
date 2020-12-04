#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl
using namespace std;
typedef long long ll;
typedef pair<int , int> ii;
typedef unsigned long long ull;

const int maxn = 1e3 + 10;
const ll inf = 1e18;
int N;
ll A[maxn];
ull cnt[60][2];
ull DP[60];
ll M;

ll solve(){
  memset(cnt , 0 , sizeof(cnt));
  memset(DP , 0 , sizeof(DP));
  //preprocess
  //find highest bit among A[1]...A[N] and M
  int high = 0;
  for(int i = 60; i >= 0; --i){
    int found = 0;
    for(int j = 1; j <= N && !found; ++j){
      if((1ll << i) & A[j]){
        found = 1;
      }
    }
    if(found){
      high = i;
      break;
    }
  }
  for(int i = 60; i >= 0; --i){
    if((1ll << i) & M){
      high = max(high , i);
      break;
    }
  }
  for(int i = 0; i <= high; ++i){
    for(int j = 1; j <= N; ++j){
      if((1ll << i) & A[j])
        ++cnt[i][1];
      else
        ++cnt[i][0];
    }
  }
  // find minimal sum up to ith bit
  for(int i = 0; i <= high; ++i){
    ll c = (cnt[i][0] < cnt[i][1]) ? cnt[i][0] : cnt[i][1];
    DP[i] = DP[i - 1] + (1ll << i) * c;
  }
  if(DP[high] > M)return -1;
  ull ret = 0;
  ull sum = 0;
  for(int i = high; i >= 0; --i){
    // check if we can place 1 at this bit
    if(sum + (1ll << i) * cnt[i][0] + DP[i - 1] <= M){
      ret |= (1ll << i);
      sum += (1ll << i) * cnt[i][0];
    }
    else{
      sum += (1ll << i) * cnt[i][1];
    }
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
