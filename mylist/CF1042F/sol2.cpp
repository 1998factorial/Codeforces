#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e6 + 10;

int N , K;
vector<int> g[maxn];
int ans = 0;
/*
  if we can not merge set a and set b , assuming d(a) < d(b)
  later, if we can merge b with c , we can surely merge c with a as well
  so b in this case can be erased and our ans will be added by 1
*/


int DFS(int v , int p){
  if(g[v].size() == 1){
    return 0; // depth is 0
  }
  vector<int> dis_child;
  for(int u : g[v]){
    if(u == p)continue;
    dis_child.push_back(DFS(u , v) + 1);
  }
  sort(dis_child.begin() , dis_child.end());
  while(dis_child.size() > 1){
    if(dis_child.back() + dis_child[dis_child.size() - 2] <= K){
      break; // means these depths are all mergable
    }
    ++ans;
    // we know that dis_child.back() will not be able to merge with anyone else
    dis_child.pop_back();
    // get rid of the largest depth (no need to keep it)
  }
  return dis_child.back();
}


void solve(){
  for(int i = 1; i <= N; ++i){
    if(g[i].size() > 1){
      DFS(i , i);
      return;
    }
  }
}

int main(){
  scanf("%d %d" , &N , &K);
  for(int i = 1; i < N; ++i){
    int x , y; scanf("%d %d" , &x , &y);
    g[x].push_back(y);
    g[y].push_back(x);
  }
  solve();
  ++ans; // need to consider the last set.
  printf("%d\n" , ans);
}
