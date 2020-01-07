#include <iostream>
#include <vector>
#include <map>
#include <cstring>
#include <algorithm>
using namespace std;

const int inf = 1e9 + 10;
int N , a[105];
map<int , int> mp , inv;
int dp[105][1 << 17];
int best[105][1 << 17];
int pre[105][1 << 17];
int mask[65];
int tot;

bool is_prime(int n ){
  for(int i = 2; i * i <= n; ++i){
    if(n % i == 0)return false;
  }
  return true;
}

int abs(int x){
  return x >= 0 ? x : -x;
}

void show(int state){
  string ret = "";
  for(int i = 1; i <= state; i <<= 1){
    if(i & state)ret += '1';
    else ret += '0';
  }
  reverse(ret.begin() , ret.end());
  cout << ret;
}

int main(){
  for(int i = 2; i <= 60; ++i){
    if(is_prime(i))mp[i] = tot , inv[tot] = i , ++tot;
  }
  for(int i = 2; i <= 60; ++i){
    int k = i;
    for(int j = 2; j <= i; ++j){
      if(k % j == 0){
        mask[i] |= (1 << mp[j]);
        while(k % j == 0)k /= j;
      }
    }
  }
  cin >> N; for(int i = 1; i <= N; ++i)cin >> a[i];
  for(int i = 0; i <= N; ++i){
    for(int j = 0; j < (1 << 17); ++j){
      dp[i][j] = inf;
    }
  }
  dp[0][0] = 0;
  for(int i = 1; i <= N; ++i){
    for(int j = 1; j <= 60; ++j){
      int x = (~mask[j]) & ((1 << 17) - 1);
      for(int s = x; s >= 0; s = (s - 1) & x){ // iterate over subset
        if(dp[i][s | mask[j]] > dp[i - 1][s] + abs(a[i] - j)){
          dp[i][s | mask[j]] = dp[i - 1][s] + abs(a[i] - j);
          best[i][s | mask[j]] = j;
          pre[i][s | mask[j]] = s;
        }
        if(s == 0)break;
      }
    }
  }
  int ret = inf , tg = 0;
  for(int i = 0; i < (1 << 17); ++i){
    if(ret > dp[N][i])ret = dp[N][i] , tg = i;
  }
  vector<int> ans;
  for(int i = N; i >= 1; --i){
    ans.push_back(best[i][tg]);
    tg = pre[i][tg];
  }
  reverse(ans.begin() , ans.end());
  for(int i : ans)cout << i << " ";
  cout << endl;
}
