#include <iostream>
#include <algorithm>
using namespace std;
typedef long long ll;

const ll inf = 1e18;
const int maxn = 1e5 + 10;
int N , p;
ll t[maxn];
ll ans[maxn];

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> N >> p;
  for(int i = 1; i <= N; ++i)cin >> t[i];
  ll cur_time = 0;
  for(int i = 1; i <= N; ++i){
    ll min_val = inf;
    for(int j = 1; j <= N; ++j)min_val = min(min_val , t[j]);
    if(min_val <= cur_time){
      for(int j = 1; j <= N; ++j){
        if(t[j] <= cur_time){
          cur_time += p;
          ans[j] = cur_time;
          t[j] = inf;
          break;
        }
      }
    }
    else{
      for(int j = 1; j <= N; ++j){
        if(t[j] <= min_val){
          cur_time = min_val + p;
          ans[j] = cur_time;
          t[j] = inf;
          break;
        }
      }
    }
  }
  for(int i = 1; i <= N; ++i)cout << ans[i] << " ";
  cout << endl;
}
