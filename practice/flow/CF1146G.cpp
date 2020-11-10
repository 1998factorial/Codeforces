/*
    Flow (can also be solved by DP) , rating 2700
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 5000;
const double INF = 1e12;
const double ep = 1e-8;

struct Edge {
  int from, to;
  double cap, flow;
  Edge(int u, int v, double c, double f) : from(u), to(v), cap(c), flow(f) {}
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

  void add(int from, int to, double cap) {
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

};

int N , M , H;
int L[55] , R[55] , X[55] , C[55];

int id(int i , int j){
    return (H + 1) * (i - 1) + j;
}

int main(){
    cin >> N >> H >> M;
    Dinic G;
    G.init(N * (H + 1) + M + 2);
    int s = 0 , t = N * (H + 1) + M + 1;
    for(int i = 1; i <= N; ++i){
        G.add(s , id(i , 0) , INF);
        for(int j = 0; j < H; ++j){
            G.add(id(i , j) , id(i , j + 1) , H * H - j * j);
        }
    }
    for(int i = 1; i <= M; ++i){
        cin >> L[i] >> R[i] >> X[i] >> C[i];
        int to = N * (H + 1) + i;
        for(int x = L[i]; x <= R[i]; ++x){
            if(X[i] < H){
                G.add(id(x , X[i] + 1) , to , INF);
            }
        }
        G.add(to , t , C[i]);
    }
    cout << H * H * N - G.maxFlow(s , t) << endl;
}
