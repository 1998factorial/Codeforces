#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5 + 10;

int N , K;
vector<int> g[maxn];
multiset<int> val[maxn];

/*
  for each vertex v, store the sets of minimal leaves in it's subtree
  classify each set of leaves by the largest depth.
  choose the child with largest number of sets to be the center
  merge other child to the center
  when merging depth x, choose the largest possible depth of a set in center
  to merge. this can be done by set upperbound query (logN)
  Overall O(N * logN * logN)
*/

void DFS(int v , int d , int p){
  if(g[v].size() == 1){
    val[v].insert(d);
  }
  else{
    int best = -1;
    for(int u : g[v]){
      if(u == p)continue;
      DFS(u , d + 1 , v);
      if(best == -1 || val[best].size() < val[u].size()){
        best = u;
      }
    }
    swap(val[v] , val[best]);
    for(int u : g[v]){
      if(u == p || u == best)continue;
      for(int x : val[u]){ // logN
        int lim = K + 2 * d - x;
        auto y = val[v].upper_bound(lim); // logN
        if(y == val[v].begin()){ // can not find any
          val[v].insert(x);
        }
        else{
          --y;
          val[v].erase(*y);
          val[v].insert(max(*y , x));
        }
      }
    }
  }
}

int solve(){
  for(int i = 1; i <= N; ++i){
    if(g[i].size() > 1){
      DFS(i , 0 , i);
      return (int)val[i].size();
    }
  }
  return -1;
}

int main(){
  scanf("%d %d" , &N , &K);
  for(int i = 1; i < N; ++i){
    int x , y; scanf("%d %d" , &x , &y);
    g[x].push_back(y);
    g[y].push_back(x);
  }
  printf("%d\n" , solve());
}
