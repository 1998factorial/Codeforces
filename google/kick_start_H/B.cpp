#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl
using namespace std;
typedef long long ll;
typedef pair<int , int> ii;

const int maxn = 105;
char a[maxn][maxn];
struct edge{
  int to , c;
  edge(){}
  edge(int a , int b) : to(a) , c(b) {}
};
vector<edge> g[maxn * 4];
int vis[maxn * 4];
int cnt[2];
int N;

void DFS(int v , int c){
  ++cnt[c];
  vis[v] = c;
  for(auto& e : g[v]){
    if(vis[e.to] == -1){
      if(e.c == 0)DFS(e.to , c);
      else DFS(e.to , 1 - c);
    }
      //DFS(e.to , e.c ^ c);
  }
}

int solve(){
  cin >> N;
  for(int i = 0; i < 4 * N - 2; ++i)g[i].clear();
  for(int i = 0; i < N; ++i){
    for(int j = 0; j < N; ++j){
      cin >> a[i][j];
    }
  }
  for(int i = 0; i < N; ++i){
    for(int j = 0; j < N; ++j){
      int u = i + j; // top-left -> bottom-right diagonal encodes
      int v = 2 * N - 1 + (i - j + N - 1); // top-right -> bottom-left diagonal encodes
      g[u].emplace_back(v , a[i][j] == '.');
      g[v].emplace_back(u , a[i][j] == '.');
    }
  }
  fill(vis , vis + 4 * N - 2 , -1);
  int ret = 0;
  for(int i = 0; i < 4 * N - 2; ++i){
    if(vis[i] == -1){
      cnt[0] = cnt[1] = 0;
      DFS(i , 0);
      ret += min(cnt[0] , cnt[1]);
    }
  }
  return ret;
}


int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t; cin >> t;
  for(int x = 1; x <= t; ++x){
    cout << "Case #" << x << ": " << solve() << endl;
  }
}
