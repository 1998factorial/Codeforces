#include <bits/stdc++.h>
using namespace std;

/*
  we have a forest to begin with
  for each tree it the answer is just the diameter of it
  when merging two trees
  if we want to minimize the diameter of the resulting tree
  we obtain that the minimal bound is
  max{diameter[x] , diameter[y] , ceil(diameter[x] / 2) + ceil(diameter[y] / 2) + 1}
*/

const int maxn = 3e5 + 10;
int N , M , Q;
int a[maxn];
vector<int> g[maxn];
int tot;
int ans[maxn];
int dp[maxn];

int find(int x){
  return a[x] == x ? x : a[x] = find(a[x]);
}

void add(int x , int y){
  x = find(x);
  y = find(y);
  if(x != y){
    a[x] = y;
  }
}

void merge(int x , int y){
  x = find(x);
  y = find(y);
  if(x != y){
    int m = ceil((double)ans[x] / 2) + ceil((double)ans[y] / 2) + 1;
    ans[y] = max(ans[y] , ans[x]);
    ans[y] = max(ans[y] , m);
    a[x] = y;
  }
}

void DFS(int root , int v , int p){
  dp[v] = 0;
  vector<int> rets;
  for(int u : g[v]){
    if(u != p){
      DFS(root , u , v);
      dp[v] = max(dp[v] , dp[u] + 1);
      rets.push_back(dp[u]);
    }
  }
  ans[root] = max(ans[root] , dp[v]);
  sort(rets.begin() , rets.end());
  if(rets.size() > 1){
    ans[root] = max(ans[root] , rets[rets.size() - 1] + rets[rets.size() - 2] + 2);
  }
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> N >> M >> Q;
  for(int i = 1; i <= N; ++i)a[i] = i;
  for(int i = 1; i <= M; ++i){
    int x , y; cin >> x >> y;
    g[x].push_back(y);
    g[y].push_back(x);
    add(x , y);
  }
  set<int> vis;
  for(int i = 1; i <= N; ++i){ // for each tree
    int root = find(i);
    if(!vis.count(root)){
      DFS(root , root , -1);
      vis.insert(root);
    }
  }
  for(int i = 1; i <= Q; ++i){
    int t; cin >> t;
    if(t == 1){
      int x; cin >> x;
      cout << ans[find(x)] << endl;
    }
    else if(t == 2){
      int x , y; cin >> x >> y;
      merge(x , y);
    }
  }
}
