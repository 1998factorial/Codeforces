#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl
using namespace std;
typedef long long ll;
typedef pair<int , int> ii;

const int maxn = 1e5 + 10;
const int inf = 1e9 + 10;
int N , tot;


map<int , unordered_set<int>> cnt[maxn << 1];
unordered_map<int , int> mp;

struct spell{
  int a , b , c , d;
}spells[maxn];

struct state{
  int a , b , c , d , id;
  state(){}
  state(int a_ , int b_ , int c_ , int d_ , int id_) : a(a_) , b(b_) , c(c_) , d(d_) , id(id_) {}
};

int pre[maxn];
bool vis[maxn];

struct minsegtree{

  int tree[maxn << 3];

  void build(int l , int r , int id){
    if(l > r)return;
    if(l == r){
      tree[id] = inf;
    }
    else{
      int mid = (l + r) >> 1;
      build(l , mid , id << 1);
      build(mid + 1 , r , id << 1 | 1);
      tree[id] = min(tree[id << 1] , tree[id << 1 | 1]);
    }
  }

  void update(int l , int r , int pos , int Y , int ID , int id , int add){
    // adding or deleting an ID at cnt[pos][Y]
    if(l > r || pos < l || pos > r)return;
    if(l == r && pos == l){
      if(add){
        cnt[pos][Y].insert(ID);
        tree[id] = cnt[pos].begin()->first;
      }
      else{
        cnt[pos][Y].erase(ID);
        if(cnt[pos][Y].empty()){
          cnt[pos].erase(Y);
        }
        if(cnt[pos].empty()){
          tree[id] = inf;
        }
        else{
          tree[id] = cnt[pos].begin()->first;
        }
      }
      return ;
    }
    int mid = (l + r) >> 1;
    if(pos <= mid){
      update(l , mid , pos , Y , ID , id << 1 , add);
    }
    else{
      update(mid + 1 , r , pos , Y , ID , id << 1 | 1 , add);
    }
    tree[id] = min(tree[id << 1] , tree[id << 1 | 1]);
  }

  ii query(int l , int r , int x , int y , int maxY , int id){ // return the minimal y in range [0 , x] such that cnt[x][y] is non empty
    if(l > r || r < x || y < l)return make_pair(inf , -1);
    if(tree[id] > maxY)return make_pair(inf , -1);
    int mid = (x + y) >> 1;
    if(l <= x && y <= r){
      if(x == y){
        return make_pair(tree[id] , *cnt[x][tree[id]].begin());
      }
      if(tree[id << 1] <= maxY)
        return query(l , r , x , mid , maxY , id << 1);
      return query(l , r , mid + 1 , y , maxY , id << 1 | 1);
    }
    if(mid >= r)
      return query(l , r , x , mid , maxY , id << 1);
    if(mid < l)
      return query(l , r , mid + 1 , y , maxY , id << 1 | 1);
    return min(
      query(l , r , x , mid , maxY , id << 1) ,
      query(l , r , mid + 1 , y , maxY , id << 1 | 1)
    );
  }

}T;

int main(){
  scanf("%d" , &N);
  vector<int> tmp;
  for(int i = 1; i <= N; ++i){
    int a , b , c , d;
    scanf("%d %d %d %d", &spells[i].a , &spells[i].b , &spells[i].c , &spells[i].d);
    tmp.push_back(spells[i].a);
    tmp.push_back(spells[i].c);
  }
  tot = 1;
  tmp.push_back(0);
  sort(tmp.begin() , tmp.end());
  for(int i : tmp){ // data compression
    if(!mp[i]){
      mp[i] = tot; ++tot;
    }
  }
  T.build(0 , tot , 1);
  for(int i = 1; i <= N; ++i){
    T.update(0 , tot , mp[spells[i].a] , spells[i].b , i , 1 , 1);
    // add points
  }
  queue<pair<state , int>> q;
  q.push(make_pair(state(0 , 0 , 0 , 0 , 0) , 0));
  while(!q.empty()){
    pair<state , int> cur = q.front(); q.pop();
    state s = cur.first;
    //cout << s.a << " " << s.b << " " << s.c << " " << s.d << " " << s.id << endl;
    int dis = cur.second;
    if(!vis[s.id]){
      vis[s.id] = 1;
      if(s.id == N){
        vector<int> path;
        int start = N;
        while(start){
          path.push_back(start);
          start = pre[start];
        }
        reverse(path.begin() , path.end());
        printf("%d\n" , dis);
        for(int i : path)printf("%d ", i);
        puts("\n");
        return 0;
      }
      for(;;){
        ii ret = T.query(0 , mp[s.c] , 0 , tot , s.d , 1);
        if(ret.first >= inf || ret.second == -1)break;
        int x = ret.second;
        if(vis[x])continue;
        q.push(make_pair(state(spells[x].a , spells[x].b , spells[x].c , spells[x].d , x) , dis + 1));
        T.update(0 , tot , mp[spells[x].a] , spells[x].b , x , 1 , 0);
        pre[x] = s.id;
      }
    }
  }
  printf("-1\n");
}
