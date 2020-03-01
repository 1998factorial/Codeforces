#include <bits/stdc++.h>
using namespace std;

/*
  Ignore the fact that we can choose to erase one element
  to make the whole sequence strictly increasing, we need to find the
  least number of steps to make this happen.
  we can use DP to find the longest increasing sequence
  by transforming the sequence {a[i]} to {a[i] - i} (make sense intuitively)
  we can instead find the longest non decreasing sequence
  let pre[i] = the longest non decreasing sequence ending at a[i]
  this can be done by DP (N ^ 2) or we can have a max segment tree
  where tree[l .. r] = length LND ending at a[i] in {l .. r}

  Then, we consider the case where we can erase one element.
  we can enumerate on this element with a sweep from a[N] to a[1]
  this is like merging 2 sequences from [1 ... k - 1] and [k + 1 ... N]
  Here comes the greedy observation: each left sequence can end with
  a[1] .. a[N] , so when deleting a[k] , it is always not bad to choose
  the left sequence's ending = a[k - 1]. (as a[j] , j < k - 1 will be taken care of later)
  now , since we assume removal of a[k] , for i = k + 1 .. N , {a[i] - i} -> {a[i] - i + 1}
  so we are looking for the maximal length of some LND starting with element in
  [a[k - 1] - 1 , max{a[i]}]. this can be done with a max segment tree again
  ans = N - 1 - max{left seq + right seq}
*/

const int maxn = 2e5 + 10;
int a[maxn];
int N , tot;
unordered_map<int , int> mp , imp;
int pre[maxn] , suf[maxn];

struct maxtree{
  int tree[maxn << 3];

  void init(){
    memset(tree , 0 , sizeof(tree));
  }

  int query(int l , int r , int x , int y , int id){
    if(l <= x && y <= r){
      return tree[id];
    }
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

  void update(int l , int r , int pos , int val , int id){
    if(l > r || pos < l || pos > r)return;
    if(l == r && pos == l){
      tree[id] = max(tree[id] , val);
    }
    else{
      int mid = (l + r) >> 1;
      if(mid >= pos)
        update(l , mid , pos , val , id << 1);
      else
        update(mid + 1 , r , pos , val , id << 1 | 1);
      tree[id] = max(tree[id << 1] , tree[id << 1 | 1]);
    }
  }

} T;


int main(){
  scanf("%d" , &N);
  tot = 1;
  vector<int> tmp;
  for(int i = 1; i <= N; ++i){
    scanf("%d" , &a[i]);
    a[i] -= i;
    tmp.push_back(a[i]);
  }
  sort(tmp.begin() , tmp.end());
  for(int i : tmp){
    if(!mp[i]){
      mp[i] = tot;
      imp[tot] = i;
      ++tot;
    }
  }
  for(int i = 1; i <= N; ++i){
    a[i] = mp[a[i]];
    pre[i] = T.query(0 , a[i] , 0 , tot , 1) + 1;
    T.update(0 , tot , a[i] , pre[i] , 1);
  }
  T.init();
  int ans = N - 1 - pre[N - 1]; // delete the last element
  for(int i = N - 1; i >= 1; --i){
    suf[i + 1] = T.query(a[i + 1] , tot , 0 , tot , 1) + 1;
    T.update(0 , tot , a[i + 1] , suf[i + 1] , 1);
    if(mp[imp[a[i - 1]] - 1]){
      ans = min(ans , N - 1 - pre[i - 1] - T.query(a[i - 1] - 1 , tot , 0 , tot , 1));
    }
    else{
      ans = min(ans , N - 1 - pre[i - 1] - T.query(a[i - 1] , tot , 0 , tot , 1));
    }
  }
  printf("%d\n" , ans);
}
