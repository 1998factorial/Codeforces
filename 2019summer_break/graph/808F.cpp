#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

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

struct card{
  int p , c , l;
  card(){}
  card(int p_ , int c_ , int l_ ): p(p_) , c(c_) , l(l_) {}
  bool operator < (const card& rhs) const {
    return p > rhs.p;
  }
} a[105];

const int maxc = 2e5 + 10;
set<int> primes;
bool seen[maxc];
int N , K;

void getprime(){
  // seive
  for(int i = 2; i < maxc; ++i){
    if(!seen[i]){
      primes.insert(i);
      for(int j = i; j < maxc; j += i){
        seen[j] = 1;
      }
    }
  }
}

void read(){
  cin >> N >> K;
  for(int i = 1; i <= N; ++i){
    cin >> a[i].p >> a[i].c >> a[i].l;
  }
  sort(a + 1 , a + 1 + N);
}



bool solve(int mid){
  Dinic g;
  g.init(N + 2);
  int s = 0 , t = N + 1;
  ll tot = 0;
  int one = 0;
  for(int i = 1; i <= N; ++i){
    if(a[i].l > mid)continue;
    if(a[i].c == 1 && one)continue;
    if(a[i].c == 1)one++;
    tot += a[i].p;
    if(a[i].c % 2 == 0){
      g.add(i , t , a[i].p);
    }
    else{
      g.add(s , i , a[i].p);
    }
    for(int j = 1; j <= N; ++j){
      if(a[j].l <= mid && primes.count(a[i].c + a[j].c) != 0){
        if(a[i].c % 2 == 1){
          g.add(i , j , INF);
        }
      }
    }
  }
  ll ret = g.maxFlow(s , t);
  return tot - ret >= K;
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  getprime();
  read();
  int l = 1 , r = 100 , ans = -1;
  while(l <= r){
    int mid = (l + r) >> 1;
    if(solve(mid)){
      ans = mid;
      r = mid - 1;
    }
    else{
      l = mid + 1;
    }
  }
  cout << ans << endl;
}
