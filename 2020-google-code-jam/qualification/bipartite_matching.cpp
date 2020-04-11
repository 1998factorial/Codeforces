#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl
using namespace std;
typedef long long ll;
typedef pair<int , int> ii;

/*
  template for finding maximum matching in a bipartite graph
  using hopcroft karp algorithm
  runtime is O(sqrt(V) * E)
*/

const int maxn = 1e5 + 10;
const int inf = 1e9 + 10;
vector<int> g[maxn];
int N , M , match[maxn] , dist[maxn];


bool BFS(){
  queue<int> q;
  for(int i = 1; i <= N; ++i){
    if(match[i] == 0){
      dist[i] = 0;
      q.push(i);
    }
    else{
      dist[i] = inf;
    }
  }
  dist[0] = inf;
  while(!q.empty()){
    int u = q.front(); q.pop();
    if(u != 0){
      for(int v : g[u]){
        if(dist[match[v]] == inf){
          dist[match[v]] = dist[u] + 1;
          q.push(match[v]);
        }
      }
    }
  }
  return dist[0] != inf;
}

bool DFS(int u){
  if(u != 0){
    for(int v : g[u]){
      if(dist[match[v]] == dist[u] + 1){
        if(DFS(match[v])){
          match[v] = u;
          match[u] = v;
          return 1;
        }
      }
    }
    dist[u] = inf;
    return 0;
  }
  return 1;
}

int hopcroft(){
  int ret = 0;
  while(BFS()){
    for(int i = 1; i <= N; ++i){
      if(match[i] == 0 && DFS(i)){
        ++ret;
      }
    }
  }
  return ret;
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> N >> M;
  for(int i = 1; i <= M; ++i){
    int x , y; cin >> x >> y;
    g[x].push_back(y);
  }
  cout << hopcroft() << endl;
  for(int i = 1; i <= N; ++i){
    printf("match[%d] = %d\n" , i , match[i]);
  }
}
