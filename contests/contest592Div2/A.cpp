#include <iostream>
#include <algorithm>
using namespace std;
int inf = 1 << 28;
int main(){
  int T;
  cin >> T;
  for(int i = 1; i <= T; ++i){
    int a , b , c , d , k;
    cin >> a >> b >> c >> d >> k;
    int ret = inf;
    int bx = 0 , by = 0;
    for(int x = 0; x <= k; ++x){
      for(int y = 0; y <= k; ++y){
        if(
          x * c >= a && y * d >= b && x + y <= k
        ){
          if(ret > x + y){
            ret = x + y;
            bx = x;
            by = y;
          }
        }
      }
    }
    if(ret != inf)cout << bx << " " << by << endl;
    else cout << -1 << endl;
  }
  return 0;
}
