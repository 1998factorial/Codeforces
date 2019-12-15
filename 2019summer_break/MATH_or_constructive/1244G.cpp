#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
using namespace std;
typedef long long ll;

int N;
ll K;
const int maxn = 1e6 + 10;
int ans[maxn];

int main(){
  cin >> N >> K;
  ll max_val = 0 , min_val = 0;
  for(int i = 1; i <= N; ++i){
    max_val += max(i , N - i + 1);
    min_val += i;
  }
  if(K < min_val){
    cout << -1 << endl;
  }
  else{
    for(int i = 1; i <= N; ++i)ans[i] = i;
    ll ret = min_val;
    int x = 1 , y = N;
    for(; x <= y; ++x){
      int lo = x , hi = y;
      int best = -1;
      while(lo <= hi){
        int mid = (lo + hi) >> 1;
        if(ret + mid - x <= K){
          best = mid;
          lo = mid + 1;
        }
        else{
          hi = mid - 1;
        }
      }
      if(best == -1)break;
      ret += best - x;
      swap(ans[x] , ans[best]);
      y = best - 1;
    }
    cout << ret << endl;
    for(int i = 1; i <= N; ++i) cout << i << " ";
    cout << endl;
    for(int i = 1; i <= N; ++i) cout << ans[i] << " ";
    cout << endl;
  }
}
