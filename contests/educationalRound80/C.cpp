#include <iostream>
using namespace std;
typedef long long ll;

const ll mod = 1e9 + 7;
ll dp[11][1005][1005];
int M , N;

int main(){
  cin >> N >> M;
  for(int a = 1; a <= N; ++a){
    for(int b = a; b <= N; ++b){
      dp[1][a][b] = 1;
    }
  }
  for(int i = 1; i < M; ++i){
    for(int a = 1; a <= N; ++a){
      for(int b = a; b <= N; ++b){
        if(dp[i][a][b]){
          for(int aa = a; aa <= N; ++aa){
            for(int bb = aa; bb <= b; ++bb){
              dp[i + 1][aa][bb] = (dp[i + 1][aa][bb] + dp[i][a][b]) % mod;
            }
          }
        }
      }
    }
  }
  ll ret = 0;
  for(int a = 1; a <= N; ++a){
    for(int b = a; b <= N; ++b){
      ret = (ret + dp[M][a][b]) % mod;
    }
  }
  cout << (ret + mod) % mod << endl;
}
