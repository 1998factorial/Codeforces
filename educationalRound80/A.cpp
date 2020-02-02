#include <iostream>
#include <cmath>
using namespace std;
typedef long long ll;

/*
  check if exist x such that
  x + ceil(d / (x + 1)) >= n
  only need to check up to sqrt(n) for x
*/


ll n , d;

bool solve(){
  if(n >= d)return 1;
  for(ll x = 1; x <= sqrt(d); ++x){
    if(x + ceil((double)d / (x + 1)) <= n){
      return 1;
    }
  }
  return 0;
}

int main(){
  int T; cin >> T;
  while(T--){
    cin >> n >> d;
    if(solve()){
      cout << "YES" << endl;
    }
    else{
      cout << "NO" << endl;
    }
  }
}
