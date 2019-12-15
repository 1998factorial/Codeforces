#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdio>
#include <vector>
using namespace std;
typedef long long ll;
// n <= 50 , ti <= 50 , T <= 2500 , 1 <= gi <= 3
// number of ways to play songs st
// cost T mins in total & no 2 consecutive songs have same genre
int n , T;
const int mod = 1e9 + 7;
const int maxn = 55;
ll fact[maxn];
ll s[3][maxn][maxn][maxn]; // number of good grouping st 0/1/2 place at front with #1 = i, #2 = j, #3 = k
ll cnt[maxn][maxn][maxn]; // number of valid ways of (#1 = i , #2 = j , #3 = k)
ll dp[3][maxn][2550]; // number of ways to have j songs in genre i cost k mins
int main(){
  cin >> n >> T;
  fact[0] = 1ll;
  for(int i = 1; i <= n; ++i)fact[i] = (fact[i - 1] * i) % mod;
  memset(cnt , 0 , sizeof(cnt));
  memset(s , 0 , sizeof(s));
  cnt[0][0][0] = 1ll;
  s[0][1][0][0] = s[1][0][1][0] = s[2][0][0][1] = 1;
  for(int i = 0; i < n; ++i){
    for(int j = 0; j + i < n; ++j){
      for(int k = 0; i + j + k < n; ++k){
        for(int x = 0; x < 3; ++x){
          if(x != 0)
            s[0][i + 1][j][k] = (s[0][i + 1][j][k] + s[x][i][j][k]) % mod;
          if(x != 1)
            s[1][i][j + 1][k] = (s[1][i][j + 1][k] + s[x][i][j][k]) % mod;
          if(x != 2)
            s[2][i][j][k + 1] = (s[2][i][j][k + 1] + s[x][i][j][k]) % mod;
        }
      }
    }
  }
  for(int i = 0; i <= n; ++i){
    for(int j = 0; j + i <= n; ++j){
      for(int k = 0; k + j + i <= n; ++k){
        if(i || j || k){
          cnt[i][j][k] = (s[0][i][j][k] + s[1][i][j][k] + s[2][i][j][k]) % mod;
          cnt[i][j][k] = (cnt[i][j][k] * fact[i]) % mod;
          cnt[i][j][k] = (cnt[i][j][k] * fact[j]) % mod;
          cnt[i][j][k] = (cnt[i][j][k] * fact[k]) % mod;
        }
      }
    }
  }
  vector<int> g[3]; // get all inputs in adj list form
  for(int i = 0 , x , y ; i < n; ++i){
    cin >> x >> y;
    g[y - 1].push_back(x);
  }
  for(int i = 0; i < 3; ++i)
    dp[i][0][0] = 1ll;
  for(int x = 0; x < 3; ++x){ // category x
    for(int i = 0; i < g[x].size(); ++i){ // enumerate i-th song
      int cost = g[x][i];
      for(int j = g[x].size(); j > 0; --j){ // have j songs
        for(int k = T; k >= cost; --k){ // using k mins
          if(k - cost >= 0 && dp[x][j - 1][k - cost]){
            dp[x][j][k] = (dp[x][j][k] + dp[x][j - 1][k - cost]) % mod;
          }
        }
      }
    }
  }
  ll ans = 0;
  for(int i = 0; i <= g[0].size(); ++i){
    for(int c0 = 0; c0 <= T; ++c0){
      if(dp[0][i][c0]){
        for(int j = 0; j <= g[1].size(); ++j){
          for(int c1 = 0; c1 + c0 <= T; ++c1){
            if(dp[1][j][c1]){
              for(int k = 0; k <= g[2].size(); ++k){
                if(dp[2][k][T - c0 - c1]){
                  ll ret = 1ll;
                  ret = (ret * dp[0][i][c0]) % mod;
                  ret = (ret * dp[1][j][c1]) % mod;
                  ret = (ret * dp[2][k][T - c0 - c1] % mod);
                  ret = (ret * cnt[i][j][k]) % mod;
                  ans = (ans + ret) % mod;
                }
              }
            }
          }
        }
      }
    }
  }
  cout << (ans + mod) % mod << endl;
}
