#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl
using namespace std;
typedef long long ll;
typedef pair<int , int> ii;

const int maxn = 2e5 + 10;
char s[maxn];
int N , K;
ll T;
int A[22][22];
ll DP[1 << 22];
ll t[22];
int mask[22];

int main(){
  scanf("%d %d %lld" , &N , &K , &T);
  scanf("%s" , s + 1);
  for(int i = 0; i < K; ++i){
    scanf("%lld" , &t[i]);
  }
  for(int i = 0; i < K; ++i){
    for(int j = 0; j < K; ++j){
      scanf("%d" , &A[i][j]);
    }
  }
  for(int i = 0; i < K; ++i){
    DP[1 << i] = t[i];
    mask[i] = -1;
  }
  // compute the cost for masks that have (a , b) adj
  int S = 0;
  for(int i = 1; i <= N; ++i){
    int x = s[i] - 'A';
    S |= (1 << x);
    for(int j = 0; j < K; ++j){
      if(mask[j] >= 0){
        if((mask[j] & (1 << j)) == 0 && (mask[j] & (1 << x)) == 0){
          DP[mask[j]] += A[j][x];
          DP[mask[j] | (1 << j)] -= A[j][x];
          DP[mask[j] | (1 << x)] -= A[j][x];
          DP[mask[j] | (1 << j) | (1 << x)] += A[j][x];
        }
        mask[j] |= (1 << x);
      }
    }
    mask[x] = 0;
  }
  // O(K * 2 ^ K)
  for(int i = 0; i < K; ++i){
    for(int s = 0; s < (1 << K); ++s){
      if(s & (1 << i)){
        DP[s] += DP[s ^ (1 << i)];
      }
    }
  }
  // O(3 ^ K)
  /*for(int state = 0; state < (1 << K); ++state){
    DP2[state] = DP[0];
    for(int subset = state; subset ; subset = (subset - 1) & state){
      DP2[state] += DP[subset];
    }
  }*/
  ll ret = 0;
  for(int s = 0; s < (1 << K); ++s){
    if((s & S) == s && DP[s] <= T && s != S){
      ++ret;
    }
  }
  printf("%lld\n" , ret);
}
