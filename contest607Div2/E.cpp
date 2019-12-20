#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
typedef long long ll;
typedef pair<ll , ll > ii;
const int maxn = 2e5 + 10;
vector<ii> g[maxn];
int N;
ll G , B;
ll tsize[maxn];

void DFS(int v , int p){
  tsize[v] = 1;
  for(auto& e : g[v]){
    ll u = e.first , w = e.second;
    if(u != p){
      DFS(u , v);
      tsize[v] += tsize[u];
      if(tsize[u] % 2 == 1)G += w;
      B += w * min(tsize[u] , 2ll * N - tsize[u]);
    }
  }
}

int main(){
  int T;
  cin >> T;
  for(int t = 1 ; t <= T; ++t){
    cin >> N;
    for(int i = 1; i <= 2 * N; ++i){
      g[i].clear();
    }
    for(int i = 1; i <= 2 * N - 1; ++i){
      ll x , y , z;
      cin >> x >> y >> z;
      g[x].emplace_back(y , z);
      g[y].emplace_back(x , z);
    }
    G = 0 , B = 0;
    DFS(1 , 1);
    cout << G << " " << B << endl;
  }
}
