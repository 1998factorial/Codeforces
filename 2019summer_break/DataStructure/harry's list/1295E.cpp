#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl
using namespace std;
typedef long long ll;
typedef pair<int , int> ii;

const int maxn = 2e5 + 10;
int p[maxn];
ll a[maxn];
int pos[maxn];
int N;
ll S[maxn];
ll tree[maxn << 2];
ll lazy[maxn << 2];

void build(int l , int r , int id){
  if(l > r)return ;
  if(l == r){
    tree[id] = S[r];
    lazy[id] = 0;
  }
  else{
    int mid = (l + r) >> 1;
    build(l , mid , id << 1);
    build(mid + 1 , r , id << 1 | 1);
    tree[id] = min(tree[id << 1] , tree[id << 1 | 1]);
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

void update(int l , int r , int x , int y , ll val , int id){
  if(l > r || r < x || y < l)return;
  if(l <= x && y <= r){
    tree[id] += val;
    lazy[id] += val;
  }
  else{
    int mid = (x + y) >> 1;
    push_down(x , y , id);
    update(l , r , x , mid , val , id << 1);
    update(l , r , mid + 1 , y , val , id << 1 | 1);
    tree[id] = min(tree[id << 1] , tree[id << 1 | 1]);
  }
}

ll query(int l , int r , int x , int y , int id){
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
  return min(
    query(l , r , x , mid , id << 1) ,
    query(l , r , mid + 1 , y , id << 1 | 1)
  );
}

int main(){
  scanf("%d" , &N);
  for(int i = 1; i <= N; ++i){
    scanf("%d" , &p[i]);
    pos[p[i]] = i;
  }
  for(int i = 1; i <= N; ++i){
    scanf("%lld" , &a[i]);
    S[i] = S[i - 1] + a[i];
  }
  build(1 , N , 1);
  ll ret = query(1 , N , 1 , N , 1);
  for(int val = 1; val <= N; ++val){
    int p = pos[val];
    update(p , N , 1 , N , -a[p] , 1);
    //cout << "update " << 1 << " " << p - 1 << " with " << a[p] << endl;
    update(1 , p - 1 , 1 , N , a[p] , 1);
    //cout << "update " << p << " " << N << " with " << -a[p] << endl;
    ret = min(ret , query(1 , N - 1 , 1 , N , 1));
  }
  printf("%lld\n" , ret);
}
