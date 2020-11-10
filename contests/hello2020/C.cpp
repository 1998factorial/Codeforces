#include <iostream>
#include <algorithm>
using namespace std;
typedef long long ll;

const int maxn = 3e5 + 10;
ll mod;
int N;
ll fac[maxn];

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> N >> mod;
  fac[0] = 1;
  for(int i = 1; i <= N; ++i)fac[i] = fac[i - 1] * i % mod;
  ll ret = 0;
  for(int i = 1; i <= N; ++i){
    ll a = (ll)i * i % mod;
    ll b = fac[i - 1] * fac[N - i + 1] % mod;
    ret = (ret + a * b % mod) % mod;
  }
  cout << (ret + mod) % mod << endl;
}
