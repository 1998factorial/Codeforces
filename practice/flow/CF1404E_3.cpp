/*
  the goal is to find minimal number of 1xn bricks to fill the black cells
  let the boarders between black cells be vertices
  we can not have L shape tile , so we need to find the size of maximal independent set
  ans = nblack_cell - maximal independent set
  since the graph is bipartitie so maximal independent set = nv - maximal bipartite matching
  we can use flow to do so
  O(N * M * sqrt(N * M))
*/
#include <bits/stdc++.h>
#define ID if(1)
using namespace std;
const int maxn = 2e5 + 10;
const double INF = 1e18;
const double ep = 1e-8;

struct Edge {
  int from, to;
  double cap, flow;
  Edge(){}
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
 
} G;

int N , M , s , t;
char MP[205][205];

int H(int i , int j){
    return i * M + j;
}

int V(int i , int j){
    return N * M + i * M + j;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int i , j , ans = 0 , tot = 0 , nv = 0;
    cin >> N >> M;
    tot = N * M * 3 + 10;
    G.init(tot);
    s = tot - 1 , t = tot - 2;
    for(i = 1; i <= N; ++i){
        for(j = 1; j <= M; ++j){
            cin >> MP[i][j];
        }
    }
    for(i = 1; i <= N; ++i){
        for(j = 1; j <= M; ++j){
            if(MP[i][j] == '#'){
                ++ans;
                if(i + 1 <= N && MP[i + 1][j] == '#'){
                    G.add(s , H(i , j) , 1);
                    ++nv;
                }
                if(j + 1 <= M && MP[i][j + 1] == '#'){
                    G.add(V(i , j) , t , 1);
                    ++nv;
                }
                // down to right
                if(i + 1 <= N && j + 1 <= M && MP[i + 1][j] == '#' && MP[i][j + 1] == '#'){
                    G.add(H(i , j) , V(i , j) , 1);
                }
                // down to left
                if(i + 1 <= N && j - 1 >= 1 && MP[i + 1][j] == '#' && MP[i][j - 1] == '#'){
                    G.add(H(i , j) , V(i , j - 1) , 1);
                }
                // up to left
                if(i - 1 >= 1 && j - 1 >= 1 && MP[i - 1][j] == '#' && MP[i][j - 1] == '#'){
                    G.add(H(i - 1 , j) , V(i , j - 1) , 1);
                }
                // up to right
                if(i - 1 >= 1 && j + 1 <= M && MP[i - 1][j] == '#' && MP[i][j + 1] == '#'){
                    G.add(H(i - 1 , j) , V(i , j) , 1);
                }
            }    
        }
    }
    //ID cout << "nv = " << nv << endl;
    cout << ans - (nv - G.maxFlow(s , t)) << endl;
}