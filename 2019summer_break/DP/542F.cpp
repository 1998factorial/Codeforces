#include <bits/stdc++.h>
using namespace std;

/*
  this problem killed me :(

  notice that if we ask x questions , then we can only complete the tasks
  where its cost of time is no more than T - x. that means we can do this task
  at depth (as a binary tree) T - x , thus grouping tasks by their depths

  then we can do DP , at depth i , with at most j leafs , pick k maximal value tasks , and notice that
  these k tasks are leafs , thus at depth i , there will be at most min(N , 2 * (j - k)) leafs

  let dp[i][j] = maximal value we can obtain at depth i , with at most j leafs

  the transition : dp[i][j] = max{dp[i][j] , sum[1 .. k] + dp[i + 1][min(N , 2 * (j - k))]}
*/

int N , T;
vector<int> tasks[105];
int sum[105][105];
int dp[105][1005];
bool vis[105][1005];

int solve(int dep , int num){ // recursive way
  if(dep == T)return 0;
  if(vis[dep][num])return dp[dep][num];
  vis[dep][num] = 1;
  for(int leafs = 0; leafs <= tasks[dep].size() && leafs <= num; ++leafs){
    dp[dep][num] = max(dp[dep][num] , sum[dep][leafs] + solve(dep + 1 , min(N , (num - leafs) * 2)));
  }
  return dp[dep][num];
}

int main(){
  cin >> N >> T;
  for(int i = 1; i <= N; ++i){
    int t , q; cin >> t >> q;
    tasks[T - t].push_back(q);
  }
  for(int i = 0; i <= T; ++i){
    sort(tasks[i].begin() , tasks[i].end() , [&](int x , int y){
      return x > y;
    });
    sum[i][0] = 0;
    for(int j = 0; j < tasks[i].size(); ++j)sum[i][j + 1] = sum[i][j] + tasks[i][j];
  }
  //cout << solve(0 , 1) << endl;
  for(int dep = T - 1; dep >= 0; --dep){ // iterative way
    for(int nv = 0; nv <= N; ++nv){
      for(int leafs = 0; leafs <= tasks[dep].size() && leafs <= nv; ++leafs){
        dp[dep][nv] = max(dp[dep][nv] , dp[dep + 1][min(N , 2 * (nv - leafs))] + sum[dep][leafs]);
      }
    }
  }
  cout << dp[0][1] << endl;
}
