#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl
using namespace std;
typedef long long ll;
typedef pair<int , int> ii;
/*
  data compression on IQ and X-co
  have N trees (each for different IQ)
  each tree is a dynamic tree, val[l , r] = number of reachable robots in range
*/
const int maxn = 1e5 + 10;
struct event{
  int pos , iq , type , id; // type = 0 , query , type = 1 , add , type = 2 , delete
  event(){}
  event(int a , int b , int c , int d) : pos(a) , iq(b) , type(c) , id(d){}
  bool operator < (const event rhs) const {
    if(pos == rhs.pos)return type > rhs.type;
    return pos < rhs.pos;
  }
} events[maxn * 3];

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






int X[maxn] , IQ[maxn] , R[maxn];
int N , K , tot;
unordered_map<int , int> mp , imp;
unordered_set<int> versions[maxn];

int main(){
  scanf("%d %d" , &N , &K);
  vector<int> tmp;
  for(int i = 1; i <= N; ++i){
    scanf("%d %d %d" , &X[i] , &R[i] , &IQ[i]);
    events[i] = event(max(X[i] - R[i] , 0) , IQ[i] , 1 , i);
    events[i + N] = event(X[i] , IQ[i] , 0 , i);
    events[i + N * 2] = event(min(X[i] + R[i] + 1 , 1000000000) , IQ[i] , 2 , i);
    tmp.push_back(IQ[i]);
  }
  sort(events + 1 , events + 1 + 3 * N);
  sort(tmp.begin() , tmp.end());
  tot = 1;
  for(int i : tmp){
    if(mp[i] == 0){
      mp[i] = tot; imp[tot] = i; ++tot;
    }
  }

  for(int i : tmp){
    for(int j = -K; j <= K; ++j){
      if(mp[i + j]){
        versions[mp[i]].insert(mp[i + j]);
      }
    }
  }
  ll ret = 0;
  for(int i = 1; i <= 3 * N; ++i){
    int iq = mp[events[i].iq];
    //DEBUG(events[i].pos);DEBUG(events[i].type);DEBUG(events[i].id);
    if(events[i].type == 0){
      // query
      for(int j : versions[iq]){
        ret += tree.query(max(0 , X[events[i].id] - R[events[i].id]) , X[events[i].id] , j);
        //cout << "at version = " << j << " " << 0 << " to " << events[i].pos << " = " << tree.query(0 , events[i].pos , j) << endl;
        //if(j == iq)--ret;
      }
    }
    if(events[i].type == 1){
      // add
      tree.update(X[events[i].id] , 1 , iq);

      //cout << "adding +1 at" << X[events[i].id] << endl;
    }
    if(events[i].type == 2){
      // delete
      tree.update(X[events[i].id] , -1 , iq);
      //cout << "adding -1 at" << X[events[i].id] << endl;
    }
    //DEBUG(ret);
  }
  printf("%lld\n" , ret - N);
}
