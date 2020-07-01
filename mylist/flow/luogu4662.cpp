#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 5000;
const ll INF = 1e18;
const double ep = 1e-8;

struct Edge {
  int from, to;
  ll cap, flow;
  Edge(int u, int v, ll c, ll f) : from(u), to(v), cap(c), flow(f) {}
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

  void add(int from, int to, ll cap) {
    edges.push_back(Edge(from, to, cap, 0));
    edges.push_back(Edge(to, from, 0 , 0));
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

  double DFS(int x, ll a) {
    if (x == t || a == 0) return a;
    ll flow = 0, f;
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

  ll maxFlow(int s, int t) {
    this->s = s;
    this->t = t;
    ll flow = 0;
    while (BFS()) {
      memset(cur, 0, sizeof(cur));
      flow += DFS(s, INF);
    }
    return flow;
  }

  void show(){
    for(auto& e : edges){
      printf("(%d -> %d) => cap = %lld , flow = %lld\n" , e.from , e.to , e.cap , e.flow);
    }
  }

  void DFS2(int v){
    vis[v] = true;
    for(int i = 0; i < G[v].size(); ++i){
      Edge e = edges[G[v][i]];
      if(!vis[e.to] && e.cap - e.flow > 0){
        DFS2(e.to);
      }
    }
  }

  vector<int> showMinCut(int v){
      DFS2(v);
      vector<int> ret;
      for(auto& e : edges){
        if(vis[e.from] && !vis[e.to] && e.cap != 0 && e.flow != 0){
            ret.push_back(e.from);
        }
            //printf("(%d -> %d) => cap = %f , flow = %f\n" , e.from , e.to , e.cap , e.flow);
      }
      sort(ret.begin() , ret.end());
      return ret;
  }

};

int N , M;
int a , b;

int main(){
    Dinic G;
    scanf("%d %d" , &N , &M);
    scanf("%d %d" , &a , &b);
    int tot = 2 * N + 10;
    int s = a , t = b + N;
    G.init(tot);
    for(int i = 1; i <= N; ++i){
        int x; scanf("%d" , &x);
        G.add(i , N + i , x);
    }
    for(int i = 1; i <= M; ++i){
        int x , y; scanf("%d %d" , &x , &y);
        G.add(N + x , y , INF);
        G.add(N + y , x , INF);
    }
    G.maxFlow(s , t);
    vector<int> ret = G.showMinCut(s);
    for(int i : ret){
        printf("%d " , i);
    }
    printf("\n");
}
