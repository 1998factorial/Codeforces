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
ll DP[maxn][maxn][maxn * 2];
int L[maxn] , R[maxn];

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
  for(int i = 1; i <= N; ++i){
    for(int j = 1; j <= N; ++j){
      for(int k = 0; k <= N; ++k){
        if(i <= j)DP[i][j][k] = -inf;
        else DP[i][j][k] = 0;
      }
    }
  }
  for(int len = 1; len <= N; ++len){
    for(int i = 1; i + len - 1 <= N; ++i){
      for(int k = 0; k <= N; ++k){
        int j = i + len - 1;
        if(i == j){
          DP[i][j][k] = max(0ll , (ll)A[i] * k);
        }
        else{
          for(int x = i; x <= j; ++x){
            if(L[x] < i && j < R[x]){
              DP[i][j][k] = max(DP[i][j][k] , DP[i][x - 1][k + j - x] + DP[x + 1][j][k] + sum[x - 1] - sum[i - 1]);
              DP[i][j][k] = max(DP[i][j][k] , DP[i][x - 1][j - x] + DP[x + 1][j][0] + sum[x - 1] - sum[i - 1] + (sum[j] - sum[i - 1]) * k);
            }
          }
        }
      }
    }
  }
  if(DP[1][N][0] > -inf)cout << DP[1][N][0] << endl;
  else cout << "Impossible" << endl;
}
