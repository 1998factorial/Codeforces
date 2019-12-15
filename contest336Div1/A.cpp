#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef pair<int,int> ii;
const int N = 1e5 + 10;
int n , dp[N] , p[N];
ii a[N];
//SAITAMA !!!!!!!!
int main(){
  cin >> n;
  for(int i = 1; i <= n; ++i){
    cin >> a[i].first >> a[i].second;
    p[i] = -1;
  }
  sort(a + 1 , a + 1 + n , [](ii x , ii y){
    return x.first < y.first;
  });
  vector<int> v;
  v.push_back(a[1].first);
  for(int i = 2; i <= n; ++i){
    //for each beacon : find the first beacon at its left that will not be affected
    v.push_back(a[i].first);
    auto it = lower_bound(v.begin() , v.end() , a[i].first - a[i].second);
    p[i] = it - v.begin();
  }
  dp[0] = 0;
  dp[1] = 1;
  int ret = 1;
  for(int i = 2; i <= n; ++i){
    dp[i] = dp[p[i]] + 1;
    ret = max(ret , dp[i]);
  }
  cout << n - ret << endl;
}
