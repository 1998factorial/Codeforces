#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdio>
#include <vector>
using namespace std;
typedef long long ll;
// easy version O(n * 2^n)
int n,T;
int t[20],g[20];
const ll mod = 1e9 + 7;
ll dp[1 << 15][15];
bool vis[1 << 15][15];
ll ret;
int cost[1 << 15];

int check(int state){
  int sum = 0;
  for(int i = 0; i < n; ++i){
    if(state & (1 << i))sum += t[i];
  }
  return sum;
}

ll solve(int state , int pos){
  if(vis[state][pos])
    return dp[state][pos];
  vis[state][pos] = true;
  int nex = state ^ (1 << pos);
  for(int i = 0; i < n; ++i){
    if(((1 << i) & nex )){
      if(g[i] != g[pos])
        dp[state][pos] = (dp[state][pos] + solve(nex , i)) % mod;
      else
        solve(nex , i);
    }
  }
  return (dp[state][pos] + mod ) % mod;
}

int main(){
  cin >> n >> T;
  for(int i = 0; i < n; ++i){
    cin >> t[i] >> g[i];
  }
  ret = 0;
  memset(vis,false,sizeof(vis));
  memset(dp,0,sizeof(dp));
  for(int i = 0; i < n; ++i){
    dp[1 << i][i] = 1ll;
    vis[1 << i][i] = true;
  }
  for(int i = 0; i < (1 << n); ++i){
    cost[i] = check(i);
  }
  for(int i = 0; i < n; ++i){
    solve((1 << n) - 1, i);
  }
  for(int i = 0; i < (1 << n); ++i){
    if(cost[i] == T){
      for(int j = 0; j < n; ++j){
        ret = (ret + dp[i][j]) % mod;
      }
    }
  }
  cout << (ret + mod) % mod << endl;
}
