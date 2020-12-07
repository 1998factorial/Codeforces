#include <bits/stdc++.h>
#define x first
#define y second
using namespace std;
typedef pair<int , int> pii;
typedef long long ll;
const int maxn = 5000;
const double INF = 1e12;
const double ep = 1e-8;
int t , N , M , K;
int deg[605];
vector<int> g[605]; // edge id that need to be used by same company , attached to v

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

int main(){
    scanf("%d" , &t);
    while(t--){
        scanf("%d %d %d" , &N , &M , &K);
        vector<pii> edges;
        vector<vector<int>> id(N + 1 , vector<int> (N + 1));
        for(int i = 1; i <= N; ++i)deg[i] = 0 , g[i].clear();
        for(int i = 1; i <= M; ++i){
            int u , v;
            scanf("%d %d" , &u , &v);
            edges.emplace_back(u , v);
            ++deg[u];
            ++deg[v];
            id[u][v] = id[v][u] = i;
        }
        int ok = 1;
        for(int i = 1; i <= N && ok; ++i){
            if(deg[i] > 2 * K){
                ok = 0;
            }
        }
        if(!ok){
            for(int i = 1; i <= M; ++i){
                printf("0 ");
            }
            printf("\n");
        }
        else{
            Dinic D;
            D.init(N + M + 10);
            int s = N + M + 8 , t = N + M + 9;
            int min_edge_merge_needed = 0;
            for(int v = 1; v <= N; ++v){
                if(deg[v] > K){
                    int r = deg[v] - K;
                    D.add(s , v , 2 * r);
                    min_edge_merge_needed += 2 * r;
                }
            }
            for(int e = 1; e <= M; ++e){
                D.add(e + N , t , 1); // each edge can be the same colour as at most one other edge
                D.add(edges[e - 1].x , e + N , 1);
                D.add(edges[e - 1].y , e + N , 1);
            }
            int ret = D.maxFlow(s , t);
            //printf("flow = %d\n" , ret);
            if(min_edge_merge_needed == ret){
                vector<int> c(M + 1);
                int cur = 1;
                for(auto& e : D.edges){
                    if(1 <= e.from && e.from <= N && e.to > N && e.to <= N + M){
                        if(e.cap - e.flow == 0){
                            int v = edges[e.to - N - 1].x , u = edges[e.to - N - 1].y;
                            g[e.from].push_back(id[v][u]);
                        }
                    }
                }
                for(int v = 1; v <= N; ++v){
                    //printf("for v = %d : " , v);
                    for(int i = 0; i < g[v].size(); i += 2){
                        c[g[v][i]] = c[g[v][i + 1]] = cur;
                        ++cur;
                        //printf(" %d %d" , g[v][i] , g[v][i + 1]);
                    }
                }
                //cout << "cur = " << cur << endl;
                for(int e = 1; e <= M; ++e){
                    if(c[e])continue;
                    c[e] = cur;
                    ++cur;
                }
                for(int i = 1; i <= M; ++i){
                    printf("%d " , c[i]);
                }
                printf("\n");
            }
            else{
                for(int i = 1; i <= M; ++i){
                    printf("0 ");
                }
                printf("\n");
            }
        }
    }
}