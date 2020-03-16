#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl
using namespace std;
typedef long long ll;
typedef pair<int , int> ii;
/*
  the use of persistent range tree + binary search length
  key observation:
  if a subarray has k distinct numbers , then it's length is at least k
  therefore, if for each k = 1 .. N
    the worst case of the length of each subarrays is k.
    then we have at most N * (1 + 1 / 2 + .. + 1 / N) = O(NlogN) querys
    if for each query we can check the number of distinct values in [l , r] in logN time
    we will be able to solve this problem
    The online version of "distinct query" can be solved by using persistent range tree.
*/

const int maxn = 1e5 + 10;
int a[maxn];
struct Node{
  int sum , lson , rson , pre;
  Node():sum(0) , lson(-1) , rson(-1) , pre(-1){}
}tree[maxn * 80];
int root[maxn << 2];
int N , version , tot;
int pre[maxn];
int froot[maxn];
int ans[maxn];
int mp[maxn];
/*
  sweep from left to right, "add" a[i] each iteration into our persistent segment tree
  -> 1 for i
  -> 0 for pre[i]

  at the end , we will have N versions of persistent segment tree
  when query [l , r]
  segtree[version r] query l , r
*/

void push_up(int ver){
  tree[ver].sum = tree[tree[ver].lson].sum + tree[tree[ver].rson].sum;
}

int build(int l , int r){
  int cur = tot;
  ++tot;
  tree[cur] = Node();
  if(l == r)return cur;
  int mid = (l + r) >> 1;
  tree[cur].lson = build(l , mid);
  tree[cur].rson = build(mid + 1 , r);
  push_up(cur);
  return cur;
}

int query(int ver , int l , int r , int x , int y){
  if(l > r || l > y || x > r)return 0;
  if(l <= x && y <= r){
    return tree[ver].sum;
  }
  int mid = (x + y) >> 1;
  if(mid >= r)
    return query(tree[ver].lson , l , r , x , mid);
  if(mid < l)
    return query(tree[ver].rson , l , r , mid + 1 , y);
  return query(tree[ver].lson , l , r , x , mid) + query(tree[ver].rson , l , r , mid + 1 , y);
}

int update(int ver , int pos , int x , int y , int val){
  int cur = tot;
  ++tot;
  tree[cur] = Node();
  tree[cur].pre = ver;
  if(x == pos && pos == y){
    tree[cur].sum = val;
  }
  else{
    int mid = (x + y) >> 1;
    if(mid >= pos){
      tree[cur].lson = update(tree[ver].lson , pos , x , mid , val);
      tree[cur].rson = tree[ver].rson;
    }
    else{
      tree[cur].rson = update(tree[ver].rson , pos , mid + 1 , y , val);
      tree[cur].lson = tree[ver].lson;
    }
    push_up(cur);
  }
  return cur;
}

int main(){
  scanf("%d" , &N);
  pre[0] = 0;
  for(int i = 1; i <= N; ++i){
    scanf("%d" , &a[i]);
    pre[i] = mp[a[i]];
    mp[a[i]] = i;
  }
  version = tot = 0;
  root[version] = build(1 , N);
  for(int i = 1; i <= N; ++i){
    root[version + 1] = update(root[version] , i , 1 , N , 1);
    ++version;
    froot[i] = version;
    if(pre[i] == 0)continue;
    root[version + 1] = update(root[version] , pre[i] , 1 , N , 0);
    ++version;
    froot[i] = version;
  }
  for(int len = 1; len <= N; ++len){
    int i = 1;
    while(i <= N){
      int l = len , r = N , best = len;
      while(l <= r){
        int mid = (l + r) >> 1;
        int j = min(i + mid - 1 , N);
        if(query(root[froot[j]] , i , j , 1 , N) <= len){ // O(N * logN ^ 3) is too slow
          best = mid;
          l = mid + 1;
        }
        else{
          r = mid - 1;
        }
      }
      ++ans[len];
      i += best;
    }
  }
  for(int i = 1; i <= N; ++i){
    printf("%d " , ans[i]);
  }
}
