#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl
using namespace std;
typedef long long ll;
typedef pair<int , int> ii;


double DP[305][305];
int N , M , L , U , R , D;

void solve(){
  cin >> N >> M >> L >> U >> R >> D;
  memset(DP , 0 , sizeof(DP));
  DP[1][1] = 1;
  for(int i = 1; i <= N; ++i){
    for(int j = 1; j <= M; ++j){
      if(i >= L && i <= R && j >= U && j <= D)continue;
      if(i < N && j < M){
        DP[i + 1][j] += 0.5 * DP[i][j];
        DP[i][j + 1] += 0.5 * DP[i][j];
      }
      if(i < N && j == M){
        DP[i + 1][j] += DP[i][j];
      }
      if(i == N && j < M){
        DP[i][j + 1] += DP[i][j];
      }
    }
  }
  cout << DP[N][M] << endl;
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int T; cin >> T;
  for(int t = 1; t <= T; ++t){
    cout << "Case #" << t << ": ";
    solve();
  }
}
