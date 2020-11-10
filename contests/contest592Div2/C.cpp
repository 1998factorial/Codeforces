#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;
typedef long long ll;

ll n , p , w , d;
// find x , y , z
// x + y + z = n
// wx + dy = p

ll gcd(ll a , ll b){
  if(a == 0)return b;
  return gcd(b % a , a);
}

ll qpow(int x , int m){
  if(m <= 0)return 1;
  ll ret = qpow(x  , m / 2);
  if(m % 2 == 0)return ret * ret;
  return ret * ret * x;
}

int main(){
  cin >> n >> p >> w >> d;
  ll q = gcd(w , d);
  if(p % q != 0)cout << -1 << endl;
  else{
    w /= q;
    d /= q;
    p /= q;
    ll x = qpow(d , w - 2);
    ll y = qpow(w , d - 2);
    cout << x << " " << y << endl;
    x *= p;
    y *= p;
    if(n - x - y < 0){
      cout << -1 << endl;
      //cout << x << " " << y << " " << n - x - y << endl;
    }
    else{
      cout << x << " " << y << " " << n - x - y << endl;
    }
  }
  return 0;
}
