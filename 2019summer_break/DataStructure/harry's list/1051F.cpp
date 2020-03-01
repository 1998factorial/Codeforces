#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl
using namespace std;
typedef long long ll;
typedef pair<ll , ll> ii;

const int maxn = 1e5 + 10;
const ll inf = 1e18 + 10;
struct edge{
  int x , y , w;
  edge(){}
  edge(int a , int b , int c) : x(a) , y(b) , w(c) {}
  bool operator < (const edge rhs) const {
    return w < rhs.w;
  }
};
vector<ii> g[maxn]; // Graph in adj list
vector<ii> sptree[maxn]; // MST
vector<edge> edges; // Graph (in edges)
int N , M;
ll treedis[maxn]; // dis for MST
ll dis[maxn][50]; // dis for dijstra
bool vis[maxn][50]; // for dijstra
int a[maxn]; // union find for MST
vector<edge> notuse; // edges not in MST
set<int> starts; // vertices of the unused edges
unordered_map<int , int> mp , imp; // mapping of these vertices
int tot = 1;
int tin[maxn] , tout[maxn] , timmer;
int up[maxn][25];
int L;


int find(int x){
  return a[x] == x ? x : a[x] = find(a[x]);
}

void add(int x , int y){
  x = find(x);
  y = find(y);
  if(x != y) a[x] = y;
}

void MST(){
  for(int i = 1; i <= N; ++i)a[i] = i;
  sort(edges.begin() , edges.end());
  for(auto& e : edges){
    int x = e.x , y = e.y , w = e.w;
    if(find(x) != find(y)){
      add(x , y);
      sptree[x].emplace_back(y , w);
      sptree[y].emplace_back(x , w);
    }
    else{
      notuse.push_back(e);
    }
  }
}

void DFS(int v , int p){
  tin[v] = ++timmer;
  up[v][0] = p;
  for(int i = 1; i <= L; ++i){
    up[v][i] = up[up[v][i - 1]][i - 1];
  }
  for(auto& e : sptree[v]){
    int u = e.first , w = e.second;
    if(u != p){
      treedis[u] = treedis[v] + w;
      DFS(u , v);
    }
  }
  tout[v] = ++timmer;
}

void dijstra(int src , int f){
  for(int i = 1; i <= N; ++i){
    dis[i][f] = inf , vis[i][f] = 0;
  }
  dis[src][f] = 0;
  priority_queue<ii , vector<ii> , greater<ii>> q;
  q.push(make_pair(dis[src][f] , src));
  while(!q.empty()){
    int v = q.top().second; q.pop();
    if(!vis[v][f]){
      vis[v][f] = 1;
      for(auto& e : g[v]){
        int u = e.first , w = e.second;
        if(!vis[u][f] && dis[u][f] > dis[v][f] + w){
          dis[u][f] = dis[v][f] + w;
          q.push(make_pair(dis[u][f] , u));
        }
      }
    }
  }
}

bool isAncestor(int u , int v){
  return tin[u] <= tin[v] && tout[u] >= tout[v];
}

int LCA(int u, int v){
    if (isAncestor(u, v))
        return u;
    if (isAncestor(v, u))
        return v;
    for (int i = L; i >= 0; --i) {
        if (!isAncestor(up[u][i], v))
            u = up[u][i];
    }
    return up[u][0];
}

ll getTreeDis(int x , int y){
  return treedis[x] + treedis[y] - 2ll * treedis[LCA(x , y)];
}

int main(){
  scanf("%d %d" , &N , &M);
  for(int i = 1; i <= M; ++i){
    int x , y , d; scanf("%d %d %d" , &x , &y , &d);
    edges.emplace_back(x , y , d);
    g[x].emplace_back(y , d);
    g[y].emplace_back(x , d);
  }
  MST();
  timmer = 1;
  L = ceil(log2(N));
  DFS(1 , 1);
  for(auto& e : notuse){
    starts.insert(e.x);
    starts.insert(e.y);
  }
  // for all these start points, run dijstra
  for(int i : starts){
    mp[i] = tot; imp[tot] = i; ++tot;
  }
  for(int i = 1; i < tot; ++i){
    dijstra(imp[i] , i);
  }
  // Do some thing about LCA
  int Q; scanf("%d" , &Q);
  for(int i = 1; i <= Q; ++i){
    int x , y; scanf("%d %d" , &x , &y);
    // find minimal dist
    // either on MST or by dijstra
    ll ret = inf;
    ret = min(ret , getTreeDis(x , y));
    for(int i = 1; i < tot; ++i){
      ret = min(ret ,
        dis[x][i] + dis[y][i]
      );
    }
    printf("%lld\n" , ret);
  }
}
