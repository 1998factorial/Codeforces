#include <iostream>
#include <algorithm>
#include <string.h>
using namespace std;
typedef long long ll;

const int maxn = 1e5 + 10;
int N , M , Q;
bool mark[maxn];
ll cnt[maxn];

// O(N * logN)
void preprocess(){
  memset(cnt , 0 , sizeof(cnt));
  for(int i = 1; i <= N; ++i){
    for(int j = i; j <= N; j += i){
      cnt[i] += mark[j];
    }
  }
}

ll solve(){
  cin >> N >> M >> Q;
  memset(mark , false , sizeof(mark));
  for(int i = 1; i <= M; ++i){
    int x; cin >> x;
    mark[x] = true;
  }
  preprocess();
  ll ret = 0;
  for(int q = 1; q <= Q; ++q){
    ll x; cin >> x;
    ret += (ll)N / x - cnt[x];
  }
  return ret;
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int T;
  cin >> T;
  for(int t = 1; t <= T; ++t){
    cout << "Case #" << t << ": " << solve() << endl;
  }
  return 0;
}
