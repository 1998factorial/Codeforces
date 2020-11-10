#include <iostream>
#include <algorithm>
using namespace std;

int main(){
  int Q;
  cin >> Q;
  for(int q = 1; q <= Q; ++q){
    int c , m , x;
    int ret = 0;
    cin >> c >> m >> x;
    if(c == 0 || m == 0)cout << ret << endl;
    else{
      ret = min(min(c , m) , x);
      x -= ret;
      c -= ret;
      m -= ret;
      if(c == 0 || m == 0)cout << ret << endl;
      else{
        int x = max(c , m);
        int y = min(c , m);
        ret += min(x - y , y);
        if(y > x - y){
          ret += (2 * y - x) * 2 / 3;
        }
        cout << ret << endl;
      }
    }
  }
}
