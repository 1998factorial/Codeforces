#include <iostream>
#include <algorithm>
#include <string.h>
#include <vector>
using namespace std;
typedef pair<int , int> ii;
typedef long long ll;

/*
  binary search answer
  [l , r] whole range +v
  -> [1 , l] +v
  -> [1 , r + 1] -v
*/

const int maxn = 505;
const int inf = 1e9;
int N , M , K;
ii point[maxn];
int mp[maxn * 4][maxn * 4];

bool check(int mid){
  vector<int> X , Y;
  memset(mp , 0 , sizeof(mp));
  for(int i = 1; i <= K; ++i){
    int x1 = max(1 , point[i].first - mid) , x2 = min(N , point[i].first + mid);
    int y1 = max(1 , point[i].second - mid) , y2 = min(M , point[i].second + mid);
    X.push_back(x1); X.push_back(x2);
    X.push_back(x1 - 1); X.push_back(x2 + 1);
    Y.push_back(y1); Y.push_back(y2);
    Y.push_back(y1 - 1); Y.push_back(y2 + 1);
  }
  X.push_back(0); X.push_back(1); X.push_back(N); X.push_back(N + 1);
  Y.push_back(0); Y.push_back(1); Y.push_back(M); Y.push_back(M + 1);
  sort(X.begin() , X.end()); X.erase(unique(X.begin() , X.end()) , X.end());
  sort(Y.begin() , Y.end()); Y.erase(unique(Y.begin() , Y.end()) , Y.end());
  for(int i = 1; i <= K; ++i){
    int x1 = max(1 , point[i].first - mid) , x2 = min(N , point[i].first + mid);
    int y1 = max(1 , point[i].second - mid) , y2 = min(M , point[i].second + mid);
    x1 = (lower_bound(X.begin() , X.end() , x1) - X.begin());
    x2 = (lower_bound(X.begin() , X.end() , x2) - X.begin());
    y1 = (lower_bound(Y.begin() , Y.end() , y1) - Y.begin());
    y2 = (lower_bound(Y.begin() , Y.end() , y2) - Y.begin());
    ++mp[x1][y1];
    --mp[x2 + 1][y1];
    --mp[x1][y2 + 1];
    ++mp[x2 + 1][y2 + 1];
  }
  int x1 = 0 , x2 = 0 , y1 = 0 , y2 = 0;
  for(int i = 1; i < X.size() - 1; ++i){
    for(int j = 1; j < Y.size() - 1; ++j){
      mp[i][j] += mp[i - 1][j] + mp[i][j - 1] - mp[i - 1][j - 1];
      if(mp[i][j] == 0){
        if(x1 == 0 || x1 > i)x1 = i;
        if(y1 == 0 || y1 > j)y1 = j;
        if(x2 == 0 || x2 < i)x2 = i;
        if(y2 == 0 || y2 < j)y2 = j;
      }
    }
  }
  return max(X[x2] - X[x1] , Y[y2] - Y[y1]) <= 2 * mid;
}

int main(){
  cin >> N >> M >> K;
  for(int i = 1; i <= K; ++i){
    cin >> point[i].first >> point[i].second;
  }
  ll l = 0 , r = max(N , M) , ret = r;
  while(l <= r){
    ll mid = (l + r) >> 1;
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
