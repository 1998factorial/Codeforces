#include <iostream>
using namespace std;
typedef long long ll;

const ll mod = 1e9 + 7;
int N , H;
ll a[2005];
ll dp[2005][2005];

/*
  dp[pos][# of open interval]
*/

int main(){
  cin >> N >> H;
  for(int i = 1; i <= N; ++i)cin >> a[i];
  dp[0][0] = 1;
  for(int i = 1; i <= N; ++i){
    int x = H - a[i];
    if(x == 0){
      dp[i][x] = (dp[i][x] + dp[i - 1][x]) % mod;
    }
    else if(x > 0){
      dp[i][x] = (dp[i][x] + dp[i - 1][x]) % mod; // a[i] does nothing
      dp[i][x - 1] = (dp[i][x - 1] + dp[i - 1][x - 1] * x % mod) % mod; // a[i] is [] , ] has x choices
      dp[i][x] = (dp[i][x] + dp[i - 1][x - 1]) % mod; // a[i] is [
      dp[i][x - 1] = (dp[i][x - 1] + dp[i - 1][x] * x % mod) % mod; // a[i] is ] , ] has x choices
    }
  }
  cout << (dp[N][0] + mod) % mod << endl;
}
