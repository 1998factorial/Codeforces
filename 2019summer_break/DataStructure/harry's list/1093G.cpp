#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl
using namespace std;
typedef long long ll;
typedef pair<int , int> ii;

const int maxn = 2e5 + 10;
const int inf = 1e9 + 10;
int a[maxn][5] , K , N , Q;

int val[maxn][1 << 5];

struct mintree{
  int tree[maxn << 2];

  void build(int l , int r , int id){
    if(l > r)return;
    if(l == r){
      tree[id] = inf;
    }
    else{
      int mid = (l + r) >> 1;
      build(l , mid , id << 1);
      build(mid + 1 , r , id << 1 | 1);
      tree[id] = min(tree[id << 1] , tree[id << 1 | 1]);
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
      tree[id] = min(tree[id << 1] , tree[id << 1 | 1]);
    }
  }

  int query(int l , int r , int x , int y , int id){
    if(l <= x && y <= r)return tree[id];
    int mid = (x + y) >> 1;
    if(mid < l)
      return query(l , r , mid + 1 , y , id << 1 | 1);
    if(mid >= r)
      return query(l , r , x , mid , id << 1);
    return min(
      query(l , r , x , mid , id << 1),
      query(l , r , mid + 1 , y , id << 1 | 1)
    );
  }

} T1[1 << 5];

struct maxtree{
  int tree[maxn << 2];

  void build(int l , int r , int id){
    if(l > r)return;
    if(l == r){
      tree[id] = -inf;
    }
    else{
      int mid = (l + r) >> 1;
      build(l , mid , id << 1);
      build(mid + 1 , r , id << 1 | 1);
      tree[id] = min(tree[id << 1] , tree[id << 1 | 1]);
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

} T2[1 << 5];

int main(){
  scanf("%d %d" , &N , &K);
  for(int s = 0; s < (1 << K); ++s){
    T1[s].build(1 , N , 1);
    T2[s].build(1 , N , 1);
  }
  for(int i = 1; i <= N; ++i){
    for(int j = 0; j < K; ++j){
      scanf("%d" , &a[i][j]);
    }
    for(int s = 0; s < (1 << K); ++s){
      int v = 0;
      for(int j = 0; j < K; ++j){
        if(((1 << j) & s) == 0)v += a[i][j];
        else v -= a[i][j];
      }
      val[i][s] = v;
      T1[s].update(1 , N , i , v , 1);
      T2[s].update(1 , N , i , v , 1);
    }
  }
  scanf("%d" , &Q);
  for(int q = 1;  q <= Q; ++q){
    int t; scanf("%d" , &t);
    if(t == 1){
      int pos; scanf("%d" , &pos);
      for(int i = 0; i < K; ++i)scanf("%d" , &a[pos][i]);
      for(int s = 0; s < (1 << K); ++s){
        int v = 0;
        for(int j = 0; j < K; ++j){
          if(((1 << j) & s) == 0)v += a[pos][j];
          else v -= a[pos][j];
        }
        val[pos][s] = v;
        T1[s].update(1 , N , pos , v , 1);
        T2[s].update(1 , N , pos , v , 1);
      }
    }
    else{
      int l , r; scanf("%d %d" , &l , &r);
      int ret = 0;
      for(int s = 0; s < (1 << K); ++s){
        ret = max(ret , T2[s].query(l , r , 1 , N , 1) - T1[s].query(l , r , 1 , N , 1));
      }
      printf("%d\n" , ret);
    }
  }
}
