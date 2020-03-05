#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl
using namespace std;
typedef long long ll;
typedef pair<int , int> ii;

const int maxn = 5e5 + 10;
ll N , K , R;
ll a[maxn] , delta[maxn];
ll sum;

bool check(ll x){
  ll lim = K , power = 0;
  memset(delta , 0 , sizeof(delta));
  for(int i = 1; i <= N && i <= R + 1; ++i)power += a[i];
  for(int i = 1; i <= N; ++i){
    if(power < x){
      int pos = min(N , i + R);
      delta[pos] += x - power; // add reinforcement at tower[pos]
      lim -= x - power;
      power = x;
    }
    if(lim < 0)return 0; // not enough reinforcement :(
    // need to get power for i + 1th
    if(i + R + 1 <= N){
      power += a[i + R + 1] + delta[i + R + 1];
    }
    // need to pop out
    if(i - R >= 1){
      power -= a[i - R] + delta[i - R];
    }
  }
  return 1;
}

int main(){
  scanf("%lld %lld %lld" , &N , &R , &K);
  sum = K;
  for(int i = 1; i <= N; ++i){
    scanf("%lld" , &a[i]);
    sum += a[i];
  }
  ll l = 0 , r = sum , ans = 0;
  while(l <= r){
    ll mid = (l + r) >> 1;
    if(check(mid)){
      ans = mid;
      l = mid + 1;
    }
    else{
      r = mid - 1;
    }
  }
  printf("%lld\n" , ans);
}
