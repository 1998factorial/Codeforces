#include <iostream>
#include <cmath>
#include <vector>
#include <cstdio>
using namespace std;
typedef long long ll;

/*
  check if x - y is divisible by some number
*/

bool check(ll n){
  for(ll i = 2; i * i <= n; ++i){
    if(n % i == 0){
      return true;
    }
  }
  if(n > 1)return true;
  return false;
}

int main(){
  int T;
  cin >> T;
  for(int t = 1; t <= T; ++t){
    ll x , y;
    scanf("%lld %lld" , &x , &y);
    if(check(x - y)){
      printf("YES\n");
    }
    else{
      printf("NO\n");
    }
  }
  return 0;
}
