#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;

int c , f1 , f2 , f3;
const ll mod = 1e9 + 7;
ll n;
// f[n] = c ^ (2 * n - 6) * f[n - 1] * f[n - 2] * f[n - 3]
//a[i] = power of f1 for f[i]
//a[i] = a[i - 1] + a[i - 2] + a[i - 3]
ll a[3][3];
/*
  [a[i]    [1 , 1 , 1        [a[i + 1]
  a[i-1] *  1 , 0 , 0      =  a[i]
  a[i-2]]   0 , 1 , 0]        a[i - 1]]

  a ^ p = a mod p  -> a ^ p - 1 = 1 mod p
  a * a ^ -1 = 1 mod p = a ^ p - 1 mod p
  a ^ -1 = a ^ p - 2 mod p

  3n - 6 = n - 1 + n - 2 + n - 3

*/

void matrixPower(int n){ // O(logn)
  if(n <= 1)return;
  matrixPower(n >> 1);
  vector<vector<ll>> t(3 , vector<ll> (3));
  for(int i = 0; i < 3; ++i)
    for(int j = 0; j < 3; ++j)
      t[i][j] = a[i][j];
  if(n % 2 == 1){
    //mult a with a then with t
    vector<vector<ll>> tt(3, vector<ll>(3));
    for(int i = 0; i < 3; ++i){
      for(int j = 0; j < 3; ++j){
        for(int k = 0; k < 3; ++k){
          tt[i][j] = (tt[i][j] + a[i][k] * a[k][j] % mod + mod) % mod;
        }
      }
    }
    vector<vector<ll>> ret(3 , vector<ll>(3));
    for(int i = 0; i < 3; ++i){
      for(int j = 0; j < 3; ++j){
        for(int k = 0; k < 3; ++k){
          ret[i][j] = (ret[i][j] + t[i][k] * tt[k][j] % mod + mod) % mod;
        }
      }
    }
    for(int i = 0; i < 3; ++i)
      for(int j = 0; j < 3; ++j)
        a[i][j] = ret[i][j];
  }
  else{
    //mult a with a
    vector<vector<ll>> ret(3 , vector<ll>(3));
    for(int i = 0; i < 3; ++i){
      for(int j = 0; j < 3; ++j){
        for(int k = 0; k < 3; ++k){
          ret[i][j] = (ret[i][j] + a[i][k] * a[k][j] % mod + mod) % mod;
        }
      }
    }
    for(int i = 0; i < 3; ++i)
      for(int j = 0; j < 3; ++j)
        a[i][j] = ret[i][j];
  }
}

ll qpower(ll x , ll n){ //compute x ^ n in log(n) time
  if(n <= 0)return 1ll;
  ll ret = qpower(x , n >> 1);
  if(n % 2 == 1){
    return ( ( x * ret ) % mod ) * ret % mod;
  }
  return ret * ret % mod;
}

ll inverse(ll x , ll p){ //by fermat's little theorm
  return qpower(x , p - 2);
}

int main(){
  //cin >> n >> f1 >> f2 >> f3 >> c;
  for(int i = 0; i < 3; ++i)
    for(int j = 0; j < 3; ++j)
      a[i][j] = 0;
  a[0][0] = a[0][1] = a[0][2] = a[1][0] = a[2][1] = 1;
  matrixPower(2);
  /*for(int i = 0; i < 3; ++i){
    for(int j = 0; j < 3; ++j){
      cout << a[i][j] << " ";
    }
    cout << endl;
  }*/
  
}
