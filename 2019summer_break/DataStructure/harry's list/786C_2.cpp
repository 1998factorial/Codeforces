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
struct Node{
  int sum , lc , rc;
}tree[maxn * 100];
int cnt;
int root[maxn];
int a[maxn];
int Next[maxn];
int pos[maxn];
int N;

void update(int l , int r , int& x , int y , int pos , int val){
  tree[++cnt] = tree[y];
  tree[cnt].sum += val;
  x = cnt;
  if(l == r)return;
  int mid = (l + r) >> 1;
  if(pos <= mid)
    update(l , mid , tree[x].lc , tree[y].lc , pos , val);
  else
    update(mid + 1 , r , tree[x].rc , tree[y].rc , pos , val);
}

int search(int l , int r , int x , int pos){
  if(l == r)return l;
  int mid = (l + r) >> 1;
  if(tree[tree[x].lc].sum >= pos)
    return search(l , mid , tree[x].lc , pos);
  return search(mid + 1 , r , tree[x].rc , pos - tree[tree[x].lc].sum);
}

int main(){
  cnt = 0;
  scanf("%d" , &N);
  for(int i = 1; i <= N; ++i){
    scanf("%d" , &a[i]);
    pos[i] = N + 1;
  }
  for(int i = N; i >= 1; --i){
    Next[i] = pos[a[i]];
    pos[a[i]] = i;
  }
  for(int i = 1; i <= N; ++i){
    update(1 , N + 1 , root[1] , root[1] , pos[i] , 1);
  }
  for(int i = 2; i <= N; ++i){
    update(1 , N + 1 , root[i] , root[i - 1] , i - 1 , -1);
    update(1 , N + 1 , root[i] , root[i] , Next[i - 1] , 1);
  }
  for(int len = 1; len <= N; ++len){
    int i = 1 , ans = 0;
    while(i <= N){
      i = search(1 , N + 1 , root[i] , len + 1);
      ++ans;
    }
    printf("%d " , ans);
  }
}
