#include <iostream>
using namespace std;
typedef long long ll;

ll n , p , w , d;

int gcd(ll a, ll b, ll & x, ll & y) {
  if(a == 0){
    x = 0; y = 1;
    return b;
  }
  ll x1 , y1;
  ll d = gcd(b % a , a , x1 , y1);
  x = y1 - (b / a) * x1;
  y = x1;
  return d;
}

int main(){
  cin >> n >> p >> w >> d;
  ll x , z;
  ll gcdv = gcd(n , d , x , z);
  cout << gcdv << endl;
  cout << x << " " << z << endl;
  if(p % gcdv != 0)cout << -1 << endl;
  else{

  }
}
