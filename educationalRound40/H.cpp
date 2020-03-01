#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

/*
  MLE :(
  dp1[i][j] = # of nodes reachable from a node at depth i in subtree rooted at i with exactly j
  steps away from root.
  dp1[i][j] = a[i] * dp1[i + 1][j - 1]
  dp2[i][j] = # of nodes reachable from a node at depth i not in subtree rooted at i with exactly j
  steps away from root.
  dp2[i][j] = dp2[i - 1][j - 1] + (a[i - 1] - 1) * dp1[i][j - 2]
*/

const ll mod = 1e9 + 7;
const int maxn = 5005;
int N;
ll a[maxn];
int dp1[maxn][maxn << 1];
int dp2[maxn][maxn << 1];
int level[maxn];
int ans[maxn << 1];

ll add(ll a , ll b){
  return (a + b) % mod;
}

ll mul(ll a , ll b){
  return a * b % mod;
}

ll qpow(ll x , ll n){
  if(n <= 0)return 1;
  ll ret = qpow(x , n / 2);
  ret = mul(ret , ret);
  if(n % 2 == 1)ret = mul(ret , x);
  return ret;
}

int main(){
  cin >> N;
  for(int i = 1; i <= N - 1; ++i){
    cin >> a[i];
  }
  level[1] = 1;
  for(int i = 2; i <= N; ++i){ // compute level
    level[i] = mul(level[i - 1] , a[i - 1]);
  }
  for(int i = N; i >= 1; --i){ // compute sub tree at depth i
    dp1[i][0] = 1;
    for(int j = 1; j <= N - i; ++j){
      dp1[i][j] = mul(a[i] , dp1[i + 1][j - 1]);
      ans[j] = add(ans[j] , mul(dp1[i][j] , level[i]));
    }
  }
  for(int i = 1; i <= N; ++i){
    dp2[i][0] = 1;
    for(int j = 1; j <= 2 * N - 2; ++j){
      dp2[i][j] = dp2[i - 1][j - 1];
      if(i > 1 && j - 2 >= 0)dp2[i][j] = add(dp2[i][j] , mul(a[i - 1] - 1 , dp1[i][j - 2]));
      ans[j] = add(ans[j] , mul(dp2[i][j] , level[i]));
    }
  }
  for(int i = 1; i <= 2 * N - 2; ++i){
    ans[i] = mul(ans[i] , qpow(2 , mod - 2));
    cout << (ans[i] + mod) % mod << " ";
  }
  cout << endl;
}
