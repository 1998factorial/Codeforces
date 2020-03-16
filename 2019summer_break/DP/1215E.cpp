#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl
using namespace std;
typedef long long ll;
typedef pair<int , int> ii;

ll cnt[20][20]; // cnt[i][j] = cost of placing all i before j
ll num[20];
ll dp[1 << 20];
const ll inf = 1e18;
vector<int> g[20];
int N;

int main(){
  scanf("%d" , &N);
  for(int i = 1; i <= N; ++i){
    int x; scanf("%d" , &x);
    --x;
    for(int j = 0; j < 20; ++j){
      cnt[x][j] += num[j];
    }
    ++num[x];
  }
  for(int i = 0; i < (1 << 20); ++i){
    dp[i] = inf;
  }
  dp[0] = 0;
  for(int state = 0; state < (1 << 20); ++state){
    vector<int> S;
    for(int j = 0; j < 20; ++j){
      if(state & (1 << j))
        S.push_back(j);
    }
    ll t = 0;
    for(int j = 0; j < 20; ++j){
      if(!(state & (1 << j))){
        ll t = 0;
        for(int k : S){
          t += cnt[j][k];
        }
        dp[state | (1 << j)] = min(dp[state | (1 << j)] , dp[state] + t);
      }
    }
  }
  printf("%lld\n" , dp[(1 << 20) - 1]);
}
