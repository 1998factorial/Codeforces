#include <iostream>
#include <unordered_map>
#include <algorithm>
using namespace std;

const int maxn = 1e3 + 10;
int A[maxn];
int N , S;
int solve(){
  int ret = 0;
  for(int i = 1; i <= N; ++i){
    for(int j = i; j <= N; ++j){
      unordered_map<int , int> cnt;
      int ans = 0;
      for(int k = i; k <= j; ++k){
        cnt[A[k]]++;
      }
      for(auto& it : cnt){
        if(it.second <= S)ans += it.second;
      }
      ret = max(ret , ans);
    }
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
    for(int i = 1; i <= N; ++i){
      cin >> A[i];
    }
    cout << "Case #" << t << ": " << solve() << endl;
  }
  return 0;
}
