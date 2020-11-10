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
int cnt[70];
int mask[70];
int pos[maxn];

bool canfix(int p){ // (1 << pos) in N can be obtain by some a[i]
  ll val = (1ll << p);
  for(int i = p; i >= 0 && val; --i){
    int j = 0;
    for(; j <= cnt[i] && (1ll << i) * j <= val; ++j);
    --j;
    val -= (1ll << i) * j;
  }
  return val == 0;
}

int main(){
  int T; scanf("%d" , &T);
  while(T--){
    scanf("%lld %lld" , &N , &M);
    for(int i = 0; i < 64; ++i){
      mask[i] = 0;
      cnt[i] = 0;
      if((1ll << i) & N)mask[i] = 1;
    }
    for(int i = 1; i <= M; ++i)
      scanf("%lld" , &a[i]);
    sort(a + 1 , a + 1 + M);
    for(int i = 1; i <= M; ++i)
      pos[i] = log2(a[i]);
    for(int i = 1; i <= M; ++i){
      cnt[pos[i]]++;
    }
    for(int i = 0; i < 64; ++i){
      if(mask[i] == 0)continue;
      if(canfix(i)){
        //cout << "can fix " << i << endl;
        mask[i] = 0;
        ll val = (1ll << i);
        for(int k = i; k >= 0 && val; --k){
          int j = 0;
          for(; j <= cnt[k] && (1ll << k) * j <= val; ++j);
          --j;
          val -= (1ll << k) * j;
          //cout << "using " << j << " " << "of cnt[" << k << endl;
          cnt[k] -= j;
        }
      }
    }
    /*for(int i = 0; i < 64; ++i){
      if(mask[i])printf("%d\n" , i);
    }*/
    int ok = 1;
    for(int i = 0; i < 64; ++i){
      if(mask[i])ok = 0;
    }
    if(ok){
      printf("0\n");
      continue;
    }
    int ret = 0;
    int found = 1;
    for(int i = 0; i < 64; ++i){
      if(mask[i]){
        int cando = 0;
        for(int j = i; j < 64; ++j){
          if(cnt[j]){
            //cout << "find " << j << " for " << i << endl;
            cando = 1;
            for(int k = j; k > i; --k){
              ++ret;
              --cnt[k];
              cnt[k - 1] += 2;
            }
            break;
          }
        }
        if(!cando){
          found = 0;
        }
      }
    }
    if(found){
      printf("%d\n" , ret);
    }
    else{
      printf("-1\n");
    }
  }
}
