#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;
typedef long long ll;

const ll inf = 1e18;
const int maxn = 5e5 + 10;
int N , cnt , c[maxn << 1];

struct state{
  ll val , lazy , pos;
  state(){}
  state(ll a , ll b , ll c) : val(a) , lazy(b) , pos(c) {}
} tree[maxn << 3];

struct point{
  ll x , y , w;
  point(){}
  point(ll x_ , ll y_ , ll w_) : x(x_) , y(y_) , w(w_) {}
  bool operator < (const point& other) const {
    if(x != other.x)return x < other.x;
    return y < other.y;
  }
}P[maxn];

int getid(int x){ // index compression
  return lower_bound(c , c + cnt , x) - c;
}

state merge(state a , state b){
  state ret;
  if(a.val >= b.val){
    ret.val = a.val; ret.pos = a.pos;
  }
  else{
    ret.val = b.val; ret.pos = b.pos;
  }
  ret.lazy = 0;
  return ret;
}

void build(int l , int r , int id){
  if(l > r)return ;
  if(l == r){
    tree[id].lazy = 0;
    tree[id].val = -c[l];
    tree[id].pos = l;
  }
  else{
    int mid = (l + r) >> 1;
    build(l , mid , id << 1);
    build(mid + 1 , r , id << 1 | 1);
    tree[id] = merge(tree[id << 1] , tree[id << 1 | 1]);
  }
}

void push_down(int l , int r , int id){
  if(l < r && tree[id].lazy){
    tree[id << 1].val += tree[id].lazy;
    tree[id << 1].lazy += tree[id].lazy;
    tree[id << 1 | 1].val += tree[id].lazy;
    tree[id << 1 | 1].lazy += tree[id].lazy;
    tree[id].lazy = 0;
  }
}

state query(int l , int r , int x , int y , int id){
  if(l > r || x > r || y < l)return state(-inf , 0 , 0);
  if(l <= x && y <= r)return tree[id];
  push_down(x , y , id);
  int mid = (x + y) >> 1;
  if(mid < l)
    return query(l , r , mid + 1 , y , id << 1 | 1);
  if(mid >= r)
    return query(l , r , x , mid , id << 1);
  return merge(query(l , r , x , mid , id << 1) , query(l , r , mid + 1 , y , id << 1 | 1));
}

void update(int l , int r , int x , int y , int id , ll val){
  if(l > r || y < l || x > r)return;
  if(l <= x && y <= r){
    tree[id].val += val;
    tree[id].lazy += val;
    return;
  }
  int mid = (x + y) >> 1;
  push_down(x , y , id);
  update(l , r , x , mid , id << 1 , val);
  update(l , r , mid + 1 , y , id << 1 | 1 , val);
  tree[id] = merge(tree[id << 1] , tree[id << 1 | 1]);
}

void show(int l , int r , int id){
  if(l > r)return;
  printf("tree[%d %d] = (%lld , %lld , %lld)\n" , l , r , tree[id].val ,  tree[id].lazy , tree[id].pos);
  if(l == r)return;
  int m = (l + r) >> 1;
  show(l , m , id << 1);
  show(m + 1 , r , id << 1 | 1);
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> N; cnt = 0;
  for(int i = 0; i < N; ++i){
    cin >> P[i].x >> P[i].y >> P[i].w;
    c[cnt++] = P[i].x , c[cnt++] = P[i].y;
  }
  sort(c , c + cnt);
  cnt = unique(c , c + cnt) - c;
  build(0 , cnt - 1 , 1);
  for(int i = 0; i < N; ++i){
    int x = getid(P[i].x) , y = getid(P[i].y);
    int l = min(x , y) , r = max(x , y);
    update(r , cnt - 1 , 0 , cnt - 1 , 1 , P[i].w);
    P[i] = point(l , r , P[i].w);
  }
  show(0 , cnt - 1 , 1);
  sort(P , P + N);
  ll ret = 0 , s = 1e9 + 10 , e = 1e9 + 10;
  for(int i = 0; i < N;){
    int x = P[i].x , y = P[i].y;
    ll v = P[i].w;
    state ans = query(x , cnt - 1 , 0 , cnt - 1 , 1);
    ans.val += c[x];
    if(ans.val > ret){
      ret = ans.val;
      s = c[x];
      e = c[ans.pos];
    }
    int j = i;
    while(j < N && P[i].x == P[j].x){
      update(P[j].y , cnt - 1 , 0 , cnt - 1 , 1 , -P[j].w); ++j;
    }
    i = j;
  }
  cout << s << " " << s << " " << e << " " << e << endl;
}
