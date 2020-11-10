#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll X;

/*
  a = k1 * gcd , b = k2 * gcd , assume a <= b
  k1 * gcd * k2 = X
  k1 <= sqrt(X)
  in optimal solution , gcd can be 1
  k1 * k2 = X and gcd(k1 , k2) = 1
  for(1 <= k1 <= sqrt(X))
    if(gcd(k1 , X / k1) == 1)
      -> solution
*/

int main(){
  cin >> X;
  ll a = 1 , b = 1;
  for(ll i = sqrt(X); i >= 1; --i){
    if(X % i == 0){
      if(__gcd(i , (ll)X / i) == 1){
        a = i , b = X / i;
        break;
      }
    }
  }
  cout << a << " " << b << endl;
}
