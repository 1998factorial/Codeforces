#include <bits/stdc++.h>
#define rep(i , a , b) for(int i = a; i <= b; ++i)
#define rrep(i , a , b) for(int i = a; i >= b; --i)
#define pb push_back
using namespace std;
const int maxn = 5000;
const double INF = 1e12;
const double ep = 1e-8;
int N , M;
char s[45][45];
bool vis[45][45];
int dir[4][2] = {{1 , 0} , {-1 , 0} , {0 , 1} , {0 , -1}};

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

int inside(int i , int j){
    return 0 <= i && i < N && 0 <= j && j < M;
}

void DFS(int i , int j){
    vis[i][j] = 1;
    rep(k , 0 , 3){
        int ni = i + dir[k][0] , nj = j + dir[k][1];
        if(!inside(ni , nj))continue;
        if(s[i][j] != 'L')continue;
        if(vis[ni][nj])continue;
        DFS(ni , nj);
    }   
}

int solve(){
    int initial_island = 0;
    rep(i , 0 , N - 1){
        rep(j , 0 , M - 1){
            if(vis[i][j])continue;
            if(s[i][j] != 'L')continue;
            ++initial_island;
            DFS(i , j);
        }
    }
    rep(i , 0 , N - 1){
        rep(j , 0 , M - 1){
            if(s[i][j] != 'L')continue;
            rep(k , 0 , 3){
                int ni = i + dir[k][0] , nj = j + dir[k][1];
                if(!inside(ni , nj))continue;
                if(s[ni][nj] == 'C')s[ni][nj] = 'W';
            }
        }
    }
    int tot = 0;
    Dinic G;
    auto id = [&](int i , int j){
        return i * M + j;
    };
    G.init(N * M + 10);
    int src = N * M + 8 , sink = N * M + 7;
    rep(i , 0 , N - 1){
        rep(j , 0 , M - 1){
            if(s[i][j] != 'C')continue;
            ++tot;
            if((i + j) & 1){
                G.add(src , id(i , j) , 1);
                rep(k , 0 , 3){
                    int ni = i + dir[k][0] , nj = j + dir[k][1];
                    if(!inside(ni , nj))continue;
                    if(s[ni][nj] == 'C')G.add(id(i , j) , id(ni , nj) , 1);
                }
            }
            else{
                G.add(id(i , j) , sink , 1);
            }
            
        }
    }
    return initial_island + tot - G.maxFlow(src , sink);
}

int main(){ 
    cin >> N >> M;
    rep(i , 0 , N - 1){
        rep(j , 0 , M - 1){
            cin >> s[i][j];
        }
    }
    cout << solve() << endl;
}   