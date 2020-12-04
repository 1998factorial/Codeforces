#include <iostream>
#include <string.h>
#include <algorithm>
#include <unordered_map>
using namespace std;
const int maxn = 1e5 + 10;
int N , S;
int A[maxn];
int pre[maxn] , ipre[maxn];
int P[maxn];
/*
  similar to last occurence , but last S occurence
  notice that it is impossible to generate solution by sliding window,
  so we need to consider all possible [l , r]
  but this is O(N ^ 2) , one trick is to fix r , and find optimal l
  each time we consider A[r] , set the sum at r be +1 , and pre[S][r] in sum be -S
  and pre[S + 1][r] be 0
  and we just query the maximal contiguous sum in A[1...r]
  This can be done by segment tree, each node maintains the largest sum starting from l,
  largest sum ending at r, actual sum of A[l...r], and finally, the solution in A[l...r]
  overrall time complexity = O(NlogN)
*/
struct state{
  int L , R , sum , best;
} tree[maxn << 2];

state merge(const state& left , const state& right){
  state ret;
  ret.sum = left.sum + right.sum;
  ret.L = max(left.L , left.sum + right.L);
  ret.R = max(right.R , left.R + right.sum);
  ret.best = max(left.best , right.best);
  ret.best = max(ret.best , left.R + right.L);
  return ret;
}

void update(int pos , int l , int r , int id , int val){
  if(pos < l || pos > r)return;
  if(pos == l && r == pos){
    tree[id].sum = val;
    tree[id].L = tree[id].R = tree[id].best = max(0 , val);
  }
  else{
    int m = (l + r) >> 1;
    if(pos <= m)
      update(pos , l , m , id << 1 , val);
    else
      update(pos , m + 1 , r , id << 1 | 1 , val);
    tree[id] = merge(tree[id << 1] , tree[id << 1 | 1]);
  }
}

state query(int l , int r , int x , int y , int id){
  if(l <= x && y <= r){
    return tree[id];
  }
  int m = (x + y) >> 1;
  state ret;
  if(m >= r){
    ret = query(l , r , x , m , id << 1);
    return ret;
  }
  if(m < l){
    ret = query(l , r , m + 1 , y , id << 1 | 1);
    return ret;
  }
  ret = merge(query(l , r , x , m , id << 1) , query(l , r , m + 1 , y , id << 1 | 1));
  return ret;
}

void init(){
  memset(P , 0 , sizeof(P));
  memset(pre , 0 , sizeof(pre));
  memset(ipre , 0 , sizeof(ipre));
  unordered_map<int , int> mp , fc , cnt; // first occurence
  for(int i = 1; i <= N; ++i){
    if(!fc[A[i]])fc[A[i]] = i;
    if(mp[A[i]]){
      pre[i] = mp[A[i]];
      ipre[pre[i]] = i;
    }
    mp[A[i]] = i;
    ++cnt[A[i]];
    if(cnt[A[i]] > S){
      P[i] = fc[A[i]];
      fc[A[i]] = ipre[fc[A[i]]];
    }
  }
}

int solve(){
  int ret = 0;
  memset(tree , 0 , sizeof(0));
  for(int i = 1; i <= N; ++i){
    update(i , 1 , N , 1 , 1);
    update(P[i] , 1 , N , 1 , -S);
    update(pre[P[i]] , 1 , N , 1 , 0);
    state rr = query(1 , i , 1 , N , 1);
    ret = max(ret , rr.best);
  }
  return ret;
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int T;
  cin >> T;
  for(int t = 1; t <= T; ++t){
    cin >> N >> S;
    for(int i = 1; i <= N; ++i){
      cin >> A[i];
    }
    init();
    cout << "Case #" << t << ": " << solve() << endl;
  }
  return 0;
}
