#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl
using namespace std;
typedef long long ll;
typedef pair<int , int> ii;
/*
  the use of SG function in NIM game
  will add more later on
*/
const int maxn = 3e5 + 10;
int N , x , y , z;
ll a[maxn];
int dp[maxn][3]; // 0 mix , 1 infantry , 2 cavalry
int period;

int mex(vector<int> vec){ // SG(v) = mex{SG(u) | u is v's child}
  // returns the smallest non negative integer that is not in vec (definition of mex)
  unordered_map<int , int> vis;
  for(int i : vec)vis[i] = 1;
  int ret = vec.size();
  for(int i = 0; i <= vec.size(); ++i){
    if(vis[i] == 0){
      ret = i;
      break;
    }
  }
  return ret;
}

int getval(int i , ll v){
  if(v > 100)
    return dp[(v - 100) % period + 100][i];
  return dp[v][i];
}

void solve(){
  // the value of a[i] is too large, so we should try to find cycle
  // notice that x , y , z are small, so intuitively, we should have cycle in short iterations
  period = -1;
  for(int i = 1; i <= 300 && period < 0; ++i){
    int nx = max(0 , i - x);
    int ny = max(0 , i - y);
    int nz = max(0 , i - z);
    dp[i][0] = mex({dp[nx][0] , dp[ny][1] , dp[nz][2]});
    dp[i][1] = mex({dp[nx][0] , dp[nz][2]});
    dp[i][2] = mex({dp[nx][0] , dp[ny][1]});
    // check if 5 consecutive rows are the same
    // reason for picking 5, max(x , y , z) is at most 5
    // notice that we just want to make sure that the whole rows of game repeats.
    bool ok = i > 100;
    for(int k = 0; k < 5; ++k){
      ok &= (dp[100 - k][0] == dp[i - k][0]) && (dp[100 - k][1] == dp[i - k][1]) && (dp[100 - k][2] == dp[i - k][2]);
    }
    if(ok){
      period = i - 100;
    }
  }
  ll S = 0;
  for(int i = 1; i <= N; ++i){
    S ^= getval(0 , a[i]);
  }
  int ans = 0;
  for(int i = 1; i <= N; ++i){
    S ^= getval(0 , a[i]);
    // try all possible attacks on a[i]
    if((S ^ getval(0 , max(0ll , a[i] - x))) == 0)++ans;
    if((S ^ getval(1 , max(0ll , a[i] - y))) == 0)++ans;
    if((S ^ getval(2 , max(0ll , a[i] - z))) == 0)++ans;
    S ^= getval(0 , a[i]);
  }
  printf("%d\n" , ans);
}


int main(){
  int t; scanf("%d" , &t);
  while(t--){
    // treat each a[i] as an individual game
    scanf("%d %d %d %d" , &N , &x , &y , &z);
    for(int i = 1; i <= N; ++i){
      scanf("%lld" , &a[i]);
    }
    solve();
  }
}
