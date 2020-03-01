#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl
using namespace std;
typedef long long ll;
typedef pair<int , int> ii;

const int maxn = 1e5 + 10;
ll N , M;
ll a[maxn];
ll sum[maxn];
int pos[maxn];
int cnt[maxn];
int mask[maxn];

void solve(){
  for(int i = 0; i < 64; ++i){
    mask[i] = 0;
    if((1ll << i) & N){
      mask[i] = 1;
    }
    cnt[i] = 0;
  }
  for(int i = 1; i <= M; ++i){
    ++cnt[pos[i]];
  }
  int ret = 0;
  for(int i = 0; i < 64; ++i){
    if(mask[i] == 0){
      cnt[i + 1] += cnt[i] / 2;
    }
    else{
      if(cnt[i]){
        --cnt[i];
        cnt[i + 1] += cnt[i] / 2;
      }
      else{
        int j = i;
        for(; j < 64; ++j){
          if(cnt[j]){
            break;
          }
        }
        for(; j > i; --j){
          ++ret;
          --cnt[j] , cnt[j - 1] += 2;
        }
        --cnt[i];
        cnt[i + 1] += cnt[i] / 2;
      }
    }
  }
  printf("%d\n" , ret);
}

int main(){
  int T; scanf("%d" , &T);
  while(T--){
    scanf("%lld %lld" , &N , &M);
    sum[0] = 0;
    for(int i = 1; i <= M; ++i){
      scanf("%lld" , &a[i]);
      sum[i] = sum[i - 1] + a[i];
      pos[i] = log2(a[i]);
    }
    if(sum[M] < N)printf("-1\n");
    else solve();
  }
}
