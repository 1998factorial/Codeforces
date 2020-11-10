#include <iostream>
#include <algorithm>
using namespace std;
typedef long long ll;

const int maxn = 2e3 + 10;
ll a[maxn] , b[maxn] , M;
int N;

/*
N is small
a[i] + x == b[j] (mod M)
-> exists j such that (a[1] + x) = b[j] (mod M)
  b[j] - a[1] = x (mod M)
  enumerate j from 1 ... N
*/

int main(){
  cin >> N >> M;
  for(int i = 1; i <= N; ++i){
    cin >> a[i];
  }
  for(int i = 1; i <= N; ++i){
    cin >> b[i];
  }
  sort(a + 1 , a + 1 + N);
  sort(b + 1 , b + 1 + N);
  ll ans = 1e18;
  for(int j = 1; j <= N; ++j){ // for each possible j
    ll x = ((b[j] - a[1]) % M + M) % M;
    bool ok = true;
    for(int i = 1; i <= N; ++i){
      int pos = (i + j - 2) % N + 1;
      if((a[i] + x + M) % M != b[pos])ok = false;
    }
    if(ok) ans = min(ans , x);
  }
  cout << ans << endl;
}
