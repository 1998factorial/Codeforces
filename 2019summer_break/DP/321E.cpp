#include <bits/stdc++.h>
using namespace std;

const int inf = 1e9 + 10;
const int maxn = 4e3 + 10;
int N , K;
int g[maxn][maxn];
int dp[maxn][maxn];
int cost[maxn][maxn];
int sum[maxn][maxn];

//[i , ... , j - 1] + [j]
//cost[i][j] = cost[i][j - 1] + sum[j][j] - sum[j][i - 1]
//cost[i][j] is convex and hence we can use D & C trick

void solve(int l , int r , int x , int y , int k){
  if(x >= y)return;
  int best = -1;
  int mid = (x + y) >> 1;
  dp[mid][k] = inf;
  for(int i = l; i <= min(r , mid); ++i){
    int val = dp[i - 1][k - 1] + cost[i][mid];//cost(i , mid);
    if(val < dp[mid][k])dp[mid][k] = val , best = i;
  }
  solve(l , best , x , mid, k);
  solve(best , r , mid + 1 , y , k);
}

int main(){
  scanf("%d %d" , &N , &K);
  for(int i = 1; i <= N; ++i){
    sum[i][0] = 0;
    for(int j = 1; j <= N; ++j){
      getchar();
      char a; a = getchar();
      g[i][j] = a - '0';
      sum[i][j] = sum[i][j - 1] + g[i][j];
    }
  }
  for(int len = 1; len <= N; ++len){
    for(int i = 1; i + len - 1 <= N; ++i){ // O(N * N) = O(16e6)
      int j = i + len - 1;
      cost[i][j] = cost[i][j - 1] + sum[j][j] - sum[j][i - 1];
    }
  }
  for(int i = 1; i <= N; ++i){
    dp[i][1] = cost[1][i];
  }
  for(int j = 2; j <= K; ++j){ // O(K * N * logN) = 800 * 4000 * 11 = OK
    solve(1 , N , 1 , N + 1 , j);
  }
  printf("%d\n" , dp[N][K]);
}
