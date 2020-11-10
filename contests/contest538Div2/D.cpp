#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int a[5005] , n , dp[5005][5005][2];

int main(){
  cin >> n;
  for(int i = 1; i <= n; ++i){
    cin >> a[i];
  }
  vector<int> p;
  p.push_back(a[1]);
  for(int i = 2; i <= n; ++i){
    if(a[i] != a[i - 1])p.push_back(a[i]);
  }
  n = p.size();
  for(int i = 0; i < n; ++i){
    for(int j = 0; j < n; ++j){
      for(int k = 0 ; k < 2; ++k){
        dp[i][j][k] = 0;
      }
    }
  }
  for(int len = 2; len <= n; ++len){
    for(int i = 0; i + len - 1 < n; ++i){
      int j = i + len - 1;
      dp[i][j][0] = dp[i][j][1] = 1 << 20;
      if(p[i] == p[j]){
        dp[i][j][0] = dp[i][j][1] = min(dp[i + 1][j - 1][0] , dp[i + 1][j - 1][1]) + 1;
      }
      else{
        dp[i][j][0] = min(dp[i + 1][j][0] , dp[i + 1][j][1]) + 1;
        dp[i][j][1] = min(dp[i][j - 1][0] , dp[i][j - 1][1]) + 1;
      }
    }
  }
  cout << min(dp[0][n - 1][0] , dp[0][n - 1][1]) << endl;
}
