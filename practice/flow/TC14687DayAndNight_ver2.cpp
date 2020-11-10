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

class DayAndNight{
public:

    /*
        problem left from COMP4128
        we can build flow graph on "what is the minimal cost if we have exactly D - 1 day-night / night-day transit ?"
    */

    int minimalCost(vector<int> a, vector<int> b, vector<int> day, vector<int> night, int dayToNight, int nightToDay){
        int ret = 1e9 + 10;
        int N = day.size() , M = a.size();
        Dinic G;
        for(int u = 0; u < 2; ++u){
            for(int D = 1; D <= N; ++D){
                int tot = D * N + 2;
                int s = tot - 2 , t = tot - 1;
                G.init(tot + 1);
                auto id = [&](int i , int j){ // get node id
                    return i * D + j;
                };
                for(int i = 0; i < N; ++i){
                    int pre = s;
                    for(int j = 0; j < D; ++j){
                        int val = j & 1 ? day[i] : night[i];
                        G.add(pre , id(i , j) , val);
                        pre = id(i , j);
                    }
                    G.add(pre , t , INF);
                }
                for(int i = 0; i < M; ++i){ // forcing the order
                    for(int j = 0; j < D; ++j){
                        G.add(id(a[i] , j) , id(b[i] , j) , INF);
                    }
                }
                int cost = G.maxFlow(s , t);
                for(int j = 0; j < D - 1; ++j){
                    if(j & 1)cost += dayToNight;
                    else cost += nightToDay;
                }
                ret = min(ret , cost);
            }
            for(int i = 0; i < N; ++i)swap(day[i] , night[i]);
            swap(dayToNight , nightToDay);
        }
        return ret;
    }

};

int main(){
    DayAndNight solver;
    int N , M;
    cin >> N >> M;
    vector<int> a , b , day , night;
    for(int i = 1; i <= M; ++i){
        int x; cin >> x; a.push_back(x);
    }
    for(int i = 1; i <= M; ++i){
        int x; cin >> x; b.push_back(x);
    }
    for(int i = 1; i <= N; ++i){
        int x; cin >> x; day.push_back(x);
    }
    for(int i = 1; i <= N; ++i){
        int x; cin >> x; night.push_back(x);
    }
    int dayToNight , nightToDay; cin >> dayToNight >> nightToDay;
    cout << solver.minimalCost(a , b , day , night , dayToNight , nightToDay) << endl;
}
