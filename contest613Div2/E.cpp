#include <iostream>
#include <algorithm>
#include <set>
#include <vector>
using namespace std;
typedef pair<int , int> ii;

/*
  it is not hard to find the number of unioned intervals
  so maybe we should try to find what happens when we remove
  the i-th interval
  we can do this by sweeping
  we can consider each interval as open or close interval
  sort the intervals by left point then by right point
*/


const int inf = 1e9 + 10;
const int maxn = 2e5 + 10;
vector<ii> p;
int N;
int ans[maxn];

int solve(){
  p.clear();
  for(int i = 1; i <= N; ++i){
    int l , r; cin >> l >> r;
    p.emplace_back(l , -i);
    p.emplace_back(r , i);
    ans[i] = 0;
  }
  sort(p.begin() , p.end());
  set<int> s;
  int ret = 0;
  for(int i = 0; i < p.size(); ++i){
    if(p[i].second < 0){
      s.insert(-p[i].second);
    }
    else{
      s.erase(s.find(p[i].second));
    }
    if(s.size() == 0){
      ++ret;
    }
    if(s.size() == 1){
      if(i + 1 < p.size() && p[i].second > 0 && p[i + 1].second < 0 && p[i].first < p[i + 1].first){
        ans[*s.begin()]++;
      }
    }
  }
  int t = 0;
  for(int i = 1; i <= N; ++i){
    t = max(t , ans[i]);
  }
  if(ret == N)return N - 1;
  return ret + t;
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int T; cin >> T;
  for(int t = 1; t <= T; ++t){
    cin >> N;
    cout << solve() << endl;
  }
}
