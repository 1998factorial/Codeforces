/*
    Min cost Max flow , rating 2500

    the optimal strategy is : summon K - 1 minions first , for the remaining
    N - K + 1 minions , when summon a minion , kill it after , except for the last
    minion.

    we can solve this problem by using MCMF , each minion can be in the K alived ones
    or can be killed.
    let 1 ~ N be nodes for minions , N + 1 ~ N + K + 1 be the summons
    we need to connect the flow graph such that the maximal matching is size
    N , while the cost is minimal possible , in our problem we want to maximise the
    total power , so to minimise , we take the negative of them.
    connect s to each minion with (1 , 0)
    connect minion i to summon j with (1 , -b[i] * (j - 1) - a[i])
    connect minion i to summon K + 1 with (1 , -b[i] * (K - 1))
    connect each first K summon to t with (1 , 0)
    connect last summon to t with (N - K , 0)
    this way , we can ensure that the maximal flow is N , while -cost is maximal

    if (i , N + [1..K]) is cut , means , minion[i] will be keeped alive
    if (i , N + K + 1) is cut , minion[i] will be killed straight after summoned
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

int N , K;

struct minion{
    int a , b;
}minions[80];

int ans[500];

int main(){
    int T;
    cin >> T;
    while(T--){
        cin >> N >> K;
        for(int i = 1; i <= N; ++i){
            cin >> minions[i].a >> minions[i].b;
        }
        int tot = N + K + 10;
        MCMF G;
        int s = tot - 1 , t = tot - 2;
        G.init(tot , INF , s , t);
        for(int i = 1; i <= N; ++i){
            G.add(s , i , 1 , 0);
            for(int j = 1; j <= K; ++j){
                G.add(i , N + j , 1 , -(j - 1) * minions[i].b - minions[i].a); // not killed and joined as jth
            }
            G.add(i , N + K + 1 , 1 , -(K - 1) * minions[i].b); // killed
        }
        for(int i = 1; i <= K; ++i){
            G.add(N + i , t , 1 , 0);
        }
        G.add(N + K + 1 , t , N - K , 0);
        ll cost = 0;
        ll ret = G.mincostMaxflow(cost);
        vector<int> killed;
        for(auto& e : G.edges){
            if(e.cap != e.flow)continue; // get cuts
            if(e.from >= 1 && e.from <= N && e.to >= N + 1 && e.to <= N + K){
                ans[e.to - N] = e.from;
            }
            if(e.from >= 1 && e.from <= N && e.to == N + K + 1){
                killed.push_back(e.from);
                killed.push_back(-e.from);
            }
        }
        cout << 2 * (N - K) + K << endl;
        for(int i = 1; i < K; ++i){
            cout << ans[i] << " ";
        }
        for(int i : killed){
            cout << i << " ";
        }
        cout << ans[K] << endl;
    }
}
