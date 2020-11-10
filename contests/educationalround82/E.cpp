#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl
using namespace std;
typedef long long ll;
typedef pair<int , int> ii;

/*
  t = a + b
  we can enumerate the length of a and see if we can use s to make a and b
  let dp[i][j][k] = if we can match a[1 ... j] and b[1 ... k] if we use s[1 ... i]
*/

const int maxn = 405;
int N , M , len;
char s[maxn] , t[maxn];
bool dp[maxn][maxn][maxn];
bool vis[maxn][maxn][maxn];

bool solve(int i , int j , int k){
  if(i > N){
    return j == len + 1 && k == M + 1;
  }
  if(vis[i][j][k]){
    return dp[i][j][k];
  }
  dp[i][j][k] |= solve(i + 1 , j , k);
  if(j <= len && s[i] == t[j]){
    dp[i][j][k] |= solve(i + 1 , j + 1 , k);
  }
  if(k <= M && s[i] == t[k]){
    dp[i][j][k] |= solve(i + 1 , j , k + 1);
  }
  vis[i][j][k] = 1;
  return dp[i][j][k];
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int T; cin >> T;
  while(T--){
    cin >> (s + 1);
    cin >> (t + 1);
    N = strlen(s + 1);
    M = strlen(t + 1);
    bool ok = 0;
    memset(dp , 0 , sizeof(dp));
    memset(vis , 0 , sizeof(vis));
    for(len = 0; len <= M && !ok; ++len){ // enumerate all possible length of a
      if(solve(1 , 1 , len + 1)){
        ok = 1;
      }
    }
    if(!ok)cout << "NO" << endl;
    else cout << "YES" << endl;
  }
}
