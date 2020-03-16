#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl
using namespace std;
typedef long long ll;
typedef pair<int , int> ii;

/*
  the goal is to find a Largest Biconnected component
  We shrink all the BC into points, now the graph is a tree.
  To construct the edges, we can use bridge finding algorithm.
*/

int N , M;
const int maxn = 4e5 + 10;
vector<ii> g[maxn];
int tot;
int low[maxn] , dfn[maxn];
bool instack[maxn];
vector<int> S;
int cid[maxn];
ii ans[maxn];

void tarjan(int v , int p){
  dfn[v] = low[v] = ++tot;
  instack[v] = 1;
  S.push_back(v);
  for(auto& e : g[v]){
    int u = e.first;
    if(u == p)continue;
    if(!dfn[u]){
      tarjan(u , v);
      low[v] = min(low[v] , low[u]);
    }
    else if(instack[u]){
      low[v] = min(low[v] , dfn[u]);
    }
  }
  if(low[v] == dfn[v]){
    for(;;){
      int cur = S.back();
      cid[cur] = v;
      instack[cur] = 0;
      S.pop_back();
      if(cur == v)break;
    }
  }
}

void DFS(int v , int p){
  dfn[v] = low[v] = ++tot;
  for(auto& e : g[v]){
    int u = e.first , eid = e.second;
    if(p == u)continue;
    if(!dfn[u]){
      DFS(u , v);
      low[v] = min(low[v] , low[u]);
      ans[eid].first = v;
      ans[eid].second = u;
      if(low[u] > dfn[v])
        swap(ans[eid].first , ans[eid].second);
    }
    else{
      low[v] = min(low[v] , dfn[u]);
      if(dfn[v] > dfn[u]){
        ans[eid].first = v;
        ans[eid].second = u;
      }
    }
  }
}

int main(){
  scanf("%d %d" , &N , &M);
  for(int i = 1; i <= M; ++i){
    int x , y; scanf("%d %d" , &x , &y);
    g[x].emplace_back(y , i);
    g[y].emplace_back(x , i);
  }
  tot = 0;
  tarjan(1 , 0);
  unordered_map<int , int> cnt;
  for(int i = 1; i <= N; ++i){
    ++cnt[cid[i]];
  }
  int mx = 0 , id = 0;
  for(auto& it : cnt){
    if(mx < it.second){
      id = it.first;
      mx = it.second;
    }
  }
  memset(dfn , 0 , sizeof(dfn));
  memset(low , 0 , sizeof(low));
  tot = 0;
  DFS(id , 0);
  printf("%d\n" , mx);
  for(int i = 1; i <= M; ++i){
    printf("%d %d\n" , ans[i].first , ans[i].second);
  }
}
