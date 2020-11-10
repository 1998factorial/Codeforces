#include <bits/stdc++.h>
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl
using namespace std;
typedef long long ll;
typedef pair<int , int> ii;

/*
ios::sync_with_stdio(false)
cin.tie(nullptr)
*/
/*
  # of intersecting intervals is no more than K (<= 8)
  we can store the interval intersection situation by bitset
  let dp[i-th event][set of intervals used] be the maximal satisfied childen
  under this case.
*/

const int maxn = 1e5 + 10;
int dp[2][1 << 8];
int bitcount[1 << 8];
int mask[maxn << 1]; // up to the ith event, the bits that we can use
int bitpos[maxn << 1];
int N , M , K;

struct event{
  int pos , val , id;
  event(){}
  event(int a , int b , int c) : pos(a) , val(b) , id(c){}
  bool operator < (const event rhs) const {
    if(pos == rhs.pos)return val < rhs.val;
    return pos < rhs.pos;
  }
};

vector<event> eves;

int find(int state){
  int ret = K;
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
    eves.emplace_back(l , 1 , i);
    eves.emplace_back(r + 1 , -1 , i);
  }
  sort(eves.begin() , eves.end());
  for(int s = 0; s < (1 << K); ++s)
    bitcount[s] = __builtin_popcount(s) % 2;
  int pre = 0;
  int cur = 1;
  for(auto& e : eves){
    int dis = e.pos - pre;
    pre = e.pos;
    if(e.val == 1){ // add
      int t = find(mask[cur - 1]);
      bitpos[e.id] = t;
      mask[cur] = mask[cur - 1] | (1 << t);
      for(int s = 0; s < (1 << K); ++s){
        if((s | mask[cur - 1]) != mask[cur - 1])continue;
        int inc = bitcount[s] == 1 ? dis : 0;
        // include this interval
        dp[cur % 2][s | (1 << t)] = max(dp[cur % 2][s | (1 << t)] , dp[(cur - 1) % 2][s] + inc);
        // do not include
        dp[cur % 2][s] = max(dp[cur % 2][s] , dp[(cur - 1) % 2][s] + inc);
      }
    }
    else{ // leave
      int t = bitpos[e.id];
      mask[cur] = mask[cur - 1] ^ (1 << t);
      for(int s = 0; s < (1 << K); ++s){ // iterating on subset of mask[i - 1]
        if((s | mask[cur - 1]) != mask[cur - 1])continue;
        int inc = bitcount[s] == 1 ? dis : 0;
        if((s & (1 << t)) == 0)
          dp[cur % 2][s] = max(dp[cur % 2][s] , dp[(cur - 1) % 2][s] + inc);
        else
          dp[cur % 2][s ^ (1 << t)] = max(dp[cur % 2][s ^ (1 << t)] , dp[(cur - 1) % 2][s] + inc);
      }
    }
    ++cur;
  }
  int ans = 0;
  for(int s = 0; s < (1 << K); ++s){
    if((s | mask[2 * N]) != mask[2 * N])continue;
    ans = max(ans , dp[(cur - 1) % 2][s]);
  }
  cout << ans << endl;
}
