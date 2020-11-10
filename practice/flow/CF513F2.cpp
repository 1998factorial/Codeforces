/*
    MaxFlow, rating 2700 - 2800
    first , we should be able to realise that we can do binary search on answer
    then, we need a way to check if maximal travel time is no more than T for all
    male and female to pair up. There is no obvious greedy / DP, it is even hard to
    think of an NP hard solution, so we should try flow.
    which cells can (i , j) get to under then maximal time constraint ? we first compute
    distance between each pair of cells, then all cells we can get to must satisfy :
    dis((i , j) , (x , y)) * speed <= T. this can be done using floyd
    Then , we can build a flow graph to model this.
    If there is no restriction on "maximal 1 pair for each cell", then we can
    do the following: get vertices for each male and female, get each vertices for
    each empty cell, connect src to each male with c = 1 , connect each male to
    the empty cells he can reach by c = 1 , connect each reachable cell to the female
    who can reach this cell by c = 1 , connect each female to sink by c = 1.
    check if max flow >= nmale. Now, with the restriction , we just need to put a
    capacity restriction on the cell node and we are done.
    Note that this is just a variation of the bipartite matching
*/
#include <bits/stdc++.h>
using namespace std;
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 5000;
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

char g[25][25];
int N , M;
int male[500][3] , female[500][3];
int nmale , nfemale;
int rboss , cboss , tboss;
ll dis[500][500];
int dir[4][2] = {{1 , 0} , {-1 , 0} , {0 , 1} , {0 , -1}};

bool solve(ll lim){
    Dinic G;
    int tot = nmale + nfemale + N * M * 2 + 3;
    int s = tot - 2;
    int t = tot - 1;
    G.init(tot);
    auto id = [&](int i , int j){
        return j + (i - 1) * M;
    };
    auto in = [&](int i , int j){
        return id(i , j);
    };
    auto out = [&](int i , int j){
        return N * M + id(i , j);
    };
    int base = N * M * 2;
    for(int i = 1; i <= N; ++i){
        for(int j = 1; j <= M; ++j){
            if(g[i][j] == '#')continue;
            G.add(in(i , j) , out(i , j) , 1);
        }
    }
    for(int x = 1; x <= nmale; ++x){
        G.add(s , x + base , 1);
        for(int i = 1; i <= N; ++i){
            for(int j = 1; j <= M; ++j){
                int id1 = id(male[x][0] , male[x][1]);
                int id2 = id(i , j);
                if(g[i][j] == '#')continue;
                if(dis[id1][id2] >= INF)continue;
                if(dis[id1][id2] * male[x][2] > lim)continue;
                G.add(x + base , in(i , j) , 1);
            }
        }
    }
    for(int x = 1; x <= nfemale; ++x){
        G.add(base + nmale + x , t , 1);
        for(int i = 1; i <= N; ++i){
            for(int j = 1; j <= M; ++j){
                int id1 = id(female[x][0] , female[x][1]);
                int id2 = id(i , j);
                if(g[i][j] == '#')continue;
                if(dis[id1][id2] >= INF)continue;
                if(dis[id1][id2] * female[x][2] > lim)continue;
                G.add(out(i , j) , base + nmale + x , 1);
            }
        }
    }
    ll ret = G.maxFlow(s , t);
    //cout << "checking " << lim << " flow = " << ret << endl;
    //G.showMinCut(s);
    return ret >= nmale;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> N >> M >> nmale >> nfemale;
    for(int i = 1; i <= N; ++i){
        for(int j = 1; j <= M; ++j){
            cin >> g[i][j];
        }
    }
    cin >> rboss >> cboss >> tboss;
    for(int i = 1; i <= nmale; ++i){
        cin >> male[i][0] >> male[i][1] >> male[i][2];
    }
    for(int i = 1; i <= nfemale; ++i){
        cin >> female[i][0] >> female[i][1] >> female[i][2];
    }
    if(abs(nmale - nfemale) != 1){
        cout << -1 << endl;
        return 0;
    }
    // boss can match with the extra one male / female
    if(nmale > nfemale){
        ++nfemale;
        female[nfemale][0] = rboss;
        female[nfemale][1] = cboss;
        female[nfemale][2] = tboss;
    }
    else{
        ++nmale;
        male[nmale][0] = rboss;
        male[nmale][1] = cboss;
        male[nmale][2] = tboss;
    }
    // compute shortest distance (pairwise)
    auto id = [&](int i , int j){
        return j + (i - 1) * M;
    };
    for(int i = 1; i <= N * M; ++i){
        for(int j = 1; j <= N * M; ++j){
            dis[i][j] = INF;
        }
    }
    for(int i = 1; i <= N; ++i){
        for(int j = 1; j <= M; ++j){
            if(g[i][j] == '#')continue;
            dis[id(i , j)][id(i , j)] = 0;
            for(int x = 0; x < 4; ++x){
                int di = i + dir[x][0];
                int dj = j + dir[x][1];
                if(di < 1 || di > N || dj < 1 || dj > M)continue;
                if(g[di][dj] == '#')continue;
                dis[id(i , j)][id(di , dj)] = 1;
            }
        }
    }
    // floyd warshall
    for(int k = 1; k <= N * M; ++k){
        for(int i = 1; i <= N * M; ++i){
            for(int j = 1; j <= N * M; ++j){
                dis[i][j] = min(dis[i][j] , dis[i][k] + dis[k][j]);
            }
        }
    }
    ll ret = -1 , l = 0 , r = 1e14;
    while(l <= r){
        ll mid = (l + r) >> 1;
        if(solve(mid)){
            ret = mid;
            r = mid - 1;
        }
        else{
            l = mid + 1;
        }
    }
    cout << ret << endl;
}
