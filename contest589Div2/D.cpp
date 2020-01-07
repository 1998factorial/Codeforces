#include <iostream>
#include <vector>
#include <string.h>
using namespace std;

const int maxn = 1e5 + 10;
int N , M;
vector<int> g[maxn];
int comp[maxn];
bool vis[maxn];

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> N >> M;
  for(int i = 1; i <= M; ++i){
    int x , y ; cin >> x >> y;
    g[x].push_back(y);
    g[y].push_back(x);
  }
  int color = 1;
  for(int i = 1; i <= N; ++i){
    if(!comp[i]){
      if(color > 3) {
        cout << -1 << endl;
        return 0;
      }
      memset(vis , 0 , sizeof(vis));
      for(int j : g[i]){
        if(comp[j] == color){
          cout << -1 << endl;
          return 0;
        }
        vis[j] = 1;
      }
      for(int j = 1; j <= N; ++j){
        if(!vis[j])comp[j] = color;
      }
      ++color;
    }
  }
  long long cnt[4] = {0 , 0 , 0 , 0};
  for(int i = 1; i <= N; ++i){
    for(int j : g[i]){
      if(comp[i] == comp[j]){
        cout << -1 << endl;
        return 0;
      }
    }
  }
  for(int i = 1; i <= N; ++i){
    cnt[comp[i]]++;
  }
  if(cnt[1] == 0 || cnt[2] == 0 || cnt[3] == 0){
    cout << -1 << endl;
    return 0;
  }
  if(cnt[1] * cnt[2] + cnt[2] * cnt[3] + cnt[3] * cnt[1] != M){
    cout << -1 << endl;
    return 0;
  }
  for(int i = 1; i <= N; ++i){
    //printf("com[%d] = %d\n" , i , comp[i]);
    cout << comp[i] << " ";
  }
  cout << endl;
  return 0;
}
