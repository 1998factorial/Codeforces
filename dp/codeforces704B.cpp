#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdio>
using namespace std;
typedef long long ll;

const ll inf = 1ll << 50;
const int maxn = 5005;
int N;
ll dp[maxn][maxn];
int s , e;

/*
  observations:
  1. view each chair as a node , its indeg = outdeg = 1 (apart from s and e)
  2. 4 cases to reach a chair and leave it
  maxn <= 5e3 , the state should be at least O(n^2)
  one dimension should be
*/

struct chair{
  ll X , a , b , c , d;
  int id;
}C[maxn];

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> N >> s >> e;
  for(int i = 1; i <= N; ++i)cin >> C[i].X;
  for(int i = 1; i <= N; ++i)cin >> C[i].a;
  for(int i = 1; i <= N; ++i)cin >> C[i].b;
  for(int i = 1; i <= N; ++i)cin >> C[i].c;
  for(int i = 1; i <= N; ++i)cin >> C[i].d;
  for(int i = 1; i <= N; ++i)C[i].id = i;
  for(int i = 0; i <= N; ++i)
    for(int j = 0; j <= N; ++j)
      dp[i][j] = inf;
  sort(C + 1 , C + 1 + N , [](const chair& x , const chair& y){
    return x.X < y.X;
  });
  dp[0][0] = 0;
  int tot = 0;
  for(int i = 0; i < N; ++i){
    for(int j = 0; j <= i; ++j){
      if(dp[i][j] >= inf)continue;
      int S = j , T = S + tot;
      if(C[i + 1].id == s){
        //goes to left
        if(T)dp[i + 1][j] = min(dp[i + 1][j] , dp[i][j] + C[i + 1].c + C[i + 1].X);
        //goes to right
        dp[i + 1][j + 1] = min(dp[i + 1][j + 1] , dp[i][j] + C[i + 1].d - C[i + 1].X);
      }
      else if(C[i + 1].id == e){
        //coming from left
        if(S)dp[i + 1][j - 1] = min(dp[i + 1][j - 1] , dp[i][j] + C[i + 1].a + C[i + 1].X);
        //coming from right
        dp[i + 1][j] = min(dp[i + 1][j] , dp[i][j] + C[i + 1].b - C[i + 1].X);
      }
      else{
        //left to p , p to right
        if(S)dp[i + 1][j] = min(dp[i + 1][j] , dp[i][j] + C[i + 1].a + C[i + 1].d);
        //left to p , p to left
        if(S && T)dp[i + 1][j - 1] = min(dp[i + 1][j - 1] , dp[i][j] + C[i + 1].a + C[i + 1].c + 2 * C[i + 1].X);
        //right to p , p to left
        if(T)dp[i + 1][j] = min(dp[i + 1][j] , dp[i][j] + C[i + 1].c + C[i + 1].b);
        //right to p , p to right
        dp[i + 1][j + 1] = min(dp[i + 1][j + 1] , dp[i][j] + C[i + 1].d + C[i + 1].b - 2 * C[i + 1].X);
      }
    }
    if(C[i + 1].id == s)--tot;
    if(C[i + 1].id == e)++tot;
    if(i < N - 1 && tot == 0)dp[i + 1][0] = inf; // avoid rings
  }
  /*for(int i = 0; i <= N; ++i){
    for(int j = 0; j <= i; ++j){
      printf("dp[%d][%d] = %lld\n" , i , j , dp[i][j]);
    }
  }*/
  cout << dp[N][0] << endl;
}
