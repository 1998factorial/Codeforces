#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl
using namespace std;
typedef long long ll;
typedef pair<int , int> ii;

const int maxn = 1e5 + 10;
int N , Q;
double a[maxn];
double tree[maxn << 2] , add[maxn << 2] , mul[maxn << 2];

/*
  E[l1 .. r1] <- (r1 - l1) / (r1 - l1 + 1) * E[l1 .. r1] + (r1 - l1 + 1) * 1 / ((r1 - l1 + 1) * (r2 - l2 + 1)) * E[l2 .. r2]
  maintain a range tree with 2 lazy tags, mul and add.
  2 things to notice,
  1. mul before add
  2. when adding contribution from E[l2 .. r2] to E[l1 .. r1]
  x = 1 / (r2 - l2 + 1) * E[l2 .. r2] is added to the whole interval of [l1 .. r1]
  when we update, we need to split this contribution into x / (r1 - l1 + 1) units
  and then when we add it to some subinterval [x , y] of [l1 .. r1], we add
  (x / (r1 - l1 + 1)) * (y - x + 1) to [x , y]
*/


void build(int l , int r , int id){
  if(l > r)return;
  if(l == r){
    tree[id] = a[l];
    add[id] = 0;
    mul[id] = 1;
  }
  else{
    int mid = (l + r) >> 1;
    build(l , mid , id << 1);
    build(mid + 1 , r , id << 1 | 1);
    tree[id] = tree[id << 1] + tree[id << 1 | 1];
    add[id] = 0;
    mul[id] = 1;
  }
}

void push_down(int l , int r , int id){
  if(l < r){
    int mid = (l + r) >> 1;
    // mul first then add
    tree[id << 1] = mul[id] * tree[id << 1] + ((double)mid - l + 1) * add[id];
    tree[id << 1 | 1] = mul[id] * tree[id << 1 | 1] + ((double)r - mid) * add[id];
    add[id << 1] = mul[id] * add[id << 1] + add[id];
    add[id << 1 | 1] = mul[id] * add[id << 1 | 1] + add[id];
    mul[id << 1] *= mul[id];
    mul[id << 1 | 1] *= mul[id];
    mul[id] = 1;
    add[id] = 0;
  }
}

double query(int l , int r , int x , int y , int id){
  if(l <= x && y <= r){
    return tree[id];
  }
  int mid = (x + y) >> 1;
  push_down(x , y , id);
  if(mid < l){
    return query(l , r , mid + 1 , y , id << 1 | 1);
  }
  if(mid >= r){
    return query(l , r , x , mid , id << 1);
  }
  return query(l , r , x , mid , id << 1) + query(l , r , mid + 1 , y , id << 1 | 1);
}

void update(int l , int r , int x , int y , double mul_val , double add_val , int id){
  if(l > r || l > y || r < x)return;
  if(l <= x && y <= r){
    tree[id] = tree[id] * mul_val + (y - x + 1) * add_val;
    mul[id] *= mul_val;
    add[id] *= mul_val;
    add[id] += add_val;
  }
  else{
    int mid = (x + y) >> 1;
    push_down(x , y , id);
    update(l , r , x , mid , mul_val , add_val , id << 1);
    update(l , r , mid + 1 , y , mul_val , add_val , id << 1 | 1);
    tree[id] = tree[id << 1] + tree[id << 1 | 1];
  }
}

int main(){
  scanf("%d %d" , &N , &Q);
  for(int i = 1; i <= N; ++i){
    scanf("%lf" , &a[i]);
  }
  build(1 , N , 1);
  for(int q = 1; q <= Q; ++q){
    int t; scanf("%d" , &t);
    if(t == 1){
      int l1 , r1 , l2 , r2; scanf("%d %d %d %d" , &l1 , &r1 , &l2 , &r2);
      double v1 = query(l1 , r1 , 1 , N , 1);
      double v2 = query(l2 , r2 , 1 , N , 1);
      update(l1 , r1 , 1 , N , ((double)r1 - l1) / (r1 - l1 + 1) , 1.0 / (r1 - l1 + 1) * 1.0 / (r2 - l2 + 1) * v2 , 1);
      update(l2 , r2 , 1 , N , ((double)r2 - l2) / (r2 - l2 + 1) , 1.0 / (r2 - l2 + 1) * 1.0 / (r1 - l1 + 1) * v1 , 1);
    }
    if(t == 2){
      int l , r; scanf("%d %d" , &l , &r);
      printf("%lf\n" , query(l , r , 1 , N , 1));
    }
  }
}
