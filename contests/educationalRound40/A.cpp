#include <bits/stdc++.h>
using namespace std;

int dp[105];
char s[105];

int main(){
  int N;
  cin >> N;
  for(int i = 1; i <= N; ++i)cin >> s[i];
  dp[0] = 0;
  dp[1] = 1;
  for(int i = 2; i <= N; ++i){
    dp[i] = dp[i - 1] + 1;
    if(s[i] != s[i - 1]){
      dp[i] = min(dp[i] , dp[i - 2] + 1);
    }
  }
  cout << dp[N] << endl;
}
