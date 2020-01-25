#include <iostream>
#include <set>
using namespace std;
typedef pair<int , int> ii;
typedef long long ll;

const int maxn = 3e5 + 10;
int N , W;
multiset<ii> two , one;
int ans[maxn];
int cost[maxn][3];

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> N >> W;
  for(int i = 1; i <= N; ++i){
    for(int j = 1; j <= 2; ++j){
      cin >> cost[i][j];
    }
  }
  ll ret = 0;
  for(int i = 1; i <= N; ++i){
    two.insert(make_pair(cost[i][2] , i));
    ans[i] = 2;
    ret += cost[i][2];
  }
  int cur = 2 * N;
  while(cur > W){
    int c2 = 0 , b2 , c1 = 0 , b1;
    if(two.size()){
      auto it = two.rbegin();
      c2 = it->first;
      b2 = it->second;
    }
    if(one.size()){
      auto it = one.rbegin();
      c1 = it->first;
      b1 = it->second;
    }
    if(c2 > c1){
      ret -= c2;
      two.erase(two.find(make_pair(c2 , b2)));
      one.insert(make_pair(cost[b2][1] , b2));
      ret += cost[b2][1];
      --ans[b2];
    }
    else{
      ret -= c1;
      one.erase(one.find(make_pair(c1 , b1)));
      --ans[b1];
    }
    --cur;
  }
  cout << ret << endl;
  for(int i = 1; i <= N; ++i){
    cout << ans[i];
  }
  cout << endl;
}
