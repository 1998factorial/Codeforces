#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl
#define all(x) x.begin(), x.end()
using namespace std;
typedef long long ll;
typedef pair<int , int> ii;
const ll mod = 998244353;
const int maxn = 55;
int L[maxn] , R[maxn];
vector<ll> t;
int N , M;
ll DP[maxn][maxn * 4];
ll F[maxn * 4] , INV[maxn * 4];

/*
  count the number of non-ascending sequence {a[i]}
  where a[i] is in [L[i] , R[i]]
  divide 0 ... max{R[i]} into O(N) segments
  let DP[i][j] = number of ways to allocate the first i elements into some segments
  that are allocated in the last j segments

  So to get DP[i][j] , we can fix the elements a[i]...a[k] , so that they are
  all in the j-th segment. the number of ways to do this can be viewed as the number of ways for
  x[L] + x[L+1]+ ... + x[R] = i - k + 1, where each x can be 0. Why?
  need to select i - k + 1 integers from [L , R]
  this is just C(n , r)
  after that, we can multiply this by DP[k - 1][j + 1], and we repeat this for all k <= i

  notice that, after this procedure, for i, we are only calculating the number of ways
  such that some group of elements including a[i] are placed in segment j, this is not yet
  the definition of DP[i][j].
  so we need to do DP[i][j] = DP[i][j] + DP[i][j + 1] + ... + DP[i][M]
  as by difinition, we want to allocate first i elements in some of the last j segments

*/

ll qpow(ll x , ll n){ // quick power of x
  ll ret = 1;
  while(n){
    if(n & 1)ret = ret * x % mod;
    x = x * x % mod;
    n >>= 1;
  }
  return ret;
}

ll inverse(int x){ // find y st y * x % mod = 1
  return qpow(x , mod - 2);
}

void init(){ // init factorial and inverse
  F[0] = 1ll;
  for(int i = 1; i < maxn * 4; ++i){
    F[i] = F[i - 1] * i % mod;
  }
  INV[maxn * 4 - 1] = inverse(F[maxn * 4 - 1]);
  for(int i = maxn * 4 - 2; i >= 0; --i){
    INV[i] = INV[i + 1] * (i + 1) % mod;
  }
}

void discrete(){
  t.clear();
  t.push_back(-1);
  for(int i = 1; i <= N; ++i){
    t.push_back(L[i]);
    t.push_back(R[i]);
  }
  sort(all(t));
  t.resize(unique(all(t)) - t.begin());
  M = t.size() - 1;
  for(int i = 1; i <= N; ++i){
    L[i] = lower_bound(all(t) , L[i]) - t.begin();
    R[i] = lower_bound(all(t) , R[i]) - t.begin();
  }
}

ll C(ll n , int r){
  ll ret = 1ll;
  for(int i = n; i > n - r; --i)ret = ret * i % mod;
  return ret * INV[r] % mod;
}

int main(){
  init();
  cin >> N;
  ll fenmu = 1;
  for(int i = 1; i <= N; ++i){
    cin >> L[i] >> R[i];
    ++R[i];
    fenmu = fenmu * inverse(R[i] - L[i]) % mod;
  }
  discrete();
  for(int i = 0; i <= M; ++i){
    DP[0][i] = 1;
  }
  for(int i = 1; i <= N; ++i){
    for(int j = L[i]; j < R[i]; ++j){ // will be placed in jth segment
      for(int k = i; k >= 1; --k){ // a[k]..a[i] will be in jth segment
        if(j < L[k] || R[k] <= j)break; // a[k] can not be placed in jth segment , so a[k - 1] .. a[1] can not be placed here as well
        DP[i][j] = (DP[i][j] + DP[k - 1][j + 1] * C(t[j + 1] - t[j] + i - k , i - k + 1) % mod) % mod;
      }
    }
    // for i, we have cases when a[i]..a[k] is on segment j only
    // need to complete the definition of DP[i][j]
    for(int j = M - 1; j >= 1; --j){
      DP[i][j] = (DP[i][j] + DP[i][j + 1]) % mod;
    }
  }
  cout << fenmu * DP[N][1] % mod << endl;
}
