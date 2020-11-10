#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;


const int maxn = 1e5 + 10;
bool seen[maxn];
ll c[3][maxn];
int N;
vector<int> g[maxn];
int col[maxn];
ll inf = 1ll << 55;
int deg[maxn];


ll DFS(int v , int i , int j){
  seen[v] = true;
  ll ret = c[i][v];
  for(int u : g[v]){
    if(!seen[u]){
      ret += DFS(u , 3 - i - j , i);
    }
  }
  seen[v] = false;
  return ret;
}

void DFS2(int v , int i , int j){
  seen[v] = true;
  col[v] = i + 1;
  for(int u : g[v])
    if(!seen[u])
      DFS2(u , 3 - i - j , i);
}

int main(){
  cin >> N;
  for(int j = 0; j < 3; ++j)
    for(int i = 1; i <= N; ++i)
      cin >> c[j][i];
  for(int i = 1; i <= N; ++i)
    deg[i] = 0;
  for(int i = 1; i < N; ++i){
    int x , y;
    cin >> x >> y;
    g[x].push_back(y);
    g[y].push_back(x);
    deg[x]++;
    deg[y]++;
    if(deg[x] > 2 || deg[y] > 2){ //has to be a chain
      cout << -1 << endl;
      return 0;
    }
  }
  int start = 1;
  for(int i = 1; i <= N; ++i){
    if(deg[i] == 1){
      start = i;
      break;
    }
  }
  ll ret = inf;
  int x , y;
  for(int i = 0; i < 3; ++i){
    for(int j = 0; j < 3; ++j){
      if(i == j)continue;
      ll ans = DFS(start , i , j);
      if(ans < ret){
        x = i;
        y = j;
        ret = ans;
      }
    }
  }
  if(ret >= inf){
    cout << -1 << endl;
    return 0;
  }
  cout << ret << endl;
  DFS2(start , x , y);
  for(int i = 1; i <= N; ++i){
    cout << col[i] << " ";
  }
  cout << endl;
  return 0;
}
