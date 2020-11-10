#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int N , K;
const ll mod = 1e9 + 7;
ll DP[55][55][2500];
// DP[i][j][k] = # ways such that for the first i positions, there are j of them are left unmatched with cost = k

/*
    |1 - | + |2 - | + | - p[3]| + .. |i - |

    i is left bracket
    p[i] is right bracket

    DP[i][l][r][x]
    l left brackets not complete
    r right brackets not complete
    ith |i - p[i]|

    DP[i][j][k] = DP[i - 1][j][k - 2j] * (j + j + 1)
    + DP[i - 1][j - 1][k - 2j] * ()
    + DP[i - 1][j + 1][k - 2j] * ()

    j of them are not completed
    -> i + 1 , cost at least increased
*/

int main(){
  cin >> N >> K;
  DP[0][0][0] = 1;
  for(int i = 1; i <= N; ++i){
    for(int j = 0; j <= i; ++j){
      for(int k = 0; k <= K; ++k){
        if(k - 2 * j < 0)continue;
        ll& r = DP[i][j][k];
        r = (r + DP[i - 1][j][k - 2 * j] * (2 * j + 1) % mod) % mod; // one pair match
        if(j - 1 >= 0){
          r = (r + DP[i - 1][j - 1][k - 2 * j]) % mod; // no match
        }
        if(j + 1 <= i - 1){
          r = (r + DP[i - 1][j + 1][k - 2 * j] * ((j + 1) * (j + 1) % mod) % mod) % mod; // 2 pairs match
        }
      }
    }
  }
  cout << (DP[N][0][K] + mod) % mod << endl;
}
