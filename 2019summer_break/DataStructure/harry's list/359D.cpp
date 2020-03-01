#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl
using namespace std;
typedef long long ll;
typedef pair<int , int> ii;

const int maxn = 3e5 + 10;
int N;
int a[maxn];

int gcd(int a , int b){
  return a == 0 ? b : gcd(b % a , a);
}

struct gcdtree{
  int tree[maxn << 2];
  void build(int l , int r , int id){
    if(l > r)return;
    if(l == r){
      tree[id] = a[l];
    }
    else{
      int mid = (l + r) >> 1;
      build(l , mid , id << 1);
      build(mid + 1 , r , id << 1 | 1);
      tree[id] = gcd(tree[id << 1] , tree[id << 1 | 1]);
    }
  }

  int query(int l , int r , int x , int y , int id){
    if(l <= x && y <= r)return tree[id];
    int mid = (x + y) >> 1;
    if(mid < l)
      return query(l , r , mid + 1 , y , id << 1 | 1);
    if(mid >= r)
      return query(l , r , x , mid , id << 1);
    return gcd(
      query(l , r , x , mid , id << 1),
      query(l , r , mid + 1 , y , id << 1 | 1)
    );
  }

} T1;

struct mintree{
  int tree[maxn << 2];
  void build(int l , int r , int id){
    if(l > r)return;
    if(l == r){
      tree[id] = a[l];
    }
    else{
      int mid = (l + r) >> 1;
      build(l , mid , id << 1);
      build(mid + 1 , r , id << 1 | 1);
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

} T2;

bool check(int len){
  for(int i = 1; i + len - 1 <= N; ++i){
    int minimal = T2.query(i , i + len - 1 , 1 , N , 1);
    int gcdval = T1.query(i , i + len - 1 , 1 , N , 1);
    //printf("for [%d , %d] , gcd = %d , min = %d\n" , i , i + len - 1 , gcdval , minimal);
    if(minimal == gcdval)return 1;
  }
  return 0;
}

int main(){
  scanf("%d" , &N);
  for(int i = 1; i <= N; ++i)scanf("%d" , &a[i]);
  T1.build(1 , N , 1);
  T2.build(1 , N , 1);
  int l = 1 , r = N , length = 1;
  while(l <= r){
    int mid = (l + r) >> 1;
    if(check(mid)){
      length = mid;
      l = mid + 1;
    }
    else{
      r = mid - 1;
    }
  }
  //DEBUG(length);
  // construct
  int cnt = 0;
  vector<int> ret;
  for(int i = 1; i + length - 1 <= N; ++i){
    int minimal = T2.query(i , i + length - 1 , 1 , N , 1);
    int gcdval = T1.query(i , i + length - 1 , 1 , N , 1);
    if(minimal == gcdval)ret.push_back(i) , ++cnt;
  }
  printf("%d %d\n" , cnt , length - 1);
  for(int i : ret)printf("%d " , i);
  puts("\n");
}
