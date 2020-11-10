#include <iostream>
using namespace std;
typedef long long ll;
const ll mod = 1e9 + 7;
const int maxn = 1005;

ll R[maxn] , C[maxn] , f[maxn * maxn];
int H , W;

// find all "good" cells , ans = 2 ^ (# of good cells)

int main(){
  cin >> H >> W;
  for(int i = 1; i <= H; ++i)cin >> R[i];
  for(int i = 1; i <= W; ++i)cin >> C[i];
  f[0] = 1ll;
  for(int i = 1; i <= H * W; ++i){
    f[i] = f[i - 1] * 2ll % mod;
  }
  ll cnt = 0;
  for(int i = 1; i <= H; ++i){
    for(int j = 1; j <= W; ++j){
      if(R[i] + 1 < j && C[j] + 1 < i){
        ++cnt;
      }
      if(R[i] + 1 == j && C[j] >= i){
        cout << 0 << endl;
        return 0;
      }
      if(R[i] >= j && C[j] + 1 == i){
        cout << 0 << endl;
        return 0;
      }
    }
  }
  cout << (f[cnt] + mod) % mod << endl;
  return 0;
}
