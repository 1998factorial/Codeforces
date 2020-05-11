#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl
using namespace std;
typedef long long ll;
typedef pair<ll , ll> ii;

ll D;
int N;
ll a[1005];

bool check(ll mid){
  ll cur = mid;
  for(int i = 2; i <= N; ++i){
    ll l = 1 , r = D / a[i];
    ll ret = -1;
    while(l <= r){
      ll m = (l + r) >> 1;
      if(m * a[i] >= cur){
        ret = m * a[i];
        r = m - 1;
      }
      else{
        l = m + 1;
      }
    }
    if(ret == -1)return 0;
    cur = ret;
  }
  return 1;
}

void solve(){
  cin >> N >> D;
  for(int i = 1; i <= N; ++i){
    cin >> a[i];
  }
  ll ret = a[1];
  ll l = 1 , r = D / a[1];
  while(l <= r){
    ll mid = (l + r) >> 1;
    if(check(mid * a[1])){
      ret = mid * a[1];
      l = mid + 1;
    }
    else{
      r = mid - 1;
    }
  }
  cout << ret << endl;
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int T; cin >> T;
  for(int t = 1; t <= T; ++t){
    cout << "Case #" << t << ": ";
    solve();
  }
}
