/*
    Mincut , rating 2300
    similar to project selection problem
    instead of finding the maximal profit , we can use mincut to model the
    minimal loss.
    the cost to change it's gender is v[i]
    if gender of dog is 1 then , we make edge c(s , i) = v[i]
    if gender of dog is 0 then , we make edge c(i , t) = v[i]
    if we cut c(s , i) we need to change the sex of dog[i] to 0 and pay v[i]
    if we cut c(i , t) we need to change the sex of dog[i] to 1 and pay v[i]
    if a request j has desired gender 1 , we connect c(s , N + j) with w[j]
    if a request j has desired gender 0 , we connect c(N + j , t) with w[j]
    += g if req j is made by friend
    if we cut c(s , N + j) , it means we can not fullfil request j and need to pay
    if we cut c(N + j , t) , it means we can not fullfil request j and need to pay
    if a request j has desired gender 1 , we connect for each dog i , c(N + j , i , INF)
    if a request j has desired gender 0 , we connect for each dog i , c(i , N + j , INF)
    this way , we can make sure that , for each s -- dog -- req -- t or s -- req -- dog -- t
    we cut at least one edge , being , if we want plan req , then we need to change gender
    or , if we do not change gender , we will give up the plan , if we cut both ,
    we are changing gender and giving up the plan
    ans = sum of all profit - maxflow
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 30000;
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

struct person{
    int dsex; // desired sex
    int w; // payload
    vector<int> req; // which dogs
    int isfriend; // friend of mine?
    person(){}
    person(int d , int w_ , vector<int> r , int i) : dsex(d) , w(w_) , req(r) , isfriend(i) {}
};
int N , M , g;
int v[10005] , w[2005] , sex[10005];
person people[2005];

ll solve(){
    Dinic G;
    int tot = M + N + 3;
    G.init(tot);
    int s = tot - 2 , t = tot - 1;
    for(int i = 1; i <= N; ++i){
        if(sex[i]){
            G.add(s , i , v[i]);
        }
        else{
            G.add(i , t , v[i]);
        }
    }
    for(int i = 1; i <= M; ++i){
        int w = people[i].w + people[i].isfriend * g;
        if(people[i].dsex){
            G.add(s , N + i , w);
        }
        else{
            G.add(N + i , t , w);
        }
        for(int j : people[i].req){
            if(people[i].dsex){
                G.add(N + i , j , INF);
            }
            else{
                G.add(j , N + i , INF);
            }
        }
    }
    ll ret = G.maxFlow(s , t);
    //G.showMinCut(s);
    return ret;
}

int main(){
    ll tot = 0;
    scanf("%d %d %d" , &N , &M , &g);
    for(int i = 1; i <= N; ++i)scanf("%d" , &sex[i]);
    for(int i = 1; i <= N; ++i)scanf("%d" , &v[i]);
    for(int i = 1; i <= M; ++i){
        scanf("%d %d" , &people[i].dsex , &people[i].w);
        tot += people[i].w;
        int sz; scanf("%d" , &sz);
        for(int j = 1; j <= sz; ++j){
            int x; scanf("%d" , &x); people[i].req.push_back(x);
        }
        scanf("%d" , &people[i].isfriend);
    }
    printf("%lld\n" , tot - solve());
}
