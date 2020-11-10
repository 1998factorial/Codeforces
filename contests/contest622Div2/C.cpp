#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 5e5 + 10;
const int inf = 1e9 + 10;
int a[maxn] , N;
int ans[maxn];

struct node{
  int val , index;
  node(){}
  node(int a , int b): val(a) , index(b) {}
};

struct maxsegtree{
  node tree[maxn << 2];

  void init(){
    for(int i = 1; i <= (N << 2); ++i)tree[i] = node(inf , i);
  }

  node merge(node a , node b){
    if(a.val < b.val)return a;
    return b;
  }

  void update(int l , int r , int pos , int val , int id){
    if(l > r || pos < l || pos > r)return;
    if(l == r && pos == l){
      tree[id] = node(val , pos);
    }
    else{
      int mid = (l + r) >> 1;
      if(mid >= pos)
        update(l , mid , pos , val , id << 1);
      else
        update(mid + 1 , r , pos , val , id << 1 | 1);
      tree[id] = merge(tree[id << 1] , tree[id << 1 | 1]);
    }
  }

  node query(int l , int r , int x , int y , int id){
    if(l <= x && y <= r){
      return tree[id];
    }
    int mid = (x + y) >> 1;
    if(mid < l)
      return query(l , r , mid + 1 , y , id << 1 | 1);
    if(mid >= r)
      return query(l , r , x , mid , id << 1);
    return
    merge(query(l , r , x , mid , id << 1) ,
    query(l , r , mid + 1 , y , id << 1 | 1));
  }

} T;

int NEXT[maxn];

ll solve(int L , int R){
  if(L > R)return 0;
  node cur = T.query(L , R , 1 , N , 1);
  int idx = cur.index;
  ll val = cur.val;
  // either make all idx's right to val and solve on [L , idx - 1]
  ll sum_left = solve(L , idx - 1) + val * (R - idx + 1);
  // or make all idx's left to val and solve on [idx + 1 , R]
  ll sum_right = solve(idx + 1 , R) + val * (idx - L + 1);
  if(sum_left > sum_right){
    for(int i = idx; i <= R; ++i)ans[i] = val;
    return sum_left;
  }
  for(int i = idx; i >= L; --i)ans[i] = val;
  return sum_right;
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> N;
  T.init();
  for(int i = 1; i <= N; ++i){
    cin >> a[i];
    T.update(1 , N , i , a[i] , 1);
  }
  solve(1 , N);
  for(int i = 1; i <= N; ++i){
    cout << ans[i] << " ";
  }
  cout << endl;
}
