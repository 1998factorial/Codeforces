#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl
using namespace std;
typedef long long ll;
typedef pair<int , int> ii;

const int maxn = 210;
const int maxm = 5e4 + 10;
const ll inf = 3e18 + 10;
int N , M;
ll G , S;
struct edge{
  ll from , to , g , s , pick;
  edge(){}
  edge(ll x , ll a , ll b , ll c , ll d) : from(x) , to(a) , g(b) , s(c) , pick(d) {}
};
vector<edge> edges;
int fa[maxn];

void init(){
  for(int i = 1; i <= N; ++i)
    fa[i] = i;
}

int find(int x){
  return fa[x] == x ? x : fa[x] = find(fa[x]);
}

void add(int x , int y){
  x = find(x); y = find(y);
  if(x != y)fa[x] = y;
}

ll solve(){
  sort(edges.begin() , edges.end() , [&](edge& a , edge& b){
    if(a.g == b.g){
      return a.s < b.s;
    }
    return a.g < b.g;
  });
  ll ret = inf;
  vector<edge> tree; // stores the spanning tree before i-th iteration
  for(int i = 0; i < (int)edges.size(); ++i){
    init();
    int ne = 0;
    tree.push_back(edges[i]);
    // forcing edges in tree are sorted by s
    // assume tree is sorted by s originally
    for(int j = tree.size() - 1; j > 0; --j){
      if(tree[j].s < tree[j - 1].s)swap(tree[j] , tree[j - 1]);
    }
    ll bs = 0, bg = 0;
    for(int j = 0; j < (int)tree.size(); ++j){
      if(find(tree[j].from) != find(tree[j].to)){
        ++ne;
        add(tree[j].from , tree[j].to);
        bs = max(bs , tree[j].s);
        bg = max(bg , tree[j].g);
        tree[j].pick = 1;
      }
    }
    if(ne == N - 1){ // we have a spanning tree of N nodes
      ret = min(ret , G * bg + S * bs);
    }
    vector<edge> tmp;
    for(edge& e : tree)
      if(e.pick){
        tmp.push_back(e);
      }
    tree.clear();
    for(edge& e: tmp){
      e.pick = 0;
      tree.push_back(e);
    }
  }
  return ret < inf ? ret : -1;
}

int main(){
  scanf("%d %d" , &N , &M);
  scanf("%lld %lld" , &G , &S);
  for(int i = 1; i <= M; ++i){
    int a , b , c , d; scanf("%d %d %d %d" , &a , &b , &c , &d);
    edges.emplace_back(a , b , c , d , 0);
  }
  printf("%lld\n" , solve());
}
