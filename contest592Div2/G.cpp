#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
typedef long long ll;

const int maxn = 1e6 + 10;
ll N , K , a[maxn];
ll ans[maxn];
int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> N >> K;
  ll min_val = 0 , max_val = 0;
  for(ll i = 1; i <= N; ++i){
    min_val += i;
    max_val += max(i , N - i + 1);
  }
  if(K < min_val)cout << -1 << endl;
  else{
    ll ret = min_val;
    for(ll i = 1; i <= N; ++i)ans[i] = i;
    ll x = 1 , y = N;
    for(; x < y; ++x){
      while(y > x && ret + y - x > K)--y;
      ret += y - x;
      swap(ans[x] , ans[y]);
      --y;
    }
    cout << ret << endl;
    for(ll i = 1; i <= N; ++i)cout << i << " ";
    cout << endl;
    for(ll i = 1; i <= N; ++i)cout << ans[i] << " ";
    cout << endl;
  }
}
