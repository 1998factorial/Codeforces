#include <bits/stdc++.h>
#define rep(i , a , b) for(int i = a; i <= b; ++i)
using namespace std;
typedef long long ll;

const int maxn = 50010;
const int INF = 1e9;
const double ep = 1e-8;

struct Edge {
  int from, to;
  int cap, flow;
  Edge(int u, int v, int c, int f) : from(u), to(v), cap(c), flow(f) {}
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

  void add(int from, int to, int cap) {
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
        if (!vis[e.to] && e.cap - e.flow != 0) {
          vis[e.to] = 1;
          d[e.to] = d[x] + 1;
          Q.push(e.to);
        }
      }
    }
    return vis[t];
  }

  int DFS(int x, int a) {
    if (x == t || a == 0) return a;
    int flow = 0, f;
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

  int maxFlow(int s, int t) {
    this->s = s;
    this->t = t;
    int flow = 0;
    while (BFS()) {
      memset(cur, 0, sizeof(cur));
      flow += DFS(s, INF);
    }
    return flow;
  }

  void show(){
    for(auto& e : edges){
      printf("(%d -> %d) => cap = %d , flow = %d\n" , e.from , e.to , e.cap , e.flow);
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
            printf("(%d -> %d) => cap = %d , flow = %d\n" , e.from , e.to , e.cap , e.flow);
      }
  }

};

int N , M;
int A[110][110] , B[110][110];
int row[110][110][2];
int col[110][110][2];

int solve(){
    int tot = 5 * N * M + 3;
    Dinic G; G.init(tot);
    int s = tot - 2 , t = tot - 1;
    auto id = [&](int i , int j){
        return j + (i - 1) * M;
    };
    auto row1 = [&](int i , int j){
        return N * M + id(i , j);
    };
    auto row2 = [&](int i , int j){
        return N * M * 2 + id(i , j);
    };
    auto col1 = [&](int i , int j){
        return N * M * 3 + id(i , j);
    };
    auto col2 = [&](int i , int j){
        return N * M * 4 + id(i , j);
    };
    rep(i , 1 , N){
        rep(j , 1 , M){
            G.add(s , id(i , j) , A[i][j]);
            G.add(id(i , j) , t , B[i][j]);
        }
    }
    rep(i , 1 , N - 1){
        rep(j , 1 , M){
            G.add(s , row1(i , j) , row[i][j][0]);
            G.add(row2(i , j) , t , row[i][j][1]);
            G.add(row1(i , j) , id(i , j) , INF);
            G.add(row1(i , j) , id(i + 1 , j) , INF);
            G.add(id(i , j) , row2(i , j) , INF);
            G.add(id(i + 1 , j) , row2(i , j) , INF);
        }
    }
    rep(i , 1 , N){
        rep(j , 1 , M - 1){
            G.add(s , col1(i , j) , col[i][j][0]);
            G.add(col2(i , j) , t , col[i][j][1]);
            G.add(col1(i , j) , id(i , j) , INF);
            G.add(col1(i , j) , id(i , j + 1) , INF);
            G.add(id(i , j) , col2(i , j) , INF);
            G.add(id(i , j + 1) , col2(i , j) , INF);
        }
    }
    return G.maxFlow(s , t);
}

int main(){
    int ret = 0;
    scanf("%d %d" , &N , &M);
    rep(i , 1 , N){
        rep(j , 1 , M){
            scanf("%d" , &A[i][j]);
            ret += A[i][j];
        }
    }
    rep(i , 1 , N){
        rep(j , 1 , M){
            scanf("%d" , &B[i][j]);
            ret += B[i][j];
        }
    }
    rep(k , 0 , 1){
        rep(i , 1 , N - 1){
            rep(j , 1 , M){
                scanf("%d" , &row[i][j][k]);
                ret += row[i][j][k];
            }
        }
    }
    rep(k , 0 , 1){
        rep(i , 1 , N){
            rep(j , 1 , M - 1){
                scanf("%d" , &col[i][j][k]);
                ret += col[i][j][k];
            }
        }
    }
    printf("%d\n" , ret - solve());
}
