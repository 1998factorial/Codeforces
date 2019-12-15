#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int N;
string a;
int dp[505][505];

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> N;
  cin >> a;
  string b = "";
  b += a[0];
  for(int i = 1; i < N; ++i){
    if(a[i] != a[i - 1]){
      b += a[i];
    }
  }
  for(int i = 0; i < b.size(); ++i){
    dp[i][i] = 1;
  }
  for(int len = 2; len <= b.size(); ++len){
    for(int i = 0; i + len - 1 < b.size(); ++i){
      int j = i + len - 1;
      dp[i][j] = dp[i + 1][j] + 1;
      for(int k = i; k <= j; ++k){
        if(b[i] == b[k]){
          dp[i][j] = min(dp[i][j] , dp[i + 1][k - 1] + dp[k][j]);
        }
      }
    }
  }
  cout << dp[0][b.size() - 1] << endl;
}
