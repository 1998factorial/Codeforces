#include <bits/stdc++.h>
using namespace std;

/*
  binary search maximal weight of edge and check by topological sort

  after top sort , there will be no edge comming from a[i] to a[j] , i > j
  thus we can always find a way to reverse the remaining edges
*/

const int maxn = 1e5 + 10;

struct edge{
  int from , to , w;
  edge(){}
  edge(int a , int b , int c) : from(a) , to(b) , w(c) {}
}edges[maxn];

int N , M;
vector<int> g[maxn];
int deg[maxn];
bool fix[maxn];
bool vis[maxn];

void init(int mid){
  for(int i = 1; i <= N; ++i)g[i].clear() , deg[i] = 0 , vis[i] = 0;
  for(int i = 1; i <= M; ++i){
    if(edges[i].w > mid){
      fix[i] = 1;
      g[edges[i].from].push_back(edges[i].to);
    }
    else{
      fix[i] = 0;
    }
  }
}

void DFS(int v , vector<int>& order){
  vis[v] = 1;
  order.push_back(v);
  for(int u : g[v]){
    --deg[u];
    if(!vis[u] && !deg[u])
      DFS(u , order);
  }
}

vector<int> top_sort(){ // topological sort recursive version (DFS)
  vector<int> ret;
  for(int i = 1; i <= N; ++i)
    for(int j : g[i])
      ++deg[j];
  for(int i = 1; i <= N; ++i){
    if(!deg[i] && !vis[i])
      DFS(i , ret);
  }
  return ret;
}

vector<int> top_sort(){ // topological sort iterative version (Stack simulate DFS)
  vector<int> order;
  for(int i = 1; i <= N; ++i)
    for(int j : g[i])
      ++deg[j]; // compute indegree
  for(int i = 1; i <= N; ++i)
    if(!deg[i]) // put all indegree == 0 nodes into stack to begin
      order.push_back(i);
  int cur = 0;
  while(cur < order.size()){ // expand stack
    int v = order[cur];
    ++cur;
    for(int u : g[v]){
      --deg[u]; // decrease indegree by 1
      if(!deg[u]){ // if decreased to 0 put it into stack
        order.push_back(u);
      }
    }
  }
  return order;
}

bool check(int mid){
  init(mid); // build graph first
  vector<int> ret = top_sort();
  return ret.size() == N;
}


int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> N >> M;
  for(int i = 1; i <= M; ++i){
    cin >> edges[i].from >> edges[i].to >> edges[i].w;
  }
  int l = 0 , r = 1e9 , best = -1;
  while(l <= r){
    int mid = (l + r) >> 1;
    if(check(mid)){
      best = mid;
      r = mid - 1;
    }
    else{
      l = mid + 1;
    }
  }
  cout << best << " ";
  init(best);
  vector<int> order = top_sort();
  unordered_map<int , int> location;
  for(int i = 0; i < order.size(); ++i){
    location[order[i]] = i;
  }
  vector<int> rev;
  for(int i = 1; i <= M; ++i){
    if(!fix[i] && location[edges[i].to] < location[edges[i].from]){
      rev.push_back(i);
    }
  }
  cout << rev.size() << endl;
  for(int i : rev)cout << i << " ";
  cout << endl;
}
