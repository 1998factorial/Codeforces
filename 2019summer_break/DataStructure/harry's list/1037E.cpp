#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl
using namespace std;
typedef long long ll;
typedef pair<int , int> ii;

const int maxn = 2e5 + 10;
int N , M , K;
set<int> g[maxn];
set<ii> person;
int deg[maxn];
int ans[maxn];
ii edges[maxn];
/*
  working from m-th day, and keep deleting.
  if a pereon's friend becomes < K
  then all of this person's friends should be unfriended with him
  to avoid invalid count
  this is one way to deal with "cyclic" definition
*/
int main(){
  scanf("%d %d %d" , &N , &M , &K);
  for(int i = 1; i <= M; ++i){
    scanf("%d %d" , &edges[i].first , &edges[i].second);
    g[edges[i].first].insert(edges[i].second);
    g[edges[i].second].insert(edges[i].first);
    ++deg[edges[i].first];
    ++deg[edges[i].second];
  }
  for(int i = 1; i <= N; ++i){
    person.insert(make_pair(deg[i] , i));
  }
  for(int i = M; i >= 1; --i){
    int x = edges[i].first , y = edges[i].second;
    while(!person.empty()){
      auto it = person.begin();
      if(it->first >= K){
        break;
      }
      int v = it->second;
      for(int u : g[v]){
        person.erase(make_pair(deg[u] , u));
        if(deg[u])person.insert(make_pair(--deg[u] , u));
        g[u].erase(v);
      }
      g[v].clear();
      person.erase(make_pair(deg[v] , v));
      deg[v] = 0;
    }
    ans[i] = person.size();
    if(g[x].find(y) != g[x].end()){
      person.erase(make_pair(deg[x] , x));
      person.erase(make_pair(deg[y] , y));
      g[y].erase(x);
      g[x].erase(y);
      if(deg[x])person.insert(make_pair(--deg[x] , x));
      if(deg[y])person.insert(make_pair(--deg[y] , y));
    }
  }
  for(int i = 1; i <= M; ++i){
    printf("%d\n" , ans[i]);
  }
}
