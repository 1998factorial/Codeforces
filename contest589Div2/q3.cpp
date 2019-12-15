#include <iostream>
#include <cmath>
#include <vector>
using namespace std;
typedef long long ll;
const ll mod = 1e9 + 7;

ll x , n;

//the question is just asking how many pk are there in n! .


ll qpow(ll m , ll k){
  if(k <= 0)return 1ll;
  ll ret = qpow(m , k / 2);
  if(k % 2 == 1){
    return (ret * ret % mod) * m % mod;
  }
  return (ret * ret) % mod;
}

int main(){
  cin >> x >> n;
  vector<ll> p;
  for(ll i = 2; i * i <= x; ++i){
    if(x % i == 0){
      p.push_back(i);
      while(x % i == 0){
        x /= i;
      }
    }
  }
  if(x > 1)p.push_back(x);
  ll ret = 1ll; // contribution from g(1 , 1) * ... * g(n , 1)
  for(int i = 0; i < p.size(); ++i){
    ll pk = p[i];
    ll c = pk;
    ll cnt = 0;
    for(int j = 1; j <= log(n)/log(pk) + 1; ++j){
      cnt = (cnt + (n / c));
      if(c > n / pk)break; // make sure long long does not overflow
      c = (c * pk);
    }
    ll cc = qpow(pk , cnt);
    ret = ret * cc % mod;
  }
  cout << (ret + mod) % mod << endl;
  return 0;
}
