#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl
using namespace std;
typedef long long ll;
typedef pair<int , int> ii;

const int maxn = 1e6 + 10;
vector<int> g[maxn];
int N;

unordered_map<int , int> d[maxn]; // mapping info for each subtree
set<ii> freq[maxn]; // (number , -depth)
int dep[maxn]; // depth of i from root
int a[maxn]; // union find mapping
int ans[maxn]; // answer of each node
/*
  DSU on tree, each map contains info from it's subtree,
  merge map by size, resulting in O(logN) merge time.

*/
void merge(int v , int u){// u is v's child
  int x = a[v] , y = a[u];
  // merge y to v
  if(d[y].size() >= d[x].size()){
    swap(x , y);
    swap(v , u);
  }
  for(auto& it : d[y]){
    int depth = it.first;
    int num = it.second;
    freq[x].erase(make_pair(d[x][depth] , -depth));
    d[x][depth] += num;
    freq[x].insert(make_pair(d[x][depth] , -depth));
  }
  a[u] = x;
}

void DFS(int v , int p){
  dep[v] = dep[p] + 1;
  d[v][dep[v]] = 1;
  freq[v].insert(make_pair(1 , -dep[v]));
  for(int u : g[v]){
    if(u != p){
      DFS(u , v);
    }
  }
  for(int u : g[v]){
    if(u != p){
      merge(v , u);
    }
  }
  auto it = freq[a[v]].rbegin();
  ans[v] = -it->second - dep[v];
}


int main(){
  scanf("%d" , &N);
  for(int i = 1; i < N; ++i){
    int x , y; scanf("%d %d" , &x , &y);
    g[x].push_back(y);
    g[y].push_back(x);
  }
  for(int i = 1; i <= N; ++i){
    a[i] = i;
  }
  DFS(1 , 0);
  for(int i = 1; i <= N; ++i){
    printf("%d\n" , ans[i]);
  }
}
