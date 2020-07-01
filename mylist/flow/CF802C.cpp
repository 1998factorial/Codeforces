/*
    Min cost Max flow , rating 2600

    This problem seems NP hard , we should try flow

    treat number of book as flow , each unit of book can have different cost
    this is a model to min cost max flow

    Fullfil all request by buying every book first (it is hard to consider for each day to buy or not buy)
    suppose request i and j both require book b
    if we discard b during some request i to j , we need to pay twice for book b
    else we only need to pay one time which is the same as we pay twice and then sell one of b
    if we discard b during some request i to j , we can buy b at i and discard b
    straight aways (does not make any difference if we discard it later). If we keep b , we can
    make an extra action , namely , sell it right before request j

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

int N , K;
ll c[85] , a[85];
int pre[85] , occ[85];

int main(){
    cin >> N >> K;
    memset(pre , -1 , sizeof(pre));
    memset(occ , -1 , sizeof(occ));
    for(int i = 1; i <= N; ++i){
        cin >> a[i];
        if(occ[a[i]] != -1){
            pre[i] = occ[a[i]];
        }
        occ[a[i]] = i;
    }
    for(int i = 1; i <= N; ++i){
        cin >> c[i];
    }
    auto IN = [&](int i){
        return i;

    };
    auto OUT = [&](int i){
        return N + IN(i);
    };
    MCMF G;
    int tot = 2 * N + 5;
    int s = tot - 2 , t = tot - 1;
    G.init(tot , INF , s , t);
    for(int i = 1; i <= N; ++i){
        G.addedge(s , IN(i) , 1 , c[a[i]]); // cost to buy
        if(i + 1 <= N)G.addedge(IN(i) , IN(i + 1) , K - 1 , 0); // transfer K - 1 books to next day
        G.addedge(OUT(i) , t , 1 , 0); // discard or sell
        G.addedge(IN(i) , OUT(i) , 1 , 0); // need to either sell or discard one book at most
        if(pre[i] != -1){
            G.addedge(IN(i - 1) , OUT(pre[i]) , 1 , -c[a[i]]); // if we keep a[i] from pre[i] to i , we can sell a[i] to earn c[a[i]]
        }
    }
    ll cost = 0;
    ll ret = G.mincostMaxflow(cost);
    printf("%lld\n" , cost);
}
