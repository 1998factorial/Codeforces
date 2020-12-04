#include <iostream>
#include <string.h>
#include <algorithm>
using namespace std;

int dp[10005];
int N;
int tlim;

struct stone{
  int S , L , E;
  stone(){}
  stone(int s , int l , int e):S(s) , L(l) , E(e) {}
  bool operator < (const stone& other) const {
    return S * other.L < L * other.S;
  }
}a[105];

int solve(){
  int ret = 0;
  memset(dp , -1 , sizeof(dp));
  dp[0] = 0;
  for(int i = 0; i < N; ++i){
    for(int j = tlim; j >= 0; --j){
      if(dp[j] != -1 && j + a[i + 1].S <= tlim){
        dp[j + a[i + 1].S] = max(dp[j + a[i + 1].S] , dp[j] + max(0 , a[i + 1].E - a[i + 1].L * j));
        ret = max(ret , dp[j + a[i + 1].S]);
      }
    }
  }
  return ret;
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int T;
  cin >> T;
  for(int t = 1; t <= T; ++t){
    cin >> N;
    tlim = 0;
    for(int i = 1; i <= N; ++i)
      cin >> a[i].S >> a[i].E >> a[i].L , tlim += a[i].S;
    sort(a + 1 , a + 1 + N);
    cout << "Case #" << t << ": " << solve() << endl;
  }
  return 0;
}
