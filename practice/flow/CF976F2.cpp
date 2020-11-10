#include <bits/stdc++.h>
using namespace std;
typedef pair<int , int> ii;
typedef long long ll;
 
const int maxn = 5000;
const double INF = 1e18;
const double ep = 1e-8;
 
struct Edge {
  int from, to;
  double cap, flow;
  int id;
  Edge(){}
  Edge(int u, int v, double c, double f , int id_) : from(u), to(v), cap(c), flow(f) , id(id_) {}
};
 
struct Dinic {
  int n, m, s, t;
  vector<Edge> edges;
  vector<int> G[maxn];
  int d[maxn], cur[maxn];
  bool vis[maxn];
 
  void init(int n) {
    for (int i = 0; i < maxn; i++) G[i].clear();
    edges.clear();
  }
 
  void add(int from, int to, double cap , int id) {
    edges.push_back(Edge(from, to, cap, 0 , id));
    edges.push_back(Edge(to, from, 0 , 0 , id));
    m = edges.size();
    G[from].push_back(m - 2);
    G[to].push_back(m - 1);
  }
 
  bool BFS() {
    memset(vis, 0, sizeof(vis));
    queue<int> Q;
    Q.push(s);
    d[s] = 0;
    vis[s] = 1;
    while (!Q.empty()) {
      int x = Q.front();
      Q.pop();
      for (int i = 0; i < G[x].size(); i++) {
        Edge& e = edges[G[x][i]];
        if (!vis[e.to] && e.cap - e.flow > ep) {
          vis[e.to] = 1;
          d[e.to] = d[x] + 1;
          Q.push(e.to);
        }
      }
    }
    return vis[t];
  }
 
  double DFS(int x, double a) {
    if (x == t || a == 0) return a;
    double flow = 0, f;
    for (int& i = cur[x]; i < G[x].size(); i++) {
      Edge& e = edges[G[x][i]];
      if (d[x] + 1 == d[e.to] && (f = DFS(e.to, min(a, e.cap - e.flow))) > 0) {
        e.flow += f;
        edges[G[x][i] ^ 1].flow -= f;
        flow += f;
        a -= f;
        if (a == 0) break;
      }
    }
    return flow;
  }
 
  double maxFlow(int s, int t) {
    this->s = s;
    this->t = t;
    double flow = 0;
    while (BFS()) {
      memset(cur, 0, sizeof(cur));
      flow += DFS(s, INF);
    }
    return flow;
  }
 
  void show(){
    for(auto& e : edges){
      printf("(%d -> %d) => cap = %f , flow = %f\n" , e.from , e.to , e.cap , e.flow);
    }
  }
 
  void DFS2(int v){
    vis[v] = true;
    for(int i = 0; i < G[v].size(); ++i){
      Edge e = edges[G[v][i]];
      if(!vis[e.to] && e.cap - e.flow > ep){
        DFS2(e.to);
      }
    }
  }
 
  void showMinCut(int v){
      DFS2(v);
      for(auto& e : edges){
        if(vis[e.from] && !vis[e.to] && e.cap != 0 && e.flow != 0)
            printf("(%d -> %d) => cap = %f , flow = %f\n" , e.from , e.to , e.cap , e.flow);
      }
  }
 
};
 
 
 
int N1 , N2 , M;
vector<ii> g[2005];
bool vis[2005];
int deg[4005];
map<int , map<int , int>> mp;
 
 
int s , t;
 
void solve(int K){
    for(int i = 1; i <= M; ++i)vis[i] = 0;
    Dinic G;
    G.init(N1 + N2 + 10);
    for(int i = 1; i <= N1; ++i){
        G.add(s , i , deg[i] - K , -1);
        for(auto& e : g[i]){
            G.add(i , e.first , 1 , e.second);
        }
    }
    for(int i = N1 + 1; i <= N2 + N1; ++i){
        G.add(i , t , deg[i] - K , -1);
    }
    ll ret = G.maxFlow(s , t);
    //G.show();
    printf("%lld " , M - ret);
    for(auto& e : G.edges){
        if(e.flow > 0 && e.cap - e.flow <= ep){ // saturated
            if(e.from >= 1 && e.from <= N1 && e.to >= N1 + 1 && e.to <= N1 + N2){
                vis[e.id] = 1;
            }
        }
    }
    for(int i = 1; i <= M; ++i){
        if(!vis[i])printf("%d " , i);
    }
    printf("\n");
}   
 
int main(){
    scanf("%d %d %d" , &N1 , &N2 , &M);
    for(int i = 1; i <= M; ++i){
        int x , y; scanf("%d %d" , &x , &y);
        g[x].emplace_back(y + N1 , i);
        ++deg[x]; ++deg[y + N1];
    }
    int min_deg = M + 10;
    for(int i = 1; i <= N1 + N2; ++i){
        min_deg = min(min_deg , deg[i]);
    }
    s = N1 + N2 + 10 - 2 , t = s + 1;
    printf("0\n");
    for(int k = 1; k <= min_deg; ++k){
        solve(k);
    }
}