#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl
using namespace std;
typedef long long ll;
typedef pair<int , int> ii;

int T , N , K;
int a[55][55];
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

  void show(){
    for(auto& e : edges){
      cout << e.from << " -> " << e.to << " " << "cap = " << e.cap << " " << "flow = " << e.flow << endl;
    }
  }

};


void go(int num){
  Dinic g;
  int s = 0 , t = 2 * N + 1;
  g.init(2 * N + 2);
  bitset<100> cols;
  bitset<100> rows;
  cols.reset();
  rows.reset();
  for(int i = 1; i <= N; ++i){
    for(int j = 1; j <= N; ++j){
      if(a[i][j] == num){
        rows[i] = 1;
        cols[j] = 1;
      }
    }
  }
  for(int i = 1; i <= N; ++i){
    if(!rows[i])g.add(s , i , 1);
    if(!cols[i])g.add(i + N , t , 1);
  }
  for(int i = 1; i <= N; ++i){
    for(int j = 1; j <= N; ++j){
      if(a[i][j] == -1){
        g.add(i , N + j , 1);
      }
    }
  }
  ll flow = g.maxFlow(s , t);
  for(auto& e : g.edges){
    if(e.from <= N && e.to - N >= 1 && e.cap == e.flow){ // cut
      a[e.from][e.to - N] = num;
      //printf("setting a[%d][%d] = %d\n" , e.from , e.to - N , num);
    }
  }
  /*for(int i = 1; i <= N; ++i){
    for(int j : g.G[i]){
      Edge& e = g.edges[j];
      if(e.from <= N && e.to > N && e.cap - e.flow == 0){
        a[i][e.to - N] = num;
      }
    }
  }*/
}

void solve(){
  memset(a , -1 , sizeof(a));
  if(K == N + 1 || K == N * N - 1 || (N == 3 && K == 5) || (N == 3 && K == 7)){
    cout << "IMPOSSIBLE\n";
    return;
  }
  int r = K % N;
  for(int i = 1; i <= N; ++i){
    a[i][i] = K / N;
  }
  // greedy a good diagonal, good if no element appears exactly N - 1 times
  if(r > 1 && r < N - 1){
    for(int i = 1; i <= r; ++i)
      ++a[i][i];
  }
  else if(r == 1){
    ++a[1][1]; ++a[2][2]; --a[3][3];
  }
  else if(r == N - 1){
    for(int i = 1; i <= N; ++i)
      ++a[i][i];
    --a[1][1]; --a[2][2]; ++a[3][3];
  }
  map<int , int> cnt;
  for(int i = 1; i <= N; ++i){
    cnt[a[i][i]]++;
  }
  vector<pair<int , int>> vec;
  for(int i = 1; i <= N; ++i){
    vec.emplace_back(cnt[i] , i);
  }
  sort(vec.begin() , vec.end());
  reverse(vec.begin() , vec.end());
  for(auto& e : vec){
    go(e.second);
  }
  cout << "POSSIBLE\n";
  for(int i = 1; i <= N; ++i){
    for(int j = 1; j <= N; ++j){
      cout << a[i][j] << " ";
    }
    cout << endl;
  }
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> T;
  for(int t = 1; t <= T; ++t){
    cin >> N >> K;
    cout << "Case #" << t << ": ";
    solve();
  }
}
