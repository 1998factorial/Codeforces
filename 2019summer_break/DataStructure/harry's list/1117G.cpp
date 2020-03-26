#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl
using namespace std;
typedef long long ll;
typedef pair<int , int> ii;

/*
  f(i , j) = (j - i + 1) + f(i , mij - 1) + f(mij + 1 , j)
  where a[mij] = max{a[i]..a[j]}
  consider for each a[i], what contribution it can make
  to the left of a[i] , what is the minimal index that it can possbily affect ?
  it will be the maximal index j < i, where a[j] > a[i] (it can not go further)
  similar for the case if we go right
  so we can use monotonic stack to get L[i] and R[i] for each a[i] in O(N)
  after that, we can think which layer each a[i] is in.
  we sort query by l and sweep from left to right, [L[i] , i] += 1
  and query [ql , qr]
  then we sort query by r and sweep from right, [i , R[i]] += 1
  and query [ql , qr]
*/

const int maxn = 1e6 + 10;
int N , Q;
int perm[maxn];
int ql[maxn];
int qr[maxn];
vector<int> id;
int L[maxn]; // L[i] = maximal j such that a[j] > a[i]
int R[maxn]; // R[i] = minimal j such that a[j] > a[i]
ll ans[maxn];

struct sumtree{
  ll tree[maxn << 2];
  ll lazy[maxn << 2];

  void build(){
    memset(tree , 0 , sizeof(tree));
    memset(lazy , 0 , sizeof(lazy));
  }

  void push_down(int l , int r , int id){
    if(l < r){
      int mid = (l + r) >> 1;
      tree[id << 1] += lazy[id] * (mid - l + 1);
      tree[id << 1 | 1] += lazy[id] * (r - mid);
      lazy[id << 1] += lazy[id];
      lazy[id << 1 | 1] += lazy[id];
      lazy[id] = 0;
    }
  }

  ll query(int l , int r , int x , int y , int id){
    if(l > r || l > y || r < x)return 0;
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

  void update(int l , int r , int x , int y , ll val , int id){
    if(l > r || r < x || l > y)return;
    if(l <= x && y <= r){
      tree[id] += val * (y - x + 1);
      lazy[id] += val;
    }
    else{
      int mid = (x + y) >> 1;
      push_down(x , y , id);
      update(l , r , x , mid , val , id << 1);
      update(l , r , mid + 1 , y , val , id << 1 | 1);
      tree[id] = tree[id << 1] + tree[id << 1 | 1];
    }
  }

} T;

int main(){
  scanf("%d %d" , &N , &Q);
  for(int i = 1; i <= N; ++i){
    scanf("%d" , &perm[i]);
  }
  for(int i = 1; i <= Q; ++i){
    scanf("%d" , &ql[i]);
  }
  for(int i = 1; i <= Q; ++i){
    scanf("%d" , &qr[i]);
    id.push_back(i);
  }
  vector<int> stack;
  for(int i = 1; i <= N; ++i){
    while(!stack.empty() && perm[stack.back()] <= perm[i])stack.pop_back();
    if(stack.empty())L[i] = 1; // highest layer
    else L[i] = stack.back() + 1;
    stack.push_back(i);
  }
  stack.clear();
  for(int i = N; i >= 1; --i){
    while(!stack.empty() && perm[stack.back()] <= perm[i])stack.pop_back();
    if(stack.empty())R[i] = N;
    else R[i] = stack.back() - 1;
    stack.push_back(i);
  }
  sort(id.begin() , id.end() , [&](int x , int y){
    return qr[x] < qr[y];
  });
  T.build();
  int j = 1;
  for(int i : id){
    while(j <= N && j <= qr[i]){
      T.update(L[j] , j , 1 , N , 1 , 1);
      ++j;
    }
    ans[i] += T.query(ql[i] , qr[i] , 1 , N , 1);
  }
  sort(id.begin() , id.end() , [&](int x , int y){
    return ql[x] > ql[y];
  });
  T.build();
  j = N;
  for(int i : id){
    while(j >= 1 && j >= ql[i]){
      T.update(j , R[j] , 1 , N , 1 , 1);
      --j;
    }
    ans[i] += T.query(ql[i] , qr[i] , 1 , N , 1);
  }
  for(int i = 1; i <= Q; ++i){
    printf("%lld " , ans[i] - (qr[i] - ql[i] + 1));
  }
  puts("");
}
