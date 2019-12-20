#include <iostream>
using namespace std;
typedef long long ll;

ll n , p , w , d;

/*
  wx + dy = p
  x + y <= n
*/

int main(){
  cin >> n >> p >> w >> d;
  for(ll y = 0; y <= w; ++y){ // y is at most w
    ll x = (p - d * y) / w;
    if((p - d * y) % w == 0 && x >= 0 && x + y <= n){
      cout << x << " " << y << " " << n - x - y << endl;
      return 0;
    }
  }
  cout << -1 << endl;
  return 0;
}
