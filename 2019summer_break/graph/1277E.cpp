#include <iostream>
#include <vector>
#include <string.h>
using namespace std;
typedef long long ll;

int N , M , A , B;
const int maxn = 2e5 + 10;
vector<int> g[maxn];
int comp[maxn];
bool vis[maxn];

void DFS1(int v , int id){
  vis[v] = 1;
  comp[v] = id;
  for(int u : g[v]){
    if(!vis[u] && u != A)DFS1(u , id);
  }
}

void DFS2(int v , int id){
  vis[v] = 1;
  comp[v] = id;
  for(int u : g[v]){
    if(!vis[u] && u != B)DFS2(u , id);
  }
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int T; cin >> T;
  for(int t = 1; t <= T; ++t){
    cin >> N >> M >> A >> B;
    for(int i = 1; i <= N; ++i)g[i].clear();
    for(int i = 1; i <= M; ++i){
      int x , y; cin >> x >> y;
      g[x].push_back(y);
      g[y].push_back(x);
    }
    ll cnt1 = 0 , cnt2 = 0;
    memset(vis , 0 , sizeof(vis));
    memset(comp , 0 , sizeof(comp));
    // disconnect A
    for(int i = 1; i <= N; ++i){
      if(!vis[i] && i != A)DFS1(i , ++cnt1);
    }
    ll ret1 = 0;
    for(int i = 1; i <= N; ++i){
      if(comp[i] == comp[B]){
        ++ret1;
      }
    }
    ret1 = N - ret1;
    memset(vis , 0 , sizeof(vis));
    memset(comp , 0 , sizeof(comp));
    // disconnect B
    for(int i = 1; i <= N; ++i){
      if(!vis[i] && i != B)DFS2(i , ++cnt2);
    }
    ll ret2 = 0;
    for(int i = 1; i <= N; ++i){
      if(comp[i] == comp[A]){
        ++ret2;
      }
    }
    ret2 = N - ret2;
    cout << (ret1 - 1) * (ret2 - 1) << endl;
  }
}
