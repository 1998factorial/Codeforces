#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;

const int inf = 1e9;
const int maxn = 1e5 + 10;
int N;
int maxv[maxn] , minv[maxn];
int cnt1[maxn * 10 + 1] , cnt2[maxn * 10 + 1];
ll sum[maxn * 10 + 1];
bool yes[maxn];

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> N;
  int gmax = -1 , gmin = inf;
  for(int i = 1; i <= N; ++i){
    int len; cin >> len;
    int mx = -1 , mn = inf;
    int minpos = -1 , maxpos = -1;
    for(int j = 1; j <= len; ++j){
      int x; cin >> x;
      if(x > mn)yes[i] = 1;
      mx = max(mx , x);
      mn = min(mn , x);
    }
    if(!yes[i])cnt1[mn]++, cnt2[mx]++;
    maxv[i] = mx;
    minv[i] = mn;
    gmax = max(mx , gmax);
    gmin = min(gmin , mn);
  }
  ll ret = 0;
  sum[0] = cnt2[0];
  for(int i = 1; i <= gmax; ++i){
    sum[i] = sum[i - 1] + cnt2[i];
  }
  int over = 0;
  for(int i = 1; i <= N; ++i){
    int min_val = minv[i] , max_val = maxv[i];
    if(yes[i]){
      ++over;
      ret += 2 * N - 1;
    }
    else{
      ret += sum[gmax] - sum[min_val];
    }
  }
  cout << ret - (ll)over * (over - 1) << endl;
}
