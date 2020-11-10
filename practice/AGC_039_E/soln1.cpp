#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

string str[45];
int A[45][45];
int N;
ll DP[45][45][45];


ll solve(int l , int r , int m){
  if(l == r)return 1;
  if(l == m || r == m)return 0;
  if(~DP[l][r][m])return DP[l][r][m];
  DP[l][r][m] = 0;
  for(int j = l; j < m; ++j){
    for(int k = m + 1; k <= r; ++k){
      if(A[j][k]){ // cut (j , k)
        for(int x = j; x < m; ++x){
          for(int y = m; y < k; ++y){
            DP[l][r][m] += solve(l , x , j) * solve(x + 1 , y , m) * solve(y + 1 , r , k);
          }
        }
      }
    }
  }
  return DP[l][r][m];
}


int main(){
  cin >> N;
  for(int i = 1; i <= 2 * N; ++i){
    cin >> str[i];
  }
  for(int i = 1; i <= 2 * N; ++i){
    for(int j = 0; j < 2 * N; ++j){
      A[i][j + 1] = str[i][j] == '1';
    }
  }
  ll ret = 0;
  memset(DP , -1 , sizeof(DP));
  for(int i = 2; i <= 2 * N; ++i){
    if(A[1][i]){
      ret += solve(2 , 2 * N , i);
    }
  }
  cout << ret << endl;
}
