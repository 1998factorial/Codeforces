#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll INF = 1e18;
const int maxn = 1e5 + 10;

struct Edge {
  int from, to;
  ll cap, flow, cost;
  Edge(int u, int v, ll c, ll f, ll w):from(u),to(v),cap(c),flow(f),cost(w){}
};

struct MCMF {
  int n, m;
  int src, target;
  vector<Edge> edges;
  vector<int> G[maxn];
  int inq[maxn];
  ll d[maxn];
  int p[maxn];
  ll a[maxn];
  ll K;
  MCMF() {}

  void init(int n , ll K , int s , int t) {
      this->n = n;
      for(int i = 0; i < n; i++) G[i].clear();
      edges.clear();
      this->K = K;
      src = s;
      target = t;
  }

  void addedge(int from, int to, ll cap, ll cost) {
      edges.push_back(Edge(from, to, cap, 0, cost));
      edges.push_back(Edge(to, from, 0, 0, -cost));
      m = edges.size();
      G[from].push_back(m-2);
      G[to].push_back(m-1);
  }

  bool SPFA(int s, int t, ll &flow, ll &cost) {
      for(int i = 0; i < n; i++) d[i] = INF;
      memset(inq, 0, sizeof(inq));
      d[s] = 0; inq[s] = 1; p[s] = 0; a[s] = INF;

      queue<int> Q;
      Q.push(s);
      while(!Q.empty()) {
          int u = Q.front(); Q.pop();
          inq[u] = 0;
          for(int i = 0; i < (int) G[u].size(); i++) {
              Edge& e = edges[G[u][i]];
              if(e.cap > e.flow && d[e.to] > d[u] + e.cost) {
                  d[e.to] = d[u] + e.cost;
                  p[e.to] = G[u][i];
                  a[e.to] = min(a[u], e.cap - e.flow);
                  if(!inq[e.to]) { Q.push(e.to); inq[e.to] = 1; }
              }
          }
      }
      if(d[t] == INF) return false;
      // note that everytime MCMF would find the cheapest path
      // for a unit flow
      if (cost + d[t] * a[t] > K) {
          flow += (K - cost) / d[t];
          cost += (K - cost) / d[t] * d[t];
          return false;
      }
      flow += a[t];
      cost += d[t] * a[t];
      for(int u = t; u != s; u = edges[p[u]].from) {
              edges[p[u]].flow += a[t];
              edges[p[u]^1].flow -= a[t];
      }
      return true;
  }

  ll mincostMaxflow(ll &cost) {
      ll flow = 0;
      cost = 0;
      while(SPFA(src, target, flow, cost));
      return flow;
  }
};



int N;
int r[2005];
int c , t1 , c1 , t2 , c2;

// i day[i] day , i + N day[i] night

int main(){
    scanf("%d" , &N);
    for(int i = 1; i <= N; ++i)scanf("%d" , &r[i]);
    scanf("%d %d %d %d %d" , &c , &t1 , &c1 , &t2 , &c2);
    int tot = 2 * N + 5;
    int src = tot - 2 , sink = tot - 1;
    MCMF G;
    G.init(tot , INF , src , sink);
    auto day = [&](int i){
        return i;
    };
    auto night = [&](int i){
        return day(i) + N;
    };
    for(int i = 1; i <= N; ++i){
        G.addedge(src , day(i) , INF , c); // can buy clean towel at morning
        G.addedge(src , night(i) , r[i] , 0); // day[i] night will get r[i] dirty towel
        G.addedge(day(i) , sink , r[i] , 0); // day[i] day will supply r[i] clean towel
        if(i + 1 <= N){
            G.addedge(night(i) , night(i + 1) , INF , 0); // dirty towel can be passed onto next day (but night time)
        }
        if(i + t1 <= N){
            G.addedge(night(i) , day(i + t1) , INF , c1); // fast wash
        }
        if(i + t2 <= N){
            G.addedge(night(i), day(i + t2) , INF , c2); // slow wash
        }
    }
    ll cost = 0;
    G.mincostMaxflow(cost);
    printf("%lld\n" , cost);
}
