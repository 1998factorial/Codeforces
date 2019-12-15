#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
using namespace std;
typedef pair<int , int> ii;
typedef long long ll;
//1156 D
//find all 0 components and 1 components
const int maxn = 2e5 + 10;
vector<ii> g[maxn];
bool vis[maxn];
int n;
ll ret;
int id[2][maxn]; //id of component (for a vertix)

int find(int i , int j){
  return id[i][j] == j ? j : id[i][j] = find(i , id[i][j]);
}

void add(int i , int x , int y){
  int xx = find(i , x);
  int yy = find(i , y);
  if(xx > yy)swap(xx , yy);
  if(xx != yy){
    id[i][yy] = id[i][xx];
  }
}

void DFS(int v , int c){
  if(vis[v])return;
  vis[v] = true;
  for(ii p : g[v]){
    int to = p.first , cc = p.second;
    if(!vis[to] && c == cc){
      add(c , v , to);
      DFS(to , c);
    }
  }
}

int main(){
  cin >> n;
  for(int i = 1; i <= n; ++i){
    g[i].clear();
  }
  for(int i = 1; i < n; ++i){
    int x , y , z;
    cin >> x >> y >> z;
    g[x].push_back(make_pair(y , z));
    g[y].push_back(make_pair(x , z));
  }
  for(int i = 0; i < 2; ++i){
    for(int j = 1; j <= n; ++j){
      id[i][j] = j;
    }
  }
  for(int i = 1; i <= n; ++i)vis[i] = false;
  // find all connected component for 0
  for(int i = 1; i <= n; ++i){
    if(!vis[i]){
      DFS(i , 0);
    }
  }
  for(int i = 1; i <= n; ++i)vis[i] = false;
  // find all connected component for 1
  for(int i = 1; i <= n; ++i){
    if(!vis[i]){
      DFS(i , 1);
    }
  }
  unordered_map<int , int> cnta , cntb;
  for(int i = 1; i <= n; ++i){
    ++cnta[id[0][i]];
    ++cntb[id[1][i]];
  }
  for(auto& it : cnta){
    if(it.second > 1){
      ret += 1ll * it.second * (it.second - 1);
    }
  }
  for(auto& it : cntb){
    if(it.second > 1){
      ret += 1ll * it.second * (it.second - 1);
    }
  }
  unordered_map<int , unordered_map<int, int>> v;
  for(int i = 1; i <= n; ++i){
    int x = find(0 , i);
    int y = find(1 , i);
    if(cnta[x] > 1 && cntb[y] > 1){
      if(v[x][y] == 0){
        ret += (ll)cnta[x] * cntb[y] - cnta[x] - cntb[y] + 1;
      }
      ++v[x][y];
    }
  }
  cout << ret << endl;
}
