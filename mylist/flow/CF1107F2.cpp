/*
    min cost max flow , rating 2600
    the maximal amount of money will occur in the first N months
    Instead of enumerating the number of requests we will do , we assume that we will do
    all N requests , but with different costs , if the cost is more than gain , we will
    "do" it with cost 0 (which is the same as do not do it)
    let cost[i][j] = the gain - cost if we do request i on the jth month

    unfortunately , MCMF has a large constant , it takes 7s to finish N = 500 data
    So in CF1107F3.cpp , we use hungarian algorithm to find min cost matching.
*/
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

  void add(int from, int to, ll cap, ll cost) {
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

int N , a[505] , b[505] , k[505];

int main(){
    scanf("%d" , &N);
    for(int i = 1; i <= N; ++i){
        scanf("%d %d %d" , &a[i] , &b[i] , &k[i]);
    }
    int tot = 2 * N + 10;
    int s = tot - 1 , t = tot - 2;
    MCMF G;
    G.init(tot , INF , s , t);
    for(int i = 1; i <= N; ++i){
        G.add(s , i , 1 , 0);
        G.add(N + i , t , 1 , 0);
        for(int j = 1; j <= N; ++j){
            ll val = (ll)a[i] - (ll)min(N - j , k[i]) * b[i]; // cost if we do request i on jth month
            val = min(0ll , -val); // cost if we do not do it
            G.add(i , N + j , 1 , val);
        }
    }
    ll cost = 0;
    G.mincostMaxflow(cost);
    printf("%lld\n" , -cost);
}
