#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl
using namespace std;
typedef long long ll;
typedef pair<int , int> ii;

const int maxn = 1e5 + 10;
int N , M;
vector<ii> g[maxn];
int dfn[maxn] , low[maxn];
int cid[maxn];
int tot;
bool instack[maxn];
vector<int> S;
vector<ii> bridges;
ii ans[3 * maxn];

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
  low[v] = dfn[v] = ++tot;
  for(auto& e : g[v]){
    int u = e.first , eid = e.second;
    if(u == p)continue;
    if(!dfn[u]){
      DFS(u , v);
      low[v] = min(low[v] , low[u]);
      ans[eid].first = v;
      ans[eid].second = u;
      if(low[u] > dfn[v]){ // bridge
        bridges.emplace_back(v , u);
        //printf("bridge : %d %d\n" , v , u);
      }
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
  //tot = 0;
  //tarjan(1 , 0);
  //for(int i = 1; i <= N; ++i){
//    printf("cid[%d] = %d\n" , i , cid[i]);
  //}
  //memset(dfn , 0 , sizeof(dfn));
  //memset(low , 0 , sizeof(low));
  tot = 0;
  DFS(1 , 0);
  if(bridges.size()){
    printf("0\n");
  }
  else{
    for(int i = 1; i <= M; ++i){
      printf("%d %d\n" , ans[i].first , ans[i].second);
    }
  }
}
