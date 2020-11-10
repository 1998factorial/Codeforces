#include <iostream>
using namespace std;

int g[8][8];
int n , m;

int main(){
  cin >> n >> m;
  for(int i = 1; i <= n; ++i){
    for(int j = 1; j <= n; ++j){
      g[i][j] = 0;
    }
  }
  for(int i = 1; i <= m; ++i){
    int x , y;
    cin >> x >> y;
    g[x][y] = g[y][x] = 1;
  }
  if(n < 7){
    cout << m << endl;
  }
  else{
    int ret = 0;
    for(int i = 1; i <= n; ++i){
      for(int j = i + 1; j <= n; ++j){ // for 2 vertices that have same digit on them
        int cnt = 0 , tot = 0;
        for(int k = 1; k <= n; ++k){
          if(g[i][k] == 1)++tot;
          if(g[j][k] == 1)++tot;
          if(g[i][k] == 1 && g[j][k] == 0){
            ++cnt;
          }
          if(g[j][k] == 1 && g[i][k] == 0){
            ++cnt;
          }
          if(g[j][k] == 1 && g[i][k] == 1){
            ++cnt;
          }
        }
        cnt -= g[i][j];
        tot -= g[i][j];
        ret = max(ret , m - (tot - cnt));
      }
    }
    cout << ret << endl;
  }
  return 0;
}
