#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

/*
  check(x) = min{max(a[i][k] , a[j][k]) | 1 <= k <= M} >= x
  binary search
  let a[i][j] = (a[i][j] >= x)
  check is easy
*/

const int maxn = 3e5 + 10;
int N , M;
int a[maxn][8];
int mask[maxn];
int tot;
vector<int> g[1 << 8];

bool check(int x){
  unordered_map<int , int> cnt;
  for(int i = 1; i <= N; ++i){
    int val = 0;
    for(int j = 0; j < M; ++j){
      if(a[i][j] >= x){
        val |= (1 << j);
      }
    }
    mask[i] = val;
    cnt[mask[i]]++;
  }
  for(int i = 1; i <= N; ++i){
    for(int j = 0; j <= tot; ++j){
      if((j | mask[i]) == tot && cnt[j])return 1;
    }
    if(mask[i] == tot)return 1;
  }
  return 0;
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> N >> M;
  tot = (1 << M) - 1;
  for(int i = 1; i <= N; ++i){
    for(int j = 0; j < M; ++j){
      cin >> a[i][j];
    }
  }
  int l = 0 , r = 1e9 , best = -1;
  while(l <= r){
    int mid = (l + r) >> 1;
    if(check(mid)){
      best = mid;
      l = mid + 1;
    }
    else{
      r = mid - 1;
    }
  }
  for(int i = 1; i <= N; ++i){
    int val = 0;
    for(int j = 0; j < M; ++j){
      if(a[i][j] >= best){
        val |= (1 << j);
      }
    }
    g[val].push_back(i);
    mask[i] = val;
  }
  for(int i = 1; i <= N; ++i){
    for(int j = 0; j <= tot; ++j){
      if((mask[i] | j) == tot && g[j].size()){
        cout << i << " " << g[j][0] << endl;
        return 0;
      }
    }
  }
  return 0;
}
