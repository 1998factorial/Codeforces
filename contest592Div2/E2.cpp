#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdio>
#include <cmath>
using namespace std;
typedef long long ll;

const int maxn = 1e5 + 10;
ll sum[maxn];
ll a[maxn];
ll N , K;

bool check(ll mid){
  //fix a[i] as minimal
  int pos = 1;
  for(int i = 1; i <= N; ++i){
    while(pos <= N && a[i] + mid >= a[pos])++pos;
    ll val = a[i] * i - sum[i] + (sum[N] - sum[pos - 1]) - (N - pos + 1) * (a[i] + mid);
    if(val <= K){
      return true;
    }
  }
  //fix a[i] as maximal
  pos = N;
  for(int i = N; i >= 1; --i){
    while(pos >= 1 && a[i] - mid <= a[pos])--pos;
    ll val = (a[i] - mid) * pos - sum[pos] + (sum[N] - sum[i - 1]) - (N - i + 1) * a[i];
    if(val <= K){
      return true;
    }
  }
  return false;
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> N >> K;
  for(int i = 1; i <= N; ++i){
    cin >> a[i];
  }
  sort(a + 1 , a + 1 + N);
  sum[0] = 0;
  for(int i = 1; i <= N; ++i){
    sum[i] = sum[i - 1] + a[i];
  }
  ll l = 0 , r = a[N] - a[1] , ret = r;
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
