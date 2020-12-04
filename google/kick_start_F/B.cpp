#include <iostream>
#include <algorithm>
#include <vector>
#include <unordered_map>
using namespace std;
typedef long long ll;

const int maxn = 5e4 + 10;
int N , S;
int C[maxn];
vector<int> skills[maxn];
ll base = 1001;

ll solve(){
  unordered_map<ll , ll> cnt;
  for(int i = 1; i <= N; ++i){
    ll val = 0;
    for(int j = 0; j < C[i]; ++j){
      val = val * base + skills[i][j];
    }
    ++cnt[val];
  }
  ll ret = 0;
  for(int i = 1; i <= N; ++i){
    ll sum = 0;
    for(int j = 0; j < (1 << C[i]); ++j){
      ll key = 0;
      for(int k = 0; k < C[i]; ++k){
        if(j & (1 << k)){
          key = key * base + skills[i][k];
        }
      }
      sum += cnt[key];
    }
    ret += N - sum;
  }
  return ret;
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int T;
  cin >> T;
  for(int t = 1; t <= T; ++t){
    cin >> N >> S;
    for(int i = 1; i <= N; ++i)skills[i].clear();
    for(int i = 1; i <= N; ++i){
      cin >> C[i];
      for(int j = 0; j < C[i]; ++j){
        int x; cin >> x;
        skills[i].push_back(x);
      }
      sort(skills[i].begin() , skills[i].end());
    }
    cout << "Case #" << t << ": " << solve() << endl;
  }
  return 0;
}
