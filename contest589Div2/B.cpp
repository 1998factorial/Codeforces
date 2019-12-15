#include <iostream>
#include <cstdio>
using namespace std;
typedef long long ll;
const ll mod = 1e9 + 7;
const int maxn = 1005;
int h , w;
ll r[maxn] , c[maxn];
ll f[maxn * maxn];

int main(){
  cin >> h >> w;
  for(int i = 1; i <= h; ++i)cin >> r[i];
  for(int i = 1; i <= w; ++i)cin >> c[i];
  ll ans = 0;
  f[0] = 1;
  for(int i = 1; i <= h * w; ++i)f[i] = f[i - 1] * 2ll % mod;
  ll cnt = 0;
  for(int i = 1; i <= w; ++i){
    for(int j = 1; j <= h; ++j){ // find all unreserved cells
      if(i > r[j] + 1 && j > c[i] + 1){
        ++cnt;
      }
      if(i == r[j] + 1 && j < c[i] + 1){
        cout << 0 << endl;
        return 0;
      }
      if(i < r[j] + 1 && j == c[i] + 1){
        cout << 0 << endl;
        return 0;
      }
    }
  }
  cout << (f[cnt] + mod) % mod << endl;
  return 0;
}
