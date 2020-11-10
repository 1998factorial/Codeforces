#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 30010;
const double INF = 1e18;
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

  void showMinCut(int v){
      DFS2(v);
      for(auto& e : edges){
        if(vis[e.from] && !vis[e.to] && e.cap != 0 && e.flow != 0)
            printf("(%d -> %d) => cap = %f , flow = %f\n" , e.from , e.to , e.cap , e.flow);
      }
  }

};

int N , M;
int art[110][110] , science[110][110] , same_art[110][110] , same_science[110][110];
int dir[5][2] = {{1 , 0} , {-1 , 0} , {0 , 1} , {0 , -1} , {0 , 0}};


int solve(){
    Dinic G;
    int tot = N * M * 3 + 3;
    int s = tot - 2 , t = tot - 1;
    G.init(tot);
    auto id = [&](int i , int j){
        return j + (i - 1) * M;
    };
    auto art_special = [&](int i , int j){
        return N * M + id(i , j);
    };
    auto science_special = [&](int i , int j){
        return N * M * 2 + id(i , j);
    };
    for(int i = 1; i <= N; ++i){
        for(int j = 1; j <= M; ++j){
            G.add(s , id(i , j) , art[i][j]);
            G.add(id(i , j) , t , science[i][j]);
            G.add(s , art_special(i , j) , same_art[i][j]);
            G.add(science_special(i , j) , t , same_science[i][j]);
            for(int x = 0; x < 5; ++x){
                int ni = i + dir[x][0];
                int nj = j + dir[x][1];
                if(ni < 1 || ni > N || nj < 1 || nj > M)continue;
                G.add(art_special(i , j) , id(ni , nj) ,  INF);
                G.add(id(ni , nj) , science_special(i , j) , INF);
            }
        }
    }
    return G.maxFlow(s , t);
}

int main(){
    int ret = 0;
    scanf("%d %d" , &N , &M);
    for(int i = 1; i <= N; ++i){
        for(int j = 1; j <= M; ++j){
            scanf("%d" , &art[i][j]);
            ret += art[i][j];
        }
    }
    for(int i = 1; i <= N; ++i){
        for(int j = 1; j <= M; ++j){
            scanf("%d" , &science[i][j]);
            ret += science[i][j];
        }
    }
    for(int i = 1; i <= N; ++i){
        for(int j = 1; j <= M; ++j){
            scanf("%d" , &same_art[i][j]);
            ret += same_art[i][j];
        }
    }
    for(int i = 1; i <= N; ++i){
        for(int j = 1; j <= M; ++j){
            scanf("%d" ,&same_science[i][j]);
            ret += same_science[i][j];
        }
    }
    printf("%d\n" , ret - solve());
}
