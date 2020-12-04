#include <iostream>
#include <algorithm>
using namespace std;
typedef long long ll;

ll W;
ll cnt[9];
ll L , N;
ll dp[9][10000];

/*
11994176272990019
0 6395394930893349 0 0 0 0 0 0
*/

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> W;
  for(int i = 1; i <= 8; ++i)
    cin >> cnt[i];
  for(int i = 0; i <= 8; ++i){
    for(int j = 0; j <= 7000; ++j){
      dp[i][j] = -1;
    }
  }
  dp[0][0] = 0;
  for(int i = 1; i <= 8; ++i){
    for(int j = 0; j <= 7000; ++j){
      for(int k = 0; k <= min(840ll / i , cnt[i]); ++k){
        if(j - k * i >= 0 && dp[i - 1][j - k * i] != -1){
          dp[i][j] = max(dp[i][j] , dp[i - 1][j - k * i] + (cnt[i] - k) * i / 840);
        }
      }
    }
  }
  ll ret = 0;
  for(int i = 0; i <= min(7000ll , W); ++i){
    if(dp[8][i] == -1)continue;
    ret = max(ret , i + 840ll * min((W - i) / 840 , dp[8][i]));
    //ret = max(ret , min(W , i + 840ll * dp[8][i]));
    // this failed....
  }
  cout << ret << endl;
  return 0;
}
