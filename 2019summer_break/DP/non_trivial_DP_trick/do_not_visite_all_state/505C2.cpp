#include <iostream>
#include <algorithm>
#include <unordered_map>
using namespace std;

const int maxn = 3e4 + 10;
const int inf = 1e9;
int N , D;
int cnt[maxn];
int max_dis = 0;
bool vis[maxn][1000];
int dp[maxn][1000];

/*
  D -> D - 1 -> D - 2 -> ...
  at most sqrt(N) times
  D -> D + 1 -> D + 2 -> ...
  at most sqrt(N) times
  so dp[N][2 * sqrt(N) + 2]
*/

int solve(int pos , int len){
  if(pos > max_dis)return 0;
  if(vis[pos][len])return dp[pos][len];
  int ret = 0;
  if(len + 1 > 0 && len + pos + 1 <= max_dis){
    ret = max(ret , solve(pos + len + 1 , len + 1) + cnt[pos + len + 1]);
  }
  if(len > 0 && len + pos <= max_dis){
    ret = max(ret , solve(pos + len , len) + cnt[pos + len]);
  }
  if(len - 1 > 0 && pos + len - 1 <= max_dis){
    ret = max(ret , solve(pos + len - 1 , len - 1) + cnt[pos + len - 1]);
  }
  dp[pos][len] += ret;
  vis[pos][len] = 1;
  return dp[pos][len];
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> N >> D;
  for(int i = 1; i <= N; ++i){
    int x ; cin >> x;
    cnt[x]++;
    if(max_dis < x)max_dis = x;
  }
  dp[D][D] = cnt[D];
  cout << solve(D , D) << endl;
}
