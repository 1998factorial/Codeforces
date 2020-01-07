#include <iostream>
#include <algorithm>
using namespace std;

const int maxn = 3e4 + 10;
const int inf = 1e9;
int N , D;
int cnt[maxn];
int dp[maxn][maxn];

/*
  simple O(N ^ 2) solution will go TLE
*/

int main(){
  cin >> N >> D;
  int max_dis = 0;
  for(int i = 1; i <= N; ++i){
    int x ; cin >> x;
    cnt[x]++;
    if(max_dis < x)max_dis = x;
  }
  for(int i = 0; i <= max_dis; ++i){
    for(int j = 0; j <= max_dis; ++j){
      dp[i][j] = -inf;
    }
  }
  dp[D][D] = cnt[D];
  int ret = 0;
  for(int i = D; i <= max_dis; ++i){
    for(int j = max_dis; j >= 1; --j){
      if(dp[i][j] < 0)continue;
      if(i + j + 1 <= max_dis && dp[i + j + 1][j + 1] < dp[i][j] + cnt[i + j + 1]){
        dp[i + j + 1][j + 1] = dp[i][j] + cnt[i + j + 1];
        ret = max(ret , dp[i + j + 1][j + 1]);
      }
      if(i + j <= max_dis && dp[i + j][j] < dp[i][j] + cnt[i + j]){
        dp[i + j][j] = dp[i][j] + cnt[i + j];
        ret = max(ret , dp[i + j][j]);
      }
      if(i + j - 1 <= max_dis && j - 1 > 0 && dp[i + j - 1][j - 1] < dp[i][j] + cnt[i + j - 1]){
        dp[i + j - 1][j - 1] = dp[i][j] + cnt[i + j - 1];
        ret = max(ret , dp[i + j - 1][j - 1]);
      }
    }
  }
  cout << ret << endl;
}
