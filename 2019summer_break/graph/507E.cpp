#include <bits/stdc++.h>
using namespace std;
typedef pair<int , int> ii;

const int maxn = 1e5 + 10;
const int inf = 1e9 + 10;
vector<ii> g[maxn]; // original graph
set<ii> g2[maxn]; // new graph
int N , M;
int dis[maxn][2];
int dist[maxn];
bool vis[maxn];
int good = 0;

unordered_map<int , unordered_map<int , unordered_map<int , int>>> edges;

void BFS(int src , int f){
  for(int i = 1; i <= N; ++i){
    dis[i][f] = inf;
    vis[i] = 0;
  }
  dis[src][f] = 0;
  vis[src] = 1;
  queue<int> q;
  q.push(src);
  while(!q.empty()){
    int v = q.front();
    q.pop();
    vis[v] = 1;
    for(auto& e : g[v]){
      if(!vis[e.first]){
        vis[e.first] = 1;
        q.push(e.first);
        dis[e.first][f] = dis[v][f] + 1;
      }
    }
  }
}

ii pre[maxn];

void dijstra(int src){
  for(int i = 1; i <= N; ++i){
    dist[i] = inf;
    vis[i] = 0;
    pre[i] = make_pair(-1 , -1);
  }
  dist[src] = 0;
  priority_queue<ii , vector<ii> , greater<ii>> q;
  q.push(make_pair(dist[src] , src));
  while(!q.empty()){
    int v = q.top().second;
    q.pop();
    if(!vis[v]){
      vis[v] = 1;
      for(auto& e : g2[v]){
        int u = e.first , w = e.second;
        if(!vis[u] && dist[u] > dist[v] + w){
          dist[u] = dist[v] + w;
          q.push(make_pair(dist[u] , u));
          pre[u] = make_pair(v , 1 - w);
        }
      }
    }
  }
  cout << good - dis[N][0] + 2 * dist[N] << endl;
  // bad edges from our path
  vector<pair<int , ii>> path;
  int cur = N;
  while(pre[cur].first > 0){
    if(edges[cur][pre[cur].first][pre[cur].second])path.emplace_back(cur , pre[cur]);
    else path.push_back(make_pair(pre[cur].first , make_pair(cur , pre[cur].second)));
    cur = pre[cur].first;
  }
  for(auto& e : path){
    if(!e.second.second){ // bad edges in path become good edges
      cout << e.first << " " << e.second.first << " " << 1 - e.second.second << endl;
    }
    edges[e.first][e.second.first][e.second.second] = 0;
  }

  for(int i = 1; i <= N; ++i){ // good edges from the rest of the graph become bad edges
    for(auto& e : g[i]){
      int j = e.first , w = e.second;
      if(edges[i][j][w]){
        if(w){
          cout << i << " " << j << " " << 1 - w << endl;
        }
      }
    }
  }

}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> N >> M;
  for(int i = 1; i <= M; ++i){
    int x , y , c; cin >> x >> y >> c;
    good += c == 1;
    g[x].emplace_back(y , c);
    g[y].emplace_back(x , c);
    edges[x][y][c] = 1;
  }
  BFS(1 , 0); // compute shortest dist from 1 to other places
  BFS(N , 1); // compute shortest dist from N to other places
  // the goad is to find a path from 1 to N which contains least 0s
  for(int i = 1; i <= N; ++i){
    for(auto& e : g[i]){
      int j = e.first , w = e.second;
      if(dis[N][0] == dis[i][0] + dis[j][1] + 1){
        g2[i].insert(make_pair(j , 1 - w));
      }
      if(dis[N][0] == dis[j][0] + dis[i][1] + 1){
        g2[j].insert(make_pair(i , 1 - w));
      }
    }
  }
  dijstra(1);
}
