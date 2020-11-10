#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

/*
  sliding window + binary search
  it is not hard to observe that the minimal defence power is monotonic
  we can check , can we use at most K archers to power up our defence,
  if the minimal defence power is mid
  the verification can be done by a sliding window
  but where to put the reinforcement?
  if v[i] is lower than mid, the best way to improve it is to add
  mid - v[i] archers at position min(N , i + R)
  this way , the reinforcement covers as much as possible the unchecked
  soilders, by exchange argument, this will not make the configuration any worse

  (A lot of greedy observation requires a "sense" , i feel like this can only
  be improved by praticing and thinking)
*/

const int maxn = 5e5 + 10;
int N , R;
ll K;
ll a[maxn] , prefixsum[maxn] , val[maxn] , delta[maxn];

bool check(ll mid){
  ll limit = K;
  ll power = 0;
  for(int i = 1; i <= N; ++i)delta[i] = 0;
  for(int i = 1; i <= 1 + R; ++i){
    power += a[i];
  }
  for(int i = 1; i <= N; ++i){
    if(power < mid){
      limit -= mid - power;
      if(limit < 0)return 0;
      delta[min(N , i + R)] += mid - power;
      power = mid;
    }
    if(i - R >= 1)power -= a[i - R] + delta[i - R];
    if(i + R + 1 <= N)power += a[i + R + 1] + delta[i + R + 1];
  }
  return 1;
}

int main(){
  scanf("%d %d %lld" , &N , &R , &K);
  ll ret = 0 , l = 0 , r = 0;
  for(int i = 1; i <= N; ++i){
    scanf("%lld" , &a[i]);
    r += a[i];
  }
  r += K;
  while(l <= r){
    ll mid = (l + r) >> 1;
    if(check(mid)){
      ret = mid;
      l = mid + 1;
    }
    else{
      r = mid - 1;
    }
  }
  printf("%lld\n" , ret);
}
