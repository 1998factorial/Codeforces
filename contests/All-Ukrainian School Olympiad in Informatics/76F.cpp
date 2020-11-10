#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl
using namespace std;
typedef long long ll;
typedef pair<int , int> ii;
const int maxn = 1e5 + 10;
const int inf = 1e9 + 10;
/*
  eve[i] can reach eve[j] iff |x[i] - x[j]| <= V * |t[i] - t[j]|
  assume t[i] <= t[j]
  max{x[i] - x[j] , x[j] - x[i]} <= V * (t[j] - t[i])
  need to satisfy both:
  V * t[i] + x[i] <= V * t[j] + x[j] (1)
  V * t[i] - x[i] <= V * t[j] - x[j] (2)

  sort events by (1) and then by (2)
  let dp[i] = maximal number of events if we consider first i events and the last
  event we visit is the ith.
  dp[i] = max{dp[j] | eve[j] can reach eve[i]} + 1
  this can be speeded up to logN by maintaining a range max tree
  we just query maximal in [1 , V * t[i] - x[i]] (need data compression here)
  to handle the case where we can only start at (0 , 0), we just add a dummy event (0 , 0)
  and set all dp[i] to -inf at the beginning.
*/
struct maxtree{
  int tree[maxn << 3];

  void build(int l , int r , int id){
    if(l > r)return;
    if(l == r){
      tree[id] = -inf;
    }
    else{
      int mid = (l + r) >> 1;
      build(l , mid , id << 1);
      build(mid + 1 , r , id << 1 | 1);
      tree[id] = max(tree[id << 1] , tree[id << 1 | 1]);
    }
  }

  void update(int l , int r , int pos , int val , int id){
    if(l > r || pos < l || pos > r)return;
    if(l == r && pos == l){
      tree[id] = val;
    }
    else{
      int mid = (l + r) >> 1;
      if(pos <= mid){
        update(l , mid , pos , val , id << 1);
      }
      else{
        update(mid + 1 , r , pos , val , id << 1 | 1);
      }
      tree[id] = max(tree[id << 1] , tree[id << 1 | 1]);
    }
  }

  int query(int l , int r , int x , int y , int id){
    if(l <= x && y <= r)return tree[id];
    int mid = (x + y) >> 1;
    if(mid < l)
      return query(l , r , mid + 1 , y , id << 1 | 1);
    if(mid >= r)
      return query(l , r , x , mid , id << 1);
    return max(
      query(l , r , x , mid , id << 1),
      query(l , r , mid + 1 , y , id << 1 | 1)
    );
  }

} T;


int N , V;
unordered_map<ll , ll> mp , imp;
int tot;
int ans[2];
int dp[maxn];
struct event{
  int x , t;
  event(){}
  event(int a , int b) : x(a) , t(b){}
  bool operator < (const event& rhs) const {
    if((ll)t * V + x == (ll)rhs.t * V + rhs.x){
      return (ll)t * V - x < (ll)rhs.t * V - rhs.x;
    }
    return (ll)t * V + x < (ll)rhs.t * V + rhs.x;
  }
} eve[maxn];

int main(){
  scanf("%d" , &N);
  for(int i = 1; i <= N; ++i){
    scanf("%d %d" , &eve[i].x , &eve[i].t);
  }
  scanf("%d" , &V);
  vector<ll> tmp;
  tmp.push_back(0);
  for(int i = 1; i <= N; ++i){
    tmp.push_back((ll)eve[i].t * V - eve[i].x);
  }
  sort(tmp.begin() , tmp.end());
  tot = 0;
  for(int i : tmp){
    if(!mp[i]){
      mp[i] = ++tot;
      imp[tot - 1] = i;
    }
  }
  // assume we can start at any where
  T.build(1 , tot , 1);
  sort(eve + 1 , eve + 1 + N);
  for(int i = 1; i <= N; ++i){
    dp[i] = 1;
    ll pos = (ll)eve[i].t * V - eve[i].x;
    dp[i] = max(
      dp[i] ,
      T.query(1 , mp[pos] , 1 , tot , 1) + 1
    );
    T.update(1 , tot , mp[pos] , dp[i] , 1);
    ans[1] = max(ans[1] , dp[i]);
  }
  // we can only start at (0 , 0)
  T.build(1 , tot , 1);
  eve[++N].x = 0 , eve[N].t = 0;
  sort(eve + 1 , eve + 1 + N);
  for(int i = 0; i <= N; ++i)dp[i] = -inf;
  for(int i = 1; i <= N; ++i){
    ll pos = (ll)eve[i].t * V - eve[i].x;
    if(eve[i].t == 0 && eve[i].x == 0)dp[i] = 0;
    dp[i] = max(
      dp[i] ,
      T.query(1 , mp[pos] , 1 , tot , 1) + 1
    );
    T.update(1 , tot , mp[pos] , dp[i] , 1);
    ans[0] = max(ans[0] , dp[i]);
  }
  printf("%d %d\n" , ans[0] , ans[1]);
}
