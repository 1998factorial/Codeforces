/*
    flow - mincut , rating 2400
    variation of project selection
    first thing to notice , we can binary search the answer
    we can then use min cut to model the minimal loss under this case
    observe first that in our deck , we can not have more than one card of magic number 1
    oberserve that we can pair up (odd , odd) and (even , even) for all cases
    the only thing we need to be careful of is (odd , even) , this might result in a prime
    so we can precompute all primes <= 2e5.
    and we can construct the following flow graph:
    connect all cards with magic number odd with src
    connect all cards with magic number even with sink
    connect c[i] to c[j] if c[i] + c[j] is prime with cap = INF
    if we cut an edge means we do not want to include it in our deck
    check if total power - flow >= K

    overrall O(log(100) * T(Dinic(100)))
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 30010;
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

int N , K;
struct card{
    int p , c , l;
    card(){}
    card(int p_ , int c_ , int l_) : p(p_) , c(c_) , l(l_) {}
    bool operator < (const card& rhs) const {
        return p > rhs.p;
    }
};

vector<card> cards;
bool vis[200005];
unordered_set<int> primes;

bool check(int lim){
    Dinic G;
    int tot = N + 3;
    G.init(tot);
    int s = tot - 2 , t = tot - 1;
    int ret = 0 , one = 0;
    for(int i = 1; i <= N; ++i){
        int p1 = cards[i].p , c1 = cards[i].c , l1 = cards[i].l;
        if(l1 > lim)continue;
        if(c1 == 1 && one)continue;
        if(c1 == 1)++one;
        ret += p1;
        if(c1 & 1)G.add(s , i , p1);
        else G.add(i , t , p1);
        for(int j = 1; j <= N; ++j){
            int p2 = cards[j].p , c2 = cards[j].c , l2 = cards[j].l;
            if(l2 > lim)continue;
            if(primes.find(c1 + c2) == primes.end())continue;
            if(c1 & 1){
                G.add(i , j , INF);
            }
            else{
                G.add(j , i , INF);
            }
        }
    }
    ll f = G.maxFlow(s , t);
    return ret - f >= K;
}

int main(){
    for(int i = 2; i < 200005; ++i){
        if(!vis[i]){
            primes.insert(i);
            for(int j = i; j < 200005; j += i){
                vis[j] = 1;
            }
        }
    }
    scanf("%d %d" , &N , &K);
    cards.emplace_back(0 , 0 , 0);
    for(int i = 1; i <= N; ++i){
        int x , y , z; scanf("%d %d %d" , &x , &y , &z);
        cards.emplace_back(x , y , z);
    }
    sort(cards.begin() + 1 , cards.end());
    int ret = -1 , l = 0 , r = 105;
    while(l <= r){
        int mid = (l + r) >> 1;
        if(check(mid)){
            ret = mid;
            r = mid - 1;
        }
        else{
            l = mid + 1;
        }
    }
    printf("%d\n" , ret);
}
