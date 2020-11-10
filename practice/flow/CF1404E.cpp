#include <bits/stdc++.h>
#define ID if(0)
using namespace std;
typedef long long ll;
const int maxn = 205 * 205 * 4 * 2 + 1000;
const double INF = 1e18;
const double ep = 1e-8;
int N , M , tot = 0;
char s[205][205];
int MP[205][205][4];
bool vis[maxn];
int colour[maxn];
vector<int> g[maxn];
// 0 , up 
// 1 , left 
// 2 , right
// 3 , down

struct Edge {
  int from, to;
  int cap, flow;
  Edge(int u, int v, int c, int f) : from(u), to(v), cap(c), flow(f) {}
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
        if (!vis[e.to] && e.cap - e.flow > 0) {
          vis[e.to] = 1;
          d[e.to] = d[x] + 1;
          Q.push(e.to);
        }
      }
    }
    return vis[t];
  }

  int DFS(int x, int a) {
    if (x == t || a == 0) return a;
    int flow = 0, f;
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

  int maxFlow(int s, int t) {
    this->s = s;
    this->t = t;
    int flow = 0;
    while (BFS()) {
      memset(cur, 0, sizeof(cur));
      flow += DFS(s, INF);
    }
    return flow;
  }
} D;

void DFS(int v , int c){
    colour[v] = c;
    vis[v] = 1;
    for(int x : g[v]){
        if(vis[x])continue;
        DFS(x , 1 - c);
    }
}

int main(){
    int i , j , k;
    cin >> N >> M;
    int cnt_black = 0;
    for(i = 1; i <= N; ++i){
        for(j = 1; j <= M; ++j){
            cin >> s[i][j];
            cnt_black += s[i][j] == '#';
        }
    }
    for(i = 1; i <= N; ++i){
        for(j = 1; j <= M; ++j){
            for(k = 0; k < 4; ++k){
                MP[i][j][k] = -1;
            }
        }
    }
    for(i = 1; i <= N; ++i){
        for(j = 1; j <= M; ++j){
            if(s[i][j] != '#')continue;
            if(i > 1 && s[i - 1][j] == '#'){
                if(MP[i - 1][j][3] == -1)MP[i][j][0] = ++tot;
                else MP[i][j][0] = MP[i - 1][j][3];
            }
            if(j > 1 && s[i][j - 1] == '#'){
                if(MP[i][j - 1][2] == -1)MP[i][j][1] = ++tot;
                else MP[i][j][1] = MP[i][j - 1][2];
            }
            if(j < M && s[i][j + 1] == '#'){
                if(MP[i][j + 1][1] == -1)MP[i][j][2] = ++tot;
                else MP[i][j][2] = MP[i][j + 1][1];
            }
            if(i < N && s[i + 1][j] == '#'){
                if(MP[i + 1][j][0] == -1)MP[i][j][3] = ++tot;
                else MP[i][j][3] = MP[i + 1][j][0];
            }
        }
    }
    ID{
        for(i = 1; i <= N; ++i){
            for(j = 1; j <= M; ++j){
                for(k = 0; k < 4; ++k){
                    if(~MP[i][j][k])printf("MP[%d][%d][%d] = %d\n" , i , j , k , MP[i][j][k]);
                }
            }
        }
    }
    ID cout << "tot = " << tot << endl;
    for(i = 1; i <= N; ++i){
        for(j = 1; j <= M; ++j){
            int up = MP[i][j][0];
            int left = MP[i][j][1];
            int right = MP[i][j][2];
            int down = MP[i][j][3];
            if(~up && ~left)g[up].push_back(left) , g[left].push_back(up);
            if(~up && ~right)g[up].push_back(right) , g[right].push_back(up);
            if(~down && ~left)g[down].push_back(left) , g[left].push_back(down);
            if(~down && ~right)g[down].push_back(right) , g[right].push_back(down);
        }
    }
    ID {
        for(i = 1; i <= tot; ++i){
            printf("at %d : " , i);
            for(int x : g[i]){
                printf("%d " , x);
            }
            printf("\n");
        }
    }
    for(i = 1; i <= tot; ++i){
        if(vis[i])continue;
        DFS(i , 0);
    }
    ID {
        for(i = 1; i <= tot; ++i){
            printf("colour[%d] = %d\n" , i , colour[i]);
        }
    }
    D.init(tot + 10);
    int s = tot + 10 - 2 , t = tot + 10 - 1;
    for(i = 1; i <= tot; ++i){
        if(colour[i])D.add(s , i , 1);
        else D.add(i , t , 1);
        for(int x : g[i]){
            D.add(i , x , 1);
        }
    }
    int maximal_matching = D.maxFlow(s , t);
    //cout << "maximal matching = " << maximal_matching << endl;
    cout << cnt_black - (tot - maximal_matching) << endl;
}