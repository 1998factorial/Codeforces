#include <iostream>
#include <algorithm>
using namespace std;

int N;
double dp[1 << 18][18] , p[18][18];
bool vis[1 << 18][18];

double solve(int s , int i){
  if(vis[s][i])return dp[s][i];
  for(int j = 0; j < N; ++j){
    if(i != j && (s & (1 << j))){
      dp[s][i] = max(dp[s][i] , solve(s ^ (1 << i) , j) * p[j][i] + solve(s ^ (1 << j) , i) * p[i][j]);
    }
  }
  vis[s][i] = 1;
  return dp[s][i];
}

int main(){
  scanf("%d" , &N);
  for(int i = 0; i < N; ++i)
    for(int j = 0; j < N; ++j)
      scanf("%lf" , &p[i][j]);
  dp[1][0] = 1;
  for(int i = 0; i < N; ++i)vis[1 << i][i] = 1;
  double ret = 0;
  for(int i = 0; i < N; ++i){
    ret = max(ret , solve((1 << N) - 1 , i));
  }
  printf("%lf\n" , ret);
}
