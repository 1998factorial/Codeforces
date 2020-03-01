#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl
using namespace std;
typedef long long ll;
typedef pair<int , int> ii;

/*
  Notice that to paint a W x H rectangle, assume W < H, the cost will be
  W. However, with a cost of W, we could just paint W x N rectangle, which is
  obviously not worse (better in most cases)
  So, it is obvious that we should try to paint the minimal number of cols and rows to
  cover all black cells. So it make sense to do the following:
  if N is small, we can isolate each row and col, and connet only when (ri , cj) is black
  then this is a graph matching, all is left is just Dinics.
  Now, since N is large, we can not get all rows and cols, so we can compress on the coordinates
  of the black rectangles, for each virtual node in "row" , it will represent
  row[x[i] .... x[i + 1]] and similar for cols.
  and we connect row and col when the rectangle of them is covered by some black rectangles.
*/


const int maxn = 1500;
const ll INF = 1e12;
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
    double flow = 0;
    while (BFS()) {
      memset(cur, 0, sizeof(cur));
      flow += DFS(s, INF);
    }
    return flow;
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

int N , M;
struct rec{
  int x1 , y1 , x2 , y2;
}R[55];

unordered_map<int , int> xmp , ixmp , ymp , iymp;
int X , Y;

bool cover(int x1 , int x2 , int y1 , int y2){
  for(int i = 1; i <= M; ++i){
    if(
      R[i].x1 <= x1 &&
      x2 <= R[i].x2 &&
      R[i].y1 <= y1 &&
      y2 <= R[i].y2
    )
      return 1;
  }
  return 0;
}


int main(){
  cin >> N >> M;
  vector<int> ys , xs;
  for(int i = 1; i <= M; ++i){
    cin >> R[i].x1 >> R[i].y1 >> R[i].x2 >> R[i].y2;
    ++R[i].x2;
    ++R[i].y2;
    xs.push_back(R[i].x1);
    xs.push_back(R[i].x2);
    ys.push_back(R[i].y1);
    ys.push_back(R[i].y2);
  }
  sort(xs.begin() , xs.end());
  sort(ys.begin() , ys.end());
  X = Y = 1;
  for(int i : xs){
    if(!xmp[i]){
      xmp[i] = X; ixmp[X] = i; ++X;
    }
  }
  for(int i : ys){
    if(!ymp[i]){
      ymp[i] = Y; iymp[Y] = i; ++Y;
    }
  }
  Dinic g;
  g.init(X + Y + 2); // todo
  g.s = 0;
  g.t = X + Y + 1;
  for(int x = 2; x < X; ++x){
    g.add(g.s , x , ixmp[x] - ixmp[x - 1]);
  }
  for(int y = 2; y < Y; ++y){
    g.add(y + X , g.t , iymp[y] - iymp[y - 1]);
  }
  for(int x = 2; x < X; ++x){
    for(int y = 2; y < Y; ++y){
      if(cover(ixmp[x - 1] , ixmp[x] , iymp[y - 1] , iymp[y])){
        g.add(x , X + y , INF);
      }
    }
  }
  cout << g.maxFlow(g.s , g.t) << endl;
}
