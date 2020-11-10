#include <iostream>
#include <queue>
#include <cstdio>
#include <vector>
#include <unordered_map>
#include <unordered_set>
using namespace std;

const int maxn = 1e5 + 10;
vector<int> g[maxn];
int id[maxn];
int deg[maxn];
int N , M;
bool vis[maxn];
int cnt;
/*
  tripartite
  for a vertice v , if there is no direct edge from v to some k ,
  then k and v are in the same set
*/

// m <= min(3e5 , n*(n-1)/2)
// n <= 1e5

int main(){
  cin >> N >> M;
  for(int i = 1; i <= N; ++i)g[i].clear() , deg[i] = 0;
  for(int i = 1; i <= M; ++i){
    int x , y;
    cin >> x >> y;
    g[x].push_back(y);
    g[y].push_back(x);
    ++deg[x];
    ++deg[y];
  }
  for(int i = 1; i <= N; ++i){
    id[i] = 0;
  }
  cnt = 1;
  unordered_map<int , unordered_map<int , int>> edge;
  for(int i = 1; i <= N; ++i){
    if(id[i] == 0){ // have not assigned
      if(cnt > 3){ // if there are more than 3 sets
        cout << -1 << endl;
        return 0;
      }
      else{
        id[i] = cnt;
        for(int j : g[i]){ // get directly connected
          ++edge[i][j];
          ++edge[j][i];
        }
        for(int j = 1; j <= N; ++j){
          if(id[j] == 0 && edge[i][j] == 0){
            id[j] = cnt;
          }
        }
        ++cnt;
      }
    }
  }
  int mx = 1;
  for(int i = 1; i <= N; ++i)mx = max(mx , id[i]);
  if(mx != 3){
    cout << -1 << endl;
    return 0;
  }
  unordered_set<int> v[4];
  for(int i = 1; i <= N; ++i){
    v[id[i]].insert(i);
  }
  if(v[1].size() * v[2].size() + v[1].size() * v[3].size() + v[2].size() * v[3].size() != M){
    cout << -1 << endl;
    return 0;
  }

  // check no connection between 2 vertices in same set

  

  for(int i = 1; i <= N; ++i){
    if(id[i] == 1){
      if(deg[i] != v[2].size() + v[3].size()){
        cout << -1 << endl;
        return 0;
      }
    }
    if(id[i] == 2){
      if(deg[i] != v[1].size() + v[3].size()){
        cout << -1 << endl;
        return 0;
      }
    }
    if(id[i] == 3){
      if(deg[i] != v[1].size() + v[2].size()){
        cout << -1 << endl;
        return 0;
      }
    }
  }
  for(int i = 1; i <= N; ++i){
    cout << id[i] << " ";
  }
  cout << endl;
  return 0;
}
