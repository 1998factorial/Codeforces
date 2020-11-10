#include <bits/stdc++.h>
using namespace std;

/*
  A[i][j] = y(i - 1) + j
  yes, this is a very annoying simluation problem
  many finicky edge cases
  in general , we just need to find all candidate
  y (at most 2)
  and for each such candidate, simluate the travel
  process and check if the coordinates match
  notice that there is no special requirement for x
  so just let x = 1e9
*/

const int maxn = 2e5 + 10;
int a[maxn];
int N;

int dir[4][2] = {{-1 , 0} , {1 , 0} , {0 , 1} , {0 , -1}};

bool check(int i , int j , int y){
  int x1 = a[i] / y + ((a[i] % y) != 0);
  int y1 = a[i] - y * (x1 - 1);
  if(y1 > y || x1 < 1)return 0;
  int x2 = a[j] / y + ((a[j] % y) != 0);
  int y2 = a[j] - y * (x2 - 1);
  for(int k = 0; k < 4; ++k){
    int dx = x2 + dir[k][0];
    int dy = y2 + dir[k][1];
    if(dx < 1 || dy > y)continue;
    if(dx == x1 && dy == y1)return 1;
  }
  return 0;
}

int main(){
  set<int> vis;
  cin >> N;
  if(N == 1){
    cout << "YES" << endl;
    cout << 1000000000 << " " << 1 << endl;
    return 0;
  }
  for(int i = 1; i <= N; ++i)cin >> a[i];
  for(int i = 2; i <= N; ++i){
    if(a[i] == a[i - 1]){
      cout << "NO" << endl;
      return 0;
    }
    vis.insert(abs(a[i] - a[i - 1]));
  }
  if(vis.size() > 2){
    cout << "NO" << endl;
    return 0;
  }
  else{
    for(int y : vis){
      bool ok = 1;
      for(int i = 2; i <= N; ++i){
        ok &= check(i - 1 , i , y);
      }
      if(ok){
        cout << "YES" << endl;
        cout << 1000000000 << " " << y << endl;
        return 0;
      }
    }
    cout << "NO" << endl;
  }
}
