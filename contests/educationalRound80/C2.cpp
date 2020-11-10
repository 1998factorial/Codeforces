#include <iostream>
using namespace std;
typedef long long ll;

/*
key observation : a[1] <= a[2] <= ... <= a[M] <= b[M] <= b[M - 1] <= ... <= b[1]
forming a sequence of length 2 * M consisting only elements from 1 to N
dp[len][ending value] -> O(M * N * N)
*/

int N , M;
const ll mod = 1e9 + 7;
ll dp[22][1005];

int main(){
  cin >> N >> M;
  for(int i = 1; i <= N; ++i)dp[1][i] = 1;
  for(int i = 2; i <= 2 * M; ++i){
    for(int j = 1; j <= N; ++j){
      for(int k = 1; k <= j; ++k){
        dp[i][j] = (dp[i][j] + dp[i - 1][k]) % mod;
      }
    }
  }
  ll ret = 0;
  for(int i = 1; i <= N; ++i){
    ret = (ret + dp[2 * M][i]) % mod;
  }
  cout << (ret + mod) % mod << endl;
}
