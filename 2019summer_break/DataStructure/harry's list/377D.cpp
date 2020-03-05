#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl
using namespace std;
typedef long long ll;
typedef pair<int , int> ii;
/*
  convert to intersection of rectangles problem
*/
const int maxn = 3e5 + 10;
int limit;
int N;

struct worker{
  int l , v , r;
  worker(){}
  worker(int a , int b , int c) : l(a) , v(b) , r(c) {}
}W[maxn];

struct rec{
  int x , yl , yr , val;
  rec(){}
  rec(int a , int b , int c , int d) : x(a) , yl(b) , yr(c) , val(d) {}
  bool operator < (const rec rhs) const {
    if(x == rhs.x){
      return val < rhs.val;
    }
    return x < rhs.x;
  }
}R[maxn];

int tree[maxn << 2];
int lazy[maxn << 2];

void build(int l , int r , int id){
  if(l > r)return;
  if(l == r){
    tree[id] = lazy[id] = 0;
  }
  else{
    int mid = (l + r) >> 1;
    build(l , mid , id << 1);
    build(mid + 1 , r , id << 1);
    tree[id] = max(tree[id << 1] , tree[id << 1 | 1]);
  }
}

void push_down(int l , int r , int id){
  if(l < r){
    tree[id << 1] += lazy[id];
    tree[id << 1 | 1] += lazy[id];
    lazy[id << 1] += lazy[id];
    lazy[id << 1 | 1] += lazy[id];
    lazy[id] = 0;
  }
}

void update(int l , int r , int x , int y , int id , int val){
  if(l > r || r < x || l > y)return;
  if(l <= x && y <= r){
    tree[id] += val;
    lazy[id] += val;
  }
  else{
    int mid = (x + y) >> 1;
    push_down(x , y , id);
    update(l , r , x , mid , id << 1 , val);
    update(l , r , mid + 1 , y , id << 1 | 1 , val);
    tree[id] = max(tree[id << 1] , tree[id << 1 | 1]);
  }
}

int search(int l , int r , int id){
  if(l == r)return l;
  push_down(l , r , id);
  int mid = (l + r) >> 1;
  if(tree[id << 1] >= tree[1])
    return search(l , mid , id << 1);
  return search(mid + 1 , r , id << 1 | 1);
}

int main(){
  scanf("%d" , &N);
  limit = 0;
  for(int i = 1; i <= N; ++i){
    int l , r , v;
    scanf("%d %d %d" , &l , &v , &r);
    W[i] = worker(l , v , r);
    R[i] = rec(l , v , r , 1);
    R[i + N] = rec(v + 1 , v , r , -1);
    limit = max(limit , r + 1);
  }
  sort(R + 1 , R + 1 + 2 * N);
  int ret = 0;
  int bx = 0 , by;
  for(int i = 1; i <= 2 * N; ){
    int j = i;
    while(j <= 2 * N && R[j].x == R[i].x){
      update(R[j].yl , R[j].yr , 1 , limit , 1 , R[j].val);
      ++j;
    }
    //printf("at %d , max = %d\n" , R[i].x , tree[1]);
    if(ret < tree[1]){
      ret = tree[1];
      bx = R[i].x;
      by = search(1 , limit , 1);
    }
    i = j;
  }
  printf("%d\n" , ret);
  vector<int> ans;
  for(int i = 1; i <= N; ++i){
    if(
      W[i].l <= bx &&
      bx <= W[i].v &&
      W[i].v <= by &&
      by <= W[i].r
    ){
      ans.push_back(i);
    }
  }
  for(int i : ans)printf("%d " , i);
  printf("\n");
}
