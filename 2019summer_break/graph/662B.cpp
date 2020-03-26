#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl
#define all(x) x.begin(), x.end()
using namespace std;
typedef long long ll;
typedef pair<int , int> ii;

const int maxn = 1e5 + 10;
const int inf = 1e9 + 10;
int N , M;
struct edge{
  int to , c;
  edge(){}
  edge(int a , int b) : to(a) , c(b) {}
};
vector<edge> g[maxn];
int vis[maxn];
int cnt[2];
vector<int> path;
vector<int> ret;


bool DFS(int v , int c , int goal){
  path.push_back(v);
  vis[v] = c;
  ++cnt[c];
  for(auto& e : g[v]){
    if(vis[e.to] == -1){
      if(e.c == goal){ // do not change color
        if(!DFS(e.to , c , goal))return 0;
      }
      else{ // change color
        if(!DFS(e.to , 1 - c , goal))return 0;
      }
    }
    else{
      if(vis[e.to] == vis[v] && e.c != goal){
        return 0;
      }
      if(vis[e.to] != vis[v] && e.c == goal){
        return 0;
      }
    }
  }
  return 1;
}


int main(){
  scanf("%d %d" , &N , &M);
  for(int i = 1; i <= M; ++i){
    int x , y; char z; scanf("%d %d %c" , &x , &y , &z);
    if(z == 'B'){
      g[x].emplace_back(y , 1);
      g[y].emplace_back(x , 1);
    }
    else{
      g[x].emplace_back(y , 0);
      g[y].emplace_back(x , 0);
    }
  }
  int ans1 = 0 , ans2 = 0;
  // solve for turning all edges to 0
  fill(vis + 1 , vis + 1 + N , -1);
  for(int i = 1; i <= N; ++i){
    if(vis[i] == -1){
      cnt[0] = cnt[1] = 0;
      if(!DFS(i , 0 , 0)){
        ans1 = inf;
        break;
      }
      ans1 += min(cnt[0] , cnt[1]);
    }
  }
  // solve for turning all edges to 1
  fill(vis + 1 , vis + 1 + N , -1);
  for(int i = 1; i <= N; ++i){
    if(vis[i] == -1){
      cnt[0] = cnt[1] = 0;
      if(!DFS(i , 0 , 1)){
        ans2 = inf;
        break;
      }
      ans2 += min(cnt[0] , cnt[1]);
    }
  }
  path.clear();
  int ans = min(ans1 , ans2);
  if(ans >= inf)printf("-1\n");
  else{
    printf("%d\n" , ans);
    // trace back
    int goal = (ans1 < ans2) ? 0 : 1;
    fill(vis + 1 , vis + 1 + N , -1);
    for(int i = 1; i <= N; ++i){
      if(vis[i] == -1){
        cnt[0] = cnt[1] = 0;
        DFS(i , 0 , goal);
        int cc = (cnt[0] < cnt[1]) ? 0 : 1;
        for(int j : path){
          if(vis[j] == cc)ret.push_back(j);
        }
        path.clear();
      }
    }
    for(int i : ret){
      printf("%d " , i);
    }
    printf("\n");
  }
}
