#include <bits/stdc++.h>
using namespace std;
typedef pair<int , int> ii;
typedef long long ll;

const int maxn = 5000;
const double INF = 1e18;
const double ep = 1e-8;

struct Edge {
  int from, to;
  ll cap, flow;
  int id;
  Edge(){}
  Edge(int u, int v, ll c, ll f , int id_) : from(u), to(v), cap(c), flow(f) , id(id_) {}
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

  void add(int from, int to, ll cap , int id) {
    edges.push_back(Edge(from, to, cap, 0 , id));
    edges.push_back(Edge(to, from, 0 , 0 , -1));
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

  ll DFS(int x, ll a) {
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
      if(!vis[e.to] && e.cap - e.flow > ep){
        DFS2(e.to);
      }
    }
  }

  void showMinCut(int v){
      DFS2(v);
      for(auto& e : edges){
        if(vis[e.from] && !vis[e.to] && e.cap != 0 && e.flow != 0)
            printf("(%d -> %d) => cap = %lld , flow = %lld\n" , e.from , e.to , e.cap , e.flow);
      }
  }

};



int N1 , N2 , M;
int deg[4005];
vector<int> ans[2005];

int s , t , tot;

int main(){
    Dinic G;
    scanf("%d %d %d" , &N1 , &N2 , &M);
    tot = N1 + N2 + 15;
    s = tot - 2 , t = tot - 1;
    G.init(tot);
    for(int i = 1; i <= M; ++i){
        int x , y; scanf("%d %d" , &x , &y);
        G.add(x , N1 + y , 1 , i);
        ++deg[x]; ++deg[y + N1];
    }
    int min_deg = M + 10;
    for(int i = 1; i <= N1 + N2; ++i){
        min_deg = min(min_deg , deg[i]);
    }
    for(int i = 1; i <= N1; ++i){
        G.add(s , i , deg[i] - min_deg , -1);
    }
    for(int i = 1; i <= N2; ++i){
        G.add(i + N1 , t , deg[i + N1] - min_deg , -1);
    }
    for(int k = min_deg; ~k; --k){
        G.maxFlow(s , t);
        for(auto& e : G.edges){
            if(e.from >= 1 && e.from <= N1 && e.to >= N1 + 1 && e.to <= N2 + N1){
                if(e.flow == 0 && e.cap == 1){
                    ans[k].push_back(e.id);
                }
            }
        }
        for(int i = 1; i <= N1; ++i){
            G.add(s , i , 1 , -1);
        }
        for(int i = 1; i <= N2; ++i){
            G.add(i + N1 , t , 1 , -1);
        }
    }
    for(int i = 0; i <= min_deg; ++i){
        printf("%d " , (int)ans[i].size());
        for(int j : ans[i]){
            printf("%d " , j);
        }
        printf("\n");
    }
}