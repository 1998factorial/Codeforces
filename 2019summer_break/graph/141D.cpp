#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;
typedef pair<int , int> ii;

struct edge{
  int to , w , id;
  edge(){}
  edge(int tt , int ww , int dd) : to(tt) , w(ww) , id(dd) {}
};

int N , L;
const int maxn = 1e5 + 10;
const int inf = 1e9 + 10;
vector<edge> g[maxn * 3];
int dis[maxn * 3];
int pre[maxn * 3];
int edge_use[maxn * 3]; // which edge i used to get here
bool vis[maxn * 3];
int x[maxn] , d[maxn] , t[maxn] , p[maxn];
int disc[maxn * 3];
int tot;

int dijstra(){
  for(int i = 1; i <= tot; ++i){
    dis[i] = inf; vis[i] = 0;
    edge_use[i] = -1;
  }
  dis[1] = 0;
  pre[1] = -1;
  priority_queue<ii , vector<ii> , greater<ii>> q;
  q.push(make_pair(dis[1] , 1));
  while(!q.empty()){
    auto cur = q.top(); q.pop();
    int v = cur.second;
    if(!vis[v]){
      vis[v] = 1;
      for(auto& e : g[v]){
        if(!vis[e.to] && dis[e.to] > dis[v] + e.w){
          pre[e.to] = v;
          edge_use[e.to] = e.id;
          dis[e.to] = dis[v] + e.w;
          q.push(make_pair(dis[e.to] , e.to));
        }
      }
    }
  }
  return dis[tot];
}

void solve(){
  cout << dijstra() << endl;
  int cur = tot;
  vector<int> used;
  while(pre[cur] != -1){
    int p = pre[cur];
    if(edge_use[cur] != -1){
      used.push_back(edge_use[cur]);
    }
    cur = p;
  }
  cout << used.size() << endl;
  for(int i = used.size() - 1; i >= 0; --i){
    cout << used[i] << endl;
  }
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> N >> L;
  tot = 0;
  disc[++tot] = 0 , disc[++tot] = L;
  for(int i = 1; i <= N; ++i){
    cin >> x[i] >> d[i] >> t[i] >> p[i];
    if(x[i] - p[i] >= 0){
      disc[++tot] = x[i] - p[i];
      disc[++tot] = x[i] + d[i];
    }
  }
  sort(disc + 1 , disc + 1 + tot);
  tot = unique(disc + 1 , disc + 1 + tot) - disc - 1;
  for(int i = 1; i <= N; ++i){
    if(x[i] - p[i] >= 0){
      int from = lower_bound(disc + 1 , disc + 1 + tot , x[i] - p[i]) - disc;
      int to = lower_bound(disc + 1 , disc + 1 + tot , x[i] + d[i]) - disc;
      g[from].emplace_back(to , t[i] + p[i] , i);
    }
  }
  for(int i = 2; i <= tot; ++i){
    int from = i - 1 , to = i , w = disc[to] - disc[from];
    g[from].emplace_back(to , w , -1);
    g[to].emplace_back(from , w , -1);
  }
  solve();
}
