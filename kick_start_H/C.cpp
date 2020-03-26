#include <iostream>
#include <cstdio>
#include <string.h>
using namespace std;

int cnt[10];
bool dp[100][100][2010];
bool vis[100][100][2010];
int sum;
int zero = 1005;

bool solve(int pos , int np , int ng , int sum){
  if(pos <= 0){
    return (sum - zero) % 11 == 0;
  }
  if(vis[np][ng][sum]){
    return dp[np][ng][sum];
  }
  for(int i = 0; i <= cnt[pos]; ++i){
    if(np - i >= 0 && ng - cnt[pos] + i >= 0)
      dp[np][ng][sum] |=
        solve(pos - 1 , np - i , ng - cnt[pos] + i , sum + pos * (2 * i - cnt[pos]));
  }
  vis[np][ng][sum] = true;
  return dp[np][ng][sum];
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int T;
  cin >> T;
  for(int t = 1; t <= T; ++t){
    sum = 0;
    for(int i = 1; i <= 9; ++i)cin >> cnt[i] , sum += cnt[i];
    cout << "Case #" << t << ": ";
    memset(dp , false , sizeof(dp));
    memset(vis , false , sizeof(vis));
    int np = (sum + 1) / 2 , ng = sum / 2;
    dp[0][0][1005] = true;
    vis[0][0][1005] = true;
    if(solve(9 , np , ng , 1005))cout << "YES\n";
    else cout << "NO\n";
  }
  return 0;
}
