#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl
using namespace std;
typedef long long ll;
typedef pair<int , int> ii;

/*
  DP[l][r][k] = maximal score we can get if the interval a[l , r] is accumulated k times
*/

const int maxn = 155;
const ll inf = 1e18;
int N , M;
int A[maxn]; // each score
int B[maxn][maxn]; // dependency
ll sum[maxn];
ll DP[maxn][maxn][maxn];
bool vis[maxn][maxn][maxn];
int L[maxn] , R[maxn];

ll solve(int l , int r , int k){
  if(l > r)return 0;
  if(vis[l][r][k])return DP[l][r][k];
  if(l == r){
    DP[l][r][k] = max(0ll , (ll)A[l]) * k;
    vis[l][r][k] = 1;
    return DP[l][r][k];
  }
  ll ret = -inf;
  for(int x = l; x <= r; ++x){
    if(L[x] < l && r < R[x]){
      ret = max(ret , solve(l , x - 1 , k + r - x) + solve(x + 1 , r , k) + sum[x - 1] - sum[l - 1]);
      ret = max(ret , solve(l , x - 1 , r - x) + solve(x + 1 , r , 0) + sum[x - 1] - sum[l - 1] + (sum[r] - sum[l - 1]) * k);
    }
  }
  vis[l][r][k] = 1;
  return DP[l][r][k] = ret;
}

int main(){
  cin >> N;
  for(int i = 1; i <= N; ++i){
    cin >> A[i];
    sum[i] = sum[i - 1] + A[i];
  }
  cin >> M;
  for(int i = 1; i <= M; ++i){
    int l , r; cin >> l >> r;
    B[l][r] = 1;
  }
  for(int i = 1; i <= N; ++i){
    L[i] = -1;
    R[i] = N + 1;
    for(int j = 1; j <= i; ++j){
      if(B[j][i]){
        L[i] = j;
      }
    }
    for(int j = N; j >= i; --j){
      if(B[j][i]){
        R[i] = j;
      }
    }
  }
  ll ret = solve(1 , N , 0);
  if(ret > -inf)cout << ret << endl;
  else cout << "Impossible" << endl;
}
