#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
typedef long long ll;
int n , m , mod;
ll dp[505][505];
// dp[x][i] = up to xth row , # of ways such that there are i cols sum 0 and j cols sum to 1
// 2x = 2(n - i - j) + j = 2n - 2i - j
// j = 2n - 2x - 2i = 2 (n - x - i)
// where j = 2 (n - x - i)
string a[505];
int main(){
  cin >> n >> m >> mod;
  for(int i = 0; i < m; ++i){
    cin >> a[i];
  }
  for(int i = 0; i < n; ++i){
    for(int j = 0; j < n; ++j){
        dp[i][j] = 0ll;
    }
  }
  vector<int> col(n , 0);
  for(int i = 0; i < n; ++i){
    for(int j = 0; j < m; ++j){
      if(a[j][i] == '1')
        ++col[i];
    }
  }
  vector<int> cnt(3 , 0);
  for(int i = 0; i < n; ++i){
    ++cnt[col[i]];
  }
  dp[m][cnt[0]] = 1ll;
  for(int x = m; x < n; ++x){
    for(int i = 0; i <= n; ++i){
      int j = 2 * (n - x - i);
      if(j > n || j < 0 || !dp[x][i])continue;
      if(i - 2 >= 0){
        //choose 2 cols sum to 0
        dp[x + 1][i - 2] = (dp[x + 1][i - 2] + (dp[x][i] * (i) * (i - 1) / 2 ) % mod ) % mod;
      }
      if(j - 2 >= 0){
        //choose 2 cols sum to 1
        dp[x + 1][i] = (dp[x + 1][i] + (dp[x][i] * (j) * (j - 1) / 2 ) % mod ) % mod;
      }
      if(i - 1 >= 0 && j >= 0){
        //choose 1 col for each
        dp[x + 1][i - 1] = (dp[x + 1][i - 1] + (dp[x][i] * (i) * (j) ) % mod ) % mod;
      }
    }
  }
  cout << (dp[n][0] + mod ) % mod << endl;
}
