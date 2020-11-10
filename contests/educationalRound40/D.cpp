#include <bits/stdc++.h>
using namespace std;
typedef pair<int , int> ii;

/*
  this problem is easy
  just run dijstra and enumerate edges that do not exist
*/

int N , M , s , t;
const int inf = 1e9 + 10;
vector<int> g[1005];
int reach[1005][1005];
int dis[1005][2];
bool vis[1005];

void dijstra(int src , int f){
  for(int i = 1; i <= N; ++i){
    dis[i][f] = inf;
    vis[i] = 0;
  }
  priority_queue<ii , vector<ii> , greater<ii>> q;
  dis[src][f] = 0;
  q.push(make_pair(dis[src][f] , src));
  while(!q.empty()){
    int v = q.top().second;
    q.pop();
    if(!vis[v]){
      vis[v] = 1;
      for(int i : g[v]){
        if(!vis[i] && dis[i][f] > dis[v][f] + 1){
          dis[i][f] = dis[v][f] + 1;
          q.push(make_pair(dis[i][f] , i));
        }
      }
    }
  }
}

int main(){
  cin >> N >> M >> s >> t;
  for(int i = 1; i <= M; ++i){
    int x , y; cin >> x >> y;
    g[x].push_back(y);
    g[y].push_back(x);
    reach[x][y] = reach[y][x] = 1;
  }
  dijstra(s , 0);
  dijstra(t , 1);
  int cnt = 0 , tot = 0;
  for(int x = 1; x <= N; ++x){
    for(int y = x + 1; y <= N; ++y){
      if(!reach[x][y]){
        ++tot;
        if(dis[t][0] > dis[x][0] + dis[y][1] + 1){
          ++cnt;
        }
        else if(dis[t][0] > dis[x][1] + dis[y][0] + 1){
          ++cnt;
        }
      }
    }
  }
  cout << tot - cnt << endl;
}
