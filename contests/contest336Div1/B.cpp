#include <iostream>
using namespace std;
//zuma , codeforces round 336 Div2 B
//:p
const int N = 505;
int n , a[N] , dp[N][N];
//n <= 500
//can only remove palindrome
int main(){
  cin >> n;
  for(int i = 1; i <= n; ++i){
    cin >> a[i];
  }
  for(int i = 1; i <= n; ++i){
    for(int j = 1; j <= n; ++j){ //ini
      if(i > j){
        dp[i][j] = 0;
      }
      else if(i < j){
        dp[i][j] = n;
      }
      else{
        dp[i][j] = 1;
      }
    }
  }
  for(int len = 2; len <= n; ++len){
    for(int i = 1; i + len - 1 <= n; ++i){
      int j = i + len - 1;
      if(a[i] == a[j])
        dp[i][j] = (i + 1 == j) ? dp[i + 1][j - 1] + 1 : dp[i + 1][j - 1];
      for(int k = i; k < j; ++k){
        dp[i][j] = min(dp[i][j] , dp[i][k] + dp[k + 1][j]);
      }
    }
  }
  cout << dp[1][n] << endl;
}
