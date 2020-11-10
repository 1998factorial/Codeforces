#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdio>
#include <cmath>
using namespace std;
typedef long long ll;

const int maxn = 1e5 + 10;
ll sum[maxn];
vector<ll> a;
ll N , K;

bool check(ll mid){
  //fix a[i] as minimal
  for(int i = 0; i < N; ++i){
    ll nop = K - a[i] * (i + 1) + sum[i];
    if(nop < 0)break;
    ll R = a[i] + mid;
    auto it = upper_bound(a.begin() , a.end() , R);
    if(it == a.end())return true;
    int pos = it - a.begin();
    nop -= (sum[N - 1] - sum[pos] + a[pos]) - (N - pos) * R;
    if(nop >= 0)return true;
  }
  //fix a[i] as maximal
  for(int i = N - 1; i >= 0; --i){
    ll nop = K - (sum[N - 1] - sum[i] + a[i] - (N - i) * a[i]);
    if(nop < 0)break;
    ll L = a[i] - mid;
    auto it = lower_bound(a.begin() , a.end() , L);
    if(it == a.end())return true;
    int pos = it - a.begin();
    nop -= (a[pos] * (pos + 1) - sum[pos]);
    if(nop >= 0)return true;
  }
  return false;
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> N >> K;
  for(int i = 0; i < N; ++i){
    ll x;
    cin >> x;
    a.push_back(x);
  }
  sort(a.begin() , a.end());
  sum[0] = a[0];
  for(int i = 1; i < N; ++i){
    sum[i] = sum[i - 1] + a[i];
  }
  ll l = 0 , r = 1e18 , ret = r;
  while(l <= r){
    ll mid = (l + r) / 2;
    if(check(mid)){
      ret = mid;
      r = mid - 1;
    }
    else{
      l = mid + 1;
    }
  }
  cout << ret << endl;
}
