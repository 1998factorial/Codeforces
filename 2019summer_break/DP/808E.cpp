#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll , ll> ii;
/*
  Method :
  1. fixing one variable and check others
  2. dp with tuples
  3. greedy obervation (for each category sort items by their values)  

  1 <= w[i] <= 3
  if we only have one type or two type, then it is easy
  we can fix number of w[i] == 3 and consider the items
  with w[i] = 1 or 2 only
  dp[w] = (value , cnt[1] , cnt[2])
  we can use dp[w] to relax dp[w + 1] and dp[w + 2]
  at the end we just iterate on x and pick the maximal among
  them
*/
const int maxn = 1e5 + 10;
pair<ll , ii> dp[maxn * 3];
int N , M;
vector<int> a[4];

pair<ll , ii> max(pair<ll , ii> a , pair<ll , ii> b){
  pair<ll , ii> ret;
  if(a.first == b.first){
    if(a.second.first == b.second.first){
      ret = (a.second.second > b.second.second) ? a : b;
    }
    ret = (a.second.first > b.second.first) ? a : b;
  }
  ret = (a.first > b.first) ? a : b;
  return ret;
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> N >> M;
  for(int i = 1; i <= N; ++i){
    int w , c; cin >> w >> c;
    a[w].push_back(c);
  }
  for(int i = 1; i <= 3; ++i){
    sort(a[i].begin() , a[i].end());
    reverse(a[i].begin() , a[i].end());
  }
  dp[0] = make_pair(0 , make_pair(0 , 0));
  for(int i = 0; i < M; ++i){
    int j1 = dp[i].second.first , j2 = dp[i].second.second;
    ll val = dp[i].first;
    dp[i + 1] = max(dp[i] , dp[i + 1]);
    if(j1 < a[1].size())
      dp[i + 1] = max(dp[i + 1] , make_pair(val + a[1][j1] , make_pair(j1 + 1 , j2)));
    dp[i + 2] = max(dp[i] , dp[i + 2]);
    if(j2 < a[2].size())
      dp[i + 2] = max(dp[i + 2] , make_pair(val + a[2][j2] , make_pair(j1 , j2 + 1)));
  }
  ll ret = dp[M].first;
  ll tot = 0;
  for(int x = 0; x < a[3].size() && M - 3 * (x + 1) >= 0; ++x){
    tot += a[3][x];
    ret = max(ret , dp[M - 3 * (x + 1)].first + tot);
  }
  cout << ret << endl;
}
