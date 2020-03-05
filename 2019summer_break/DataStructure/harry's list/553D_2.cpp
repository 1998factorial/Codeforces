#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl
using namespace std;
typedef long long ll;
typedef pair<int , int> ii;

int N , M , K;
const int maxn = 1e5 + 10;
int deg1[maxn]; // original graph deg
int deg2[maxn]; // after deleting K fortress deg
int deg3[maxn]; // for each check deg
unordered_set<int> ban; // set of fortress
unordered_set<int> g[maxn]; // graph after deleting K fortress
unordered_set<int> g2[maxn]; // graph for each check
set<pair<double , int>> S;
bool vis[maxn];
vector<int> comp;

void DFS(int v){
  vis[v] = 1;
  comp.push_back(v);
  for(int u : g2[v]){
    if(!vis[u])
      DFS(u);
  }
}

void del(int v){
  for(int u : g2[v]){
    S.erase(make_pair((double)deg3[u] / deg1[u] , u));
    g2[u].erase(v);
    if(deg3[u]){
      --deg3[u];
      S.insert(make_pair((double)deg3[u] / deg1[u] , u));
    }
  }
  S.erase(make_pair((double)deg3[v] / deg1[v] , v));
  deg3[v] = 0;
  g2[v].clear();
}

int main(){
  scanf("%d %d %d" , &N , &M , &K);
  for(int i = 1; i <= K; ++i){
    int x; scanf("%d" , &x);
    ban.insert(x);
  }
  for(int i = 1; i <= M; ++i){
    int x , y; scanf("%d %d" , &x , &y);
    if(ban.count(x) == 0 && ban.count(y) == 0){
      g[x].insert(y);
      g[y].insert(x);
      ++deg2[x];
      ++deg2[y];
    }
    ++deg1[x];
    ++deg1[y];
  }
  double best = -1;
  // construct the set
  S.clear();
  for(int i = 1; i <= N; ++i){
    g2[i].clear();
    if(deg1[i] == 0)continue;
    if(ban.count(i) == 0){
      deg3[i] = deg2[i];
      for(int j : g[i]){
        g2[i].insert(j);
      }
    }
  }
  for(int i = 1; i <= N; ++i){
    if(deg1[i] == 0)continue;
    if(ban.count(i) == 0){
      S.insert(make_pair((double)deg3[i] / deg1[i] , i));
    }
  }
  while(!S.empty()){
    auto it = S.begin();
    if(it->first > best){
      best = it->first;
      comp.clear();
      for(auto& i : S)
        comp.push_back(i.second);
    }
    del(it->second);
  }
  printf("%d\n" , (int)comp.size());
  for(int i : comp){
    printf("%d " , i);
  }
  printf("\n");
}
