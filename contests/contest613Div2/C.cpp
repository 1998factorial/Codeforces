#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
typedef long long ll;

/*
  lcm(a , b) = p[1]^x[1] * .. * p[k]^x[k]
  a and b must have prime factors from {p[1] .. p[k]}
  let a = p[1]^A[1] * .. * p[k]^A[k]
  let b = p[1]^B[1] * .. * p[k]^B[k]
  X = p[1]^x[1] * .. * p[k]^x[k]
  x[i] = max(A[i] , B[i])
  making the min(A[i] , B[i]) = 0 won't change max(A[i] , B[i]) thus won't change LCM
  therefore we claim that the optimal a and b can be coprime

  for X , k is logX many so we can use bitmask to brute force value of a and b
*/

int main(){
  ll X;
  cin >> X;
  vector<ll> fac;
  for(ll i = 2; i * i <= X; ++i){
    if(X % i == 0){
      ll c = 1;
      while(X % i == 0){
        c *= i;
        X /= i;
      }
      fac.push_back(c);
    }
  }
  if(X > 1)fac.push_back(X);
  int N = fac.size();
  ll A = 1e18 , B = 1e18;
  for(int i = 0; i < (1 << N); ++i){
    ll a = 1 , b = 1;
    for(int j = 0; j < N; ++j){
      if(i & (1 << j)) a *= fac[j];
      else b *= fac[j];
    }
    if(max(a , b) < max(A , B)){
      A = a;
      B = b;
    }
  }
  cout << A << " " << B << endl;
}
