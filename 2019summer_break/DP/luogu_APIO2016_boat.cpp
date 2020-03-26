#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl
#define all(x) x.begin(), x.end()
using namespace std;
typedef long long ll;
typedef pair<int , int> ii;
const ll mod = 1e9 + 7;
const int maxn = 2000;

int N , M;
ll inv[maxn];
int L[maxn] , R[maxn];
vector<int> t;
ll C[maxn];
ll DP[maxn];

void init(){
  inv[1] = 1;
  // (inv[i] * i) % mod = 1
  for(int i = 2; i <= N; ++i){
    inv[i] = (mod - mod / i) * inv[mod % i] % mod;
  }
}

void discrete(){
  for(int i = 1; i <= N; ++i){
    t.push_back(L[i]);
    t.push_back(R[i]);
  }
  t.push_back(0);
  sort(all(t));
  t.resize(unique(all(t)) - t.begin());
  M = t.size() - 1;
  for(int i = 1; i <= N; ++i){
    L[i] = lower_bound(all(t) , L[i]) - t.begin();
    R[i] = lower_bound(all(t) , R[i]) - t.begin();
  }
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> N;
  for(int i = 1; i <= N; ++i){
    cin >> L[i] >> R[i];
    ++R[i];
  }
  init();
  discrete();
  C[0] = 1;
  DP[0] = 1;
  for(int j = 1; j < M; ++j){
    int len = t[j + 1] - t[j];
    for(int i = 1; i <= N; ++i){
      C[i] = (C[i - 1] * (len + i - 1) % mod) * inv[i] % mod;
    }
    for(int i = N; i >= 1; --i){
      if(j >= L[i] && j < R[i]){
        ll m = 1 , c = len;
        for(int p = i - 1; p >= 0; --p){
          DP[i] = (DP[i] + c * DP[p] % mod) % mod;
          if(j >= L[p] && j < R[p]){
            c = C[++m];
          }
        }
        //DP[i] = (DP[i] + f) % mod;
      }
    }
  }
  ll ans = 0;
  for(int i = 1; i <= N; ++i){
    ans = (ans + DP[i]) % mod;
  }
  cout << ans << endl;
}
