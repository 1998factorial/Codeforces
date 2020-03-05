#include <iostream>
#include <algorithm>
using namespace std;
typedef long long ll;

const ll mod = 1e9 + 7;
int N , L;
int a[105];
ll dp[105][105][1005][3];

/*
  dp[i][j][k][x] = # of ways to insert the first i elements with j connected
  components , total cost being k and
  x = (0 -> no head or tail decided / 1 -> head or tail decided / 2 -> head and tail decieded)
*/

ll solve(){
  sort(a + 1 , a + 1 + N);
  dp[0][0][0][0] = 1;
  for(int i = 0; i < N; ++i){ // first i elements
    for(int j = 0; j <= i; ++j){ // j connected components
      for(int k = 0; k <= L; ++k){ // total cost
        for(int x = 0; x <= min(2 , j); ++x){ // number of fixed edges
          int nk = (a[i + 1] - a[i]) * (2 * j - x) + k;
          if(nk > L || dp[i][j][k][x] == 0)continue;
          dp[i + 1][j + 1][nk][x] = (dp[i + 1][j + 1][nk][x] + dp[i][j][k][x] * (j + 1 - x) % mod) % mod;
          // make new connected component and not edge
          if(x < 2)
            dp[i + 1][j + 1][nk][x + 1] = (dp[i + 1][j + 1][nk][x + 1] + dp[i][j][k][x] * (2 - x) % mod) % mod;
          // make new connected component and its edge
          if(j){
            dp[i + 1][j][nk][x] = (dp[i + 1][j][nk][x] + dp[i][j][k][x] * (2 * j - x)) % mod;
            // append/preppend to one connected component and not edge
            if(j > 1)
              dp[i + 1][j - 1][nk][x] = (dp[i + 1][j - 1][nk][x] + dp[i][j][k][x] * (j - 1) % mod) % mod;
              // merge 2 connected components
            if(x < 2)
              dp[i + 1][j][nk][x + 1] = (dp[i + 1][j][nk][x + 1] + dp[i][j][k][x] * (2 - x) % mod) % mod;
              // append/preppend to one connected component and being edge
          }
        }
      }
    }
  }
  for(int i = 0; i <= N; ++i){
    for(int j = 0; j <= i; ++j){
      for(int k = 0; k <= L; ++k){
        for(int x = 0; x <= 2; ++x){
          if(dp[i][j][k][x])printf("dp[%d][%d][%d][%d] = %lld\n" , i , j , k , x , dp[i][j][k][x]);
        }
      }
    }
  }
  ll ret = 0;
  for(int i = 0; i <= L; ++i){
    ret = (ret + dp[N][1][i][2]) % mod;
  }
  return ret;
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> N >> L;
  for(int i = 1; i <= N; ++i)cin >> a[i];
  if(N == 1){
    cout << 1 << endl;
  }
  else{
    cout << (solve() + mod) % mod << endl;
  }
}
