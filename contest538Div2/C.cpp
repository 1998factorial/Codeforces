#include <iostream>
#include <cstring>
#include <vector>
#include <cmath>
#include <map>
#include <unordered_map>
using namespace std;
typedef long long ll;
ll n , b;
const int maxn = 1e6 + 10;

vector<int> pri;
int vis[maxn + 11];

int main(){
  cin >> n >> b;
  for(int i = 2; i <= maxn; ++i){
    if (!vis[i]) {
      pri.push_back(i);
      for (int j = 1; j * i <= maxn; j++) {
            vis[i * j] = 1;
      }
    }
  }
  map<ll, ll> fac;
  int j = 0;
  while (b > 1 && j < (int) pri.size()) {
    if (b % pri[j] == 0){
      ++fac[pri[j]];
      b = b / pri[j];
    } else {
      ++j;
    }
  }
  if(b > 1)fac[b] = 1;
  ll ret = 1ll << 60;
  for(auto& it : fac){
     ll cur = it.first;
     ll cnt = 0;
     for(ll i = cur ; i <= n; i *= cur){
       cnt += n / i;
       if(n / i < cur)break;
     }
     ret = min(ret , cnt / it.second);
  }
  cout << ret << endl;
  return 0;
}
