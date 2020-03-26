#include <iostream>
#include <cstdio>
#include <string.h>
#include <algorithm>
using namespace std;
const int maxn = 1e5 + 10;
int N , a[maxn];
int ans[maxn];

int sum[maxn << 2];

int query(int l , int r , int x , int y , int id){
  if(l <= x && y <= r){
    return sum[id];
  }
  int m = (x + y) >> 1;
  if(m < l)
    return query(l , r , m + 1 , y , id << 1 | 1);
  if(m >= r)
    return query(l , r , x , m , id << 1);
  return query(l , r , x , m , id << 1) + query(l , r , m + 1 , y , id << 1 | 1);
}

void update(int pos , int l , int r , int id){
  if(l > r || pos < l || pos > r)return;
  if(pos == l && pos == r){
    sum[id]++;
  }
  else{
    int m = (l + r) >> 1;
    update(pos , l , m , id << 1);
    update(pos , m + 1 , r , id << 1 | 1);
    sum[id] = sum[id << 1] + sum[id << 1 | 1];
  }
}

void solve(){
  memset(sum , 0 , sizeof(sum));
  int up = 1;
  for(int i = 1; i <= N; ++i)up = max(up , a[i]);
  for(int i = 1; i <= N; ++i){
    update(a[i] , 1 , up , 1);
    //binary search for ans[i]
    int l = 0 , r = up;
    while(l <= r){
      int mid = (l + r) >> 1;
      if(query(mid , up , 1 , up , 1) >= mid){
        ans[i] = mid;
        l = mid + 1;
      }
      else{
        r = mid - 1;
      }
    }
  }
}


int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int T;
  cin >> T;
  for(int t = 1; t <= T; ++t){
    cin >> N;
    for(int i = 1; i <= N; ++i)cin >> a[i] , ans[i] = 0;
    solve();
    cout << "Case #" << t << ": ";
    for(int i = 1; i <= N; ++i)cout << ans[i] << " ";
    cout << endl;
  }
  return 0;
}
