/*
    [CTSC1999] 星际转移问题
    Nice max flow problem (layer graph)
    to check if there exist a solution , we need to check if earth and moon are
    connected by some ships. This can be done using union find
    we can enumerate the answer , being the shortest time so that we can send all K
    ppl from earth to moon.
    we will gradually build up flow graph (with respect to time) to model the transportation of ppl.
    for each time , we will create one layer 1 ... earth , moon
    the ith node in jth layer means : the state of the ith station at time j
    we will connect (i , j) to (i , j + 1) with cap = inf , as ppl can stay
    and for each ship , we will find the station that this ship will be at time ans
    and get it's previous station , and connect them with cap = H[i]
    we will build this graph layer by layer and get extra flow , stop until the total flow is
    not less than K.
*/
#include <bits/stdc++.h>
#define ID 0
using namespace std;
typedef long long ll;

const int maxn = 1e5;
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

int N , M , K; // # space station , # space ship , # ppl on earth
int sz[50] , H[50] , g[50][50];

struct DSU{

    vector<int> fa;
    int N;

    void init(int n){
        N = n;
        fa.resize(n + 1);
        for(int i = 1; i <= N; ++i){
            fa[i] = i;
            if(ID)printf("fa[%d] = %d\n" , i , fa[i]);
        }
    }

    int find(int x){
        return fa[x] == x ? x : fa[x] = find(fa[x]);
    }

    void merge(int x , int y){
        x = find(x);
        y = find(y);
        if(x != y){
            fa[x] = y;
        }
    }

    void show(){
        for(int i = 1; i <= N; ++i){
            printf("fa[%d] = %d\n" , i , fa[i]);
        }
    }

} dsu;

// earth is 0 , moon is -1
int main(){
    cin >> N >> M >> K;
    int earth = N + 1 , moon = N + 2;
    for(int i = 1; i <= M; ++i){
        cin >> H[i] >> sz[i];
        for(int j = 0; j < sz[i]; ++j){
            int x; cin >> x;
            if(x == 0)g[i][j] = earth;
            else if(x == -1)g[i][j] = moon;
            else g[i][j] = x;
        }
    }
    // if earth and moon are connected by some space ship , then there will exist a solution
    dsu.init(N + 2);
    for(int i = 1; i <= M; ++i){
        for(int j = 0; j < sz[i]; ++j){
            if(ID)printf("g[%d][%d] = %d\n" , i , j , g[i][j]);
            if(j == 0){
                if(ID)cout << "joing " << g[i][j] << " " << g[i][sz[i] - 1] << endl;
                dsu.merge(g[i][j] , g[i][sz[i] - 1]);
            }
            else{
                if(ID)cout << "joing " << g[i][j] << " " << g[i][j - 1] << endl;
                dsu.merge(g[i][j] , g[i][j - 1]);
            }
        }
    }
    if(ID)dsu.show();
    if(dsu.find(moon) != dsu.find(earth)){
        printf("0\n"); return 0;
    }
    if(ID)printf("there exist solution\n");
    int ans = 1;
    Dinic G; G.init(maxn);
    int total_flow = 0;
    int s = maxn - 3 , t = maxn - 2;
    for(; total_flow < K; ++ans){
        // connect s -> (earth , ans) with cap = inf
        // connect (moon , ans) -> t with cap = inf
        if(ID)cout << "cur ans = " << ans << endl;
        G.add(s , (N + 2) * (ans - 1) + earth , INF);
        G.add((N + 2) * (ans - 1) + moon , t , INF);
        if(ID){
            cout << "adding from " << s << " to " << (N + 2) * (ans - 1) + earth << " with cap = " << INF << endl;
            cout << "adding from " << (N + 2) * (ans - 1) + moon << " to " << t << " with cap = " << INF << endl;
        }
        if(ans > 1){
            for(int i = 1; i <= moon; ++i){
                int pre = i + (N + 2) * (ans - 2) , cur = i + (N + 2) * (ans - 1);
                G.add(pre , cur , INF);
                if(ID){
                    cout << "adding from " << pre << " to " << cur << " with cap = " << INF << endl;
                }
            }
            for(int i = 1; i <= M; ++i){
                int cid = (ans - 1) % sz[i] , pid = (ans - 2) % sz[i];
                int vc = (N + 2) * (ans - 1) + g[i][cid] , vp = (N + 2) * (ans - 2) + g[i][pid];
                G.add(vp , vc , H[i]);
                if(ID){
                    cout << "adding from " << vp << " to " << vc << " with cap = " << H[i] << endl;
                }
            }
        }
        total_flow += G.maxFlow(s , t);
        if(total_flow >= K)break;
    }
    printf("%d\n" , ans - 1);
}
