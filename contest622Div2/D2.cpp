#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5 + 10;
struct event{
  int pos , val , id;
  event(){}
  event(int a , int b , int c): pos(a) , val(b) , id(c){}
  bool operator < (const event rhs) const {
    if(pos == rhs.pos)return val < rhs.val;
    return pos < rhs.pos;
  }
} events[maxn << 1];
int N , M , K;
int idmap[maxn];
int dp[maxn << 1][1 << 8];
int popcount[1 << 8];
int mask[maxn << 1];
int bitpos[maxn];

int find(int state){ // return the first used bit
  int ret = 0;
  for(int i = 0; i < K; ++i){
    if((state & (1 << i)) == 0){
      ret = i;
      break;
    }
  }
  return ret;
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> N >> M >> K;
  for(int i = 1; i <= N; ++i){
    int l , r; cin >> l >> r;
    events[i] = event(l , 1 , i);
    events[i + N] = event(r + 1 , -1 , i);
  }
  sort(events + 1 , events + 1 + N * 2);
  for(int i = 0; i < (1 << K); ++i){
    popcount[i] = __builtin_popcount(i) % 2;
  }
  for(int i = 1; i <= N * 2; ++i){
    int dis = events[i].pos - events[i - 1].pos;
    if(events[i].val == 1){ // adding
      bitpos[events[i].id] = find(mask[i - 1]); // find first unused bit in previous mask
      int t = bitpos[events[i].id];
      mask[i] = mask[i - 1] | (1 << t);
      for(int s = 0; s < (1 << K); ++s){
        if((s | mask[i - 1]) != mask[i - 1])continue; // s is subset of mask[i - 1]
        // we can choose to include this interval or not
        int inc = (popcount[s] == 1) ? dis : 0;
        dp[i][s | (1 << t)] = max(dp[i][s | (1 << t)] , dp[i - 1][s] + inc);
        dp[i][s] = max(dp[i][s] , dp[i - 1][s] + inc);
      }
    }
    else{ // leaving
      int t = bitpos[events[i].id]; // removing this interval from all states that include it
      mask[i] = mask[i - 1] ^ (1 << t);
      for(int s = 0; s < (1 << K); ++s){
        if((s | mask[i - 1]) != mask[i - 1])continue; // s is subset of mask[i - 1]
        // which ever states that include this interval will now be transited to another reachable state
        int inc = (popcount[s] == 1) ? dis : 0;
        if((s & (1 << t))){
          dp[i][s ^ (1 << t)] = max(dp[i][s ^ (1 << t)] , dp[i - 1][s] + inc);
        }
        else{
          dp[i][s] = max(dp[i][s] , dp[i - 1][s] + inc);
        }
      }
    }
  }
  int ans = 0;
  /*for(int i = 1; i <= 2 * N; ++i){
    for(int s = 0; s < (1 << K); ++s){
      if((s | mask[i]) == mask[i]){
        printf("dp[%d][%d] = %d\n" , i , s , dp[i][s]);
      }
    }
  }*/
  for(int s = 0; s < (1 << K); ++s){
    if((s | mask[N * 2]) != mask[N * 2])continue; // not a subset
    ans = max(ans , dp[N * 2][s]);
  }
  cout << ans << endl;
}
