#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
typedef long long ll;
typedef pair<int , int> ii;

const int maxn = 2e5 + 10;
int N;
ll S;
ii p[maxn];

bool check(ll x){
  //cout << "checking " << x << endl;
  ll ret = 0;
  vector<int> ps;
  int cnt = 0;
  for(int i = 1; i <= N; ++i){
    if(p[i].second < x){
      ret += p[i].first;
    }
    else if(p[i].first >= x){
      ret += p[i].first;
      ++cnt;
    }
    else{
      ps.push_back(p[i].first);
    }
  }
  //cout << cnt << " " << ps.size() << endl;
  if(cnt + ps.size() < N / 2 + 1)return false;
  for(int i = ps.size() - 1 , j = 0; i >= 0; --i , ++j){
    if(j < N / 2 + 1 - cnt){
      ret += x;
    }
    else{
      ret += ps[i];
    }
  }
  return ret <= S;
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int T; cin >> T;
  for(int t = 1; t <= T; ++t){
    cin >> N >> S;
    for(int i = 1; i <= N; ++i){
      cin >> p[i].first >> p[i].second;
    }
    sort(p + 1 , p + 1 + N);
    ll l = 0 , r = S , best = -1;
    while(l <= r){
      ll mid = (l + r) >> 1;
      if(check(mid))
        best = mid , l = mid + 1;
      else
        r = mid - 1;
    }
    cout << best << endl;
  }
}
