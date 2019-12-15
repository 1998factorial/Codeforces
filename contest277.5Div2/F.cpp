#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
typedef long long ll;
int n , m , mod;
ll dp[2][505][505]; // TLE
// dp[x][i][j] = up to xth row , # of ways such that there are i cols sum 0 and j cols sum to 1
string a[505];
int main(){
  cin >> n >> m >> mod;
  for(int i = 0; i < m; ++i){
    cin >> a[i];
  }
  for(int i = 0; i < 2; ++i){
    for(int j = 0; j < n; ++j){
      for(int k = 0; k < n; ++k){
        dp[i][j][k] = 0ll;
      }
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
  dp[m % 2][cnt[0]][cnt[1]] = 1ll;
  for(int x = m; x <=n; ++x){
    for(int i = 0; i <= n; ++i){
      for(int j = 0; j <= n; ++j){
        if(j - 2 >= 0){
          //put at 2 col sum to 1
          dp[(x + 1) % 2][i][j - 2] = (dp[(x + 1) % 2][i][j - 2] + ( dp[x % 2][i][j] * (j) * (j - 1) / 2 ) % mod) % mod;
        }
        if(i - 2 >= 0 && j + 2 <= n){
          //put at 2 col sum to 0
          dp[(x + 1) % 2][i - 2][j + 2] = (dp[(x + 1) % 2][i - 2][j + 2] + ( dp[x % 2][i][j] * (i) * (i - 1) / 2 ) % mod) % mod;
        }
        if(i - 1 >= 0){
          //put ont at col sum to 0 and one at col sum to 1
          dp[(x + 1) % 2][i - 1][j] = (dp[(x + 1) % 2][i - 1][j] + ( dp[x % 2][i][j] * (i) * (j)) % mod) % mod;
        }
      }
    }
  }
  cout << (dp[n % 2][0][0] + mod ) % mod << endl;
}
