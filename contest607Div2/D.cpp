#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
const int maxn = 65;
char a[maxn][maxn];
int R , C;

int solve(){
  // at least one A
  int ret = 4;
  // find if there is row/col of A
  // row check
  for(int i = 0; i < R; ++i){
    bool ok = 1;
    for(int j = 0; j < C; ++j)
      ok &= a[i][j] == 'A';
    if(ok){
      if(i == 0 || i == R - 1)ret = min(ret , 1);
      else ret = min(ret , 2);
    }
  }
  // col check
  for(int i = 0; i < C; ++i){
    bool ok = 1;
    for(int j = 0; j < R; ++j)
      ok &= a[j][i] == 'A';
    if(ok){
      if(i == 0 || i == C - 1)ret = min(ret , 1);
      else ret = min(ret , 2);
    }
  }
  // check edge A
  for(int i = 0; i < R; ++i){
    if(a[i][0] == 'A' || a[i][C - 1] == 'A')ret = min(ret , 3);
  }
  for(int j = 0; j < C; ++j){
    if(a[0][j] == 'A' || a[R - 1][j] == 'A')ret = min(ret , 3);
  }
  if(a[0][0] == 'A' || a[0][C - 1] == 'A' || a[R - 1][0] == 'A' || a[R - 1][C - 1] == 'A')ret = min(ret , 2);
  return ret;
}

int main(){
  int T; cin >> T;
  for(int t = 1; t <= T; ++t){
    cin >> R >> C;
    for(int i = 0; i < R; ++i)
      cin >> a[i];
    int cnt = 0;
    for(int i = 0; i < R; ++i)
      for(int j = 0; j < C; ++j)
        if(a[i][j] == 'A')++cnt;
    if(cnt == R * C){
      cout << 0 << endl;
    }
    else if(cnt == 0){
      cout << "MORTAL\n";
    }
    else{
      cout << solve() << endl;
    }
  }
}
