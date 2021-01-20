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
        if (!vis[e.to] && e.cap - e.flow > 0) {
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

int N , M , C;
char grid[35][35];
int v[35] , dir[4][2] = {{1 , 0} , {-1 , 0} , {0 , 1} , {0 , -1}};

int main(){
    cin >> M >> N >> C;
    for(int i = 1; i <= N; ++i){
        for(int j = 1; j <= M; ++j){
            cin >> grid[i][j];
        }
    }
    for(int i = 0; i < C; ++i)cin >> v[i];
    auto in = [&](int i , int j){
        return (i - 1) * M + j;
    };
    auto out = [&](int i , int j){
        return N * M + (i - 1) * M + j;
    };
    Dinic g;
    g.init(N * M * 2 + 10);
    int s = N * M * 2 + 8 , t = N * M * 2 + 7;
    for(int i = 1; i <= N; ++i){
        for(int j = 1; j <= M; ++j){
            if('a' <= grid[i][j] && grid[i][j] <= 'z'){
                g.add(in(i , j) , out(i , j) , v[grid[i][j] - 'a'] , 0);
            }
            else{
                g.add(in(i , j) , out(i , j) , INF , 0);
            }
            for(int k = 0; k < 4; ++k){
                int ni = i + dir[k][0] , nj = j + dir[k][1];
                if(ni < 1 || ni > N || nj < 1 || nj > M)continue;
                g.add(out(i , j) , in(ni , nj) , INF , 0);
            }
            if(grid[i][j] == 'B'){
                g.add(s , in(i , j) , INF , 0);
            }
            if(i == 1 || i == N || j == 1 || j == M){
                g.add(out(i , j) , t , INF , 0);
            }
        }
    }
    ll ret = g.maxFlow(s , t);
    if(ret < INF){
        cout << ret << endl;
    }
    else {
        cout << -1 << endl;
    }
}