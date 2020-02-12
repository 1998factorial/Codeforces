#include <bits/stdc++.h>
using namespace std;
typedef pair<int , int> ii;
typedef long long ll;

const int maxn = 3e5 + 10;
const ll inf = 1e9 + 10;
unordered_map<ll , ll> mp , imp;

struct channel{
  ll l , r , c , id;
  channel(){}
  channel(ll a , ll b , ll x , ll d) : l(a) , r(b) , c(x) , id(d) {}
} ch[maxn];

struct video{
  ll l , r , id;
  video(){}
  video(ll a , ll b , ll c) : l(a) , r(b) , id(c) {}
} vi[maxn];

struct maxsegtree{ // MAX segment tree with point update and range query
  int tree[maxn << 4];

  void update(int l , int r , int pos , int id , int val){
    if(l > r || pos < l || pos > r)return ;
    if(l == pos && pos == r){
      tree[id] = max(tree[id] , val);
    }
    else{
      int mid = (l + r) >> 1;
      update(l , mid , pos , id << 1 , val);
      update(mid + 1 , r , pos , id << 1 | 1 , val);
      tree[id] = max(tree[id << 1] , tree[id << 1 | 1]);
    }
  }

  ll query(int l , int r , int x , int y , int id){
    if(l > r || y < l || x > r)return 0;
    if(l <= x && y <= r){
      return tree[id];
    }
    int mid = (x + y) >> 1;
    if(mid >= r){
      return query(l , r , x , mid , id << 1);
    }
    if(mid < l){
      return query(l , r , mid + 1 , y , id << 1 | 1);
    }
    return max(
      query(l , r , x , mid , id << 1) ,
      query(l , r , mid + 1 , y , id << 1 | 1)
    );
  }

};

struct minsegtree{ // MAX segment tree with point update and range query
  int tree[maxn << 4];

  void init(){
    for(int i = 0; i < (maxn << 3); ++i)tree[i] = inf;
  }

  void update(int l , int r , int pos , int id , int val){
    if(l > r || pos < l || pos > r)return ;
    if(l == pos && pos == r){
      tree[id] = min(tree[id] , val);
    }
    else{
      int mid = (l + r) >> 1;
      update(l , mid , pos , id << 1 , val);
      update(mid + 1 , r , pos , id << 1 | 1 , val);
      tree[id] = min(tree[id << 1] , tree[id << 1 | 1]);
    }
  }

  ll query(int l , int r , int x , int y , int id){
    if(l > r || y < l || x > r)return inf;
    if(l <= x && y <= r){
      return tree[id];
    }
    int mid = (x + y) >> 1;
    if(mid >= r){
      return query(l , r , x , mid , id << 1);
    }
    if(mid < l){
      return query(l , r , mid + 1 , y , id << 1 | 1);
    }
    return min(
      query(l , r , x , mid , id << 1) ,
      query(l , r , mid + 1 , y , id << 1 | 1)
    );
  }

};


int N , M;
int tot = 0;
ll ans = 0;
int best = 0;
vector<ll> disc;


maxsegtree tree1 , tree2;
minsegtree tree3;


int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> N >> M;
  for(int i = 1; i <= N; ++i){
    cin >> vi[i].l >> vi[i].r; vi[i].id = i;
    disc.push_back(vi[i].l);
    disc.push_back(vi[i].r);
  }
  for(int j = 1; j <= M; ++j){
    cin >> ch[j].l >> ch[j].r >> ch[j].c; ch[j].id = j;
    disc.push_back(ch[j].l);
    disc.push_back(ch[j].r);
  }
  sort(disc.begin() , disc.end());
  tot = unique(disc.begin() , disc.end()) - disc.begin();
  // data compression
  for(int i = 0; i < tot; ++i){
    mp[disc[i]] = i;
    imp[i] = disc[i];
  }
  // fully covered interval check
  sort(vi + 1 , vi + 1 + N , [&](video a , video b){
    return a.r < b.r;
  });
  sort(ch + 1 , ch + 1 + M , [&](channel a , channel b){
    return a.r < b.r;
  });
  // process
  for(int i = 1 , j = 1; i <= M; ++i){
    while(j <= N && vi[j].r <= ch[i].r){
      tree1.update(0 , tot - 1 , mp[vi[j].l] , 1 , vi[j].r - vi[j].l);
      ++j;
    }
    ll len = tree1.query(mp[ch[i].l] , mp[ch[i].r] , 0 , tot - 1 , 1);
    if(ans < len * ch[i].c){
      ans = len * ch[i].c;
      best = ch[i].id;
    }
  }
  // partial covered
  tree3.init();
  for(int i = 1; i <= N; ++i){
    tree2.update(0 , tot - 1 , mp[vi[i].l] , 1 , vi[i].r);
    tree3.update(0 , tot - 1 , mp[vi[i].r] , 1 , vi[i].l);
  }
  for(int i = 1; i <= M; ++i){
    ll leftret = tree2.query(0 , mp[ch[i].l] - 1 , 0 , tot - 1 , 1);
    ll rightret = tree3.query(mp[ch[i].r] + 1 , tot - 1 , 0 , tot - 1 , 1);
    ll r1 = (ch[i].r - max(rightret , ch[i].l)) * ch[i].c;
    ll r2 = (min((ll)leftret , ch[i].r) - ch[i].l) * ch[i].c;
    if(ans < r1){
      ans = r1;
      best = ch[i].id;
    }
    if(ans < r2){
      ans = r2;
      best = ch[i].id;
    }
  }
  cout << ans << endl;
  if(ans > 0){
    ll bl , br , bc;
    for(int i = 1; i <= M; ++i)if(ch[i].id == best)bl = ch[i].l , br = ch[i].r , bc = ch[i].c;
    for(int i = 1; i <= N; ++i){
      ll l = max(bl , vi[i].l) , r = min(br , vi[i].r);
      ll val = r - l;
      if(val * bc == ans){
        cout << vi[i].id << " " << best << endl;
        return 0;
      }
    }
  }
}
