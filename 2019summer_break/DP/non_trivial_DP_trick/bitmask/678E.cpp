#include <iostream>
using namespace std;

int N;
double p[20][20];
double dp[1 << 20][20];
bool vis[1 << 20][20];

double solve(int s , int i){
  if(vis[s][i])return dp[s][i];
  vis[s][i] = 1;
  double pp = 0;
  for(int j = 0; j < N; ++j){
    if(s & (1 << j) && i != j){
      pp += solve(s ^ (1 << i) , j) * p[i][j];
      dp[s][i] = max(dp[s][i] , solve(s ^ (1 << j) , i) * p[i][j]);
    }
  }
  dp[s][i] = max(dp[s][i] , pp);
  return dp[s][i];
}

int main(){
  cin >> N;
  if(N == 1){
    double ret = 1;
    printf("%lf\n" , ret);
    return 0;
  }
  for(int i = 0; i < N; ++i){
    for(int j = 0; j < N; ++j){
      scanf("%lf" , &p[i][j]);
    }
  }
  for(int i = 0; i < N; ++i){
    for(int j = i + 1; j < N; ++j){
      int s = (1 << i) | (1 << j);
      dp[s][i] = p[i][j];
      dp[s][j] = p[j][i];
      vis[s][i] = vis[s][j] = 1;
    }
  }
  printf("%f\n" , solve((1 << N) - 1 , 0));
}
