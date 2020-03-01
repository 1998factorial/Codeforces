#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl
using namespace std;
typedef long long ll;
typedef pair<int , int> ii;

/*
  Greedy observation: if a robot with radius x can cover another robot with radius x + 1
  then obviously vice versa.
  we can use dynamic range tree to get range tree for each different IQ
  the memory amortized to NlogN

  when query, we say, for iq - K to iq + K trees, how many robots i can cover
  with range [x[i] - r[i] , x[i] + r[i]].
  and when updating, we add 1 at x[i] at tree[iq]
*/

const int maxn = 1e5 + 10;
struct robot{
  int x , r , iq;
  robot(){}
  robot(int a , int b , int c) : x(a) , r(b) , iq(c) {}
  bool operator < (const robot rhs) const {
    return r > rhs.r;
  }
}R[maxn];

struct dynamictree{
  // template for dynamictree
  struct node{
    int l , r , val;
    struct node *left , *right;
    node(int a , int b , int c): l(a) , r(b) , val(c) , left(NULL) , right(NULL){}
  };
  node *tree[maxn]; // each IQ
  node *add(node *rt , int pos , int l , int r , int val){
    if(l > r || pos < l || pos > r)return rt;
    if(rt == NULL){
      rt = new node(l , r , 0);
    }
    if(l == r && pos == r){
      rt->val += val;
      return rt;
    }
    int mid = (l + r) >> 1;
    if(pos <= mid){
      rt->left = add(rt->left , pos , l , mid , val);
    }
    else{
      rt->right = add(rt->right , pos , mid + 1 , r , val);
    }
    int v1 = rt->left == NULL ? 0 : rt->left->val;
    int v2 = rt->right == NULL ? 0 : rt->right->val;
    rt->val = v1 + v2;
    return rt;
  }

  int ask(node* rt , int l , int r){
    if(rt == NULL)return 0;
    if(l <= rt->l && rt->r <= r)return rt->val;
    int mid = (rt->l + rt->r) >> 1;
    if(r <= mid){
      return ask(rt->left , l , r);
    }
    if(l > mid){
      return ask(rt->right , l , r);
    }
    return ask(rt->left , l , r) + ask(rt->right , l , r);
  }

  void update(int pos , int val , int version){
    tree[version] = add(tree[version] , pos , 0 , 1000000000 , val);
  }

  int query(int l , int r , int version){
    return ask(tree[version] , l , r);
  }

} tree;

int N , K , tot;
unordered_map<int , int> mp;

int main(){
  scanf("%d %d" , &N , &K);
  vector<int> tmp;
  for(int i = 1; i <= N; ++i){
    scanf("%d %d %d" , &R[i].x , &R[i].r , &R[i].iq);
    tmp.push_back(R[i].iq);
  }
  sort(R + 1 , R + 1 + N);
  sort(tmp.begin() , tmp.end());
  tot = 1;
  for(int i : tmp){
    if(!mp[i]){
      mp[i] = tot; ++tot;
    }
  }
  ll ret = 0;
  for(int i = 1; i <= N; ++i){
    int q = R[i].iq;
    for(int k = -K; k <= K; ++k){
      if(mp[q + k]){
        ret += tree.query(max(R[i].x - R[i].r , 0) , min(R[i].x + R[i].r , 1000000000) , mp[q + k]);
      }
    }
    tree.update(R[i].x , 1 , mp[q]);
  }
  printf("%lld\n" , ret);
}
