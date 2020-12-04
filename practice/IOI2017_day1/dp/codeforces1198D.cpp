#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;

int N;
int dp[55][55][55][55];
string s[55];

int solve(int a , int b , int c , int d){
  if(dp[a][b][c][d] != -1)return dp[a][b][c][d];
  if(a == c && b == d){
    dp[a][b][c][d] = (s[a][b] == '#');
    return dp[a][b][c][d];
  }
  int ret = max(c - a + 1 , d - b + 1);
  for(int x = b; x < d; ++x)ret = min(ret , solve(a , b , c , x) + solve(a , x + 1 , c , d));
  for(int x = a; x < c; ++x)ret = min(ret , solve(a , b , x , d) + solve(x + 1 , b , c , d));
  return dp[a][b][c][d] = ret;
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> N;
  for(int i = 0; i < N; ++i){
    cin >> s[i];
  }
  for(int a = 0; a < N; ++a)
    for(int b = 0; b < N; ++b)
      for(int c = 0; c < N; ++c)
        for(int d = 0; d < N; ++d)
          dp[a][b][c][d] = -1;
  cout << solve(0 , 0 , N - 1 , N - 1) << endl;
}
