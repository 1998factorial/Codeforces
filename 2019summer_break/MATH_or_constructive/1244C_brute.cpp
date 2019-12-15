#include <iostream>
using namespace std;
typedef long long ll;

ll n , p , w , d;
/*
  wx + dz = p
  x + z <= n
*/
int main(){
  cin >> n >> p >> w >> d;
  for(ll z = 0; z <= w; ++z){
    if((p - z * d) % w == 0 && (p - z * d) / w >= 0 && n - (p - z * d) / w - z >= 0){
      cout << (p - z * d) / w  << " " << z << " " << n - (p - z * d) / w - z << endl;
      return 0;
    }
  }
  cout << -1 << endl;
  return 0;
}
