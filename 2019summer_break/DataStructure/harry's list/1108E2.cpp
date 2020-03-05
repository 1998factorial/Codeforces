#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl
using namespace std;
typedef long long ll;
typedef pair<int , int> ii;

const int maxn = 1e5 + 10;
int a[maxn];
int N , M;

struct interval{
  int l , r;
  interval(){}
  interval(int a , int b): l(a) , r(b) {}
}its[305];

vector<int> add[maxn];
vector<int> del[maxn];

struct maxtree{

  struct node{
    int val , lazy;
    node(){}
    node(int a , int b): val(a) , lazy(b){}
  };

  node tree[maxn << 2];

  void push_down(int l , int r , int id){
    if(l < r){
      tree[id << 1].val += tree[id].lazy;
      tree[id << 1 | 1].val += tree[id].lazy;
      tree[id << 1].lazy += tree[id].lazy;
      tree[id << 1 | 1].lazy += tree[id].lazy;
      tree[id].lazy = 0;
    }
  }

  node merge(node a , node b){
    node ret = node(0 , 0);
    if(a.val > b.val){
      ret.val = a.val;
    }
    else{
      ret.val = b.val;
    }
    return ret;
  }

  void build(int l , int r , int id){
    if(l > r)return;
    if(l == r){
      tree[id] = node(a[l] , 0);
    }
    else{
      int mid = (l + r) >> 1;
      build(l , mid , id << 1);
      build(mid + 1 , r , id << 1 | 1);
      tree[id] = merge(tree[id << 1] , tree[id << 1 | 1]);
    }
  }

  void update(int l , int r , int x , int y , int val , int id){
    if(l > r || l > y || r < x)return;
    if(l <= x && y <= r){
      tree[id].val += val;
      tree[id].lazy += val;
    }
    else{
      int mid = (x + y) >> 1;
      push_down(x , y , id);
      update(l , r , x , mid , val , id << 1);
      update(l , r , mid + 1 , y , val , id << 1 | 1);
      tree[id] = merge(tree[id << 1] , tree[id << 1 | 1]);
    }
  }

} tree;

void solve(){
  tree.build(1 , N , 1);
  ll ret = 0 , best = 0 , ncover = 0;
  for(int i = 1; i <= N; ++i){
    for(int v : add[i]){
      ++ncover;
      tree.update(its[v].l , its[v].r , 1 , N , -1 , 1);
    }
    ll min_ai = a[i] - ncover;
    if(ret < tree.tree[1].val - min_ai){
      ret = tree.tree[1].val - min_ai;
      best = i;
    }
    for(int v : del[i]){
      --ncover;
      tree.update(its[v].l , its[v].r , 1 , N , 1 , 1);
    }
  }
  printf("%lld\n" , ret);
  vector<int> good;
  for(int i = 1; i <= M; ++i){
    if(its[i].l <= best && its[i].r >= best)
      good.push_back(i);
  }
  printf("%d\n" , (int)good.size());
  for(int i : good)printf("%d " , i);
  printf("\n");
}

int main(){
  scanf("%d %d" , &N , &M);
  for(int i = 1; i <= N; ++i)scanf("%d" , &a[i]);
  for(int i = 1; i <= M; ++i){
    scanf("%d %d" , &its[i].l , &its[i].r);
    add[its[i].l].push_back(i);
    del[its[i].r].push_back(i);
  }
  solve();
}
