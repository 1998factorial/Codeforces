#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl
using namespace std;
typedef long long ll;
typedef pair<int , int> ii;

int N;
int a[105];


void solve(){
  cin >> N;
  int ret = 0;
  for(int i = 1; i <= N; ++i)cin >> a[i];
  for(int i = 2; i < N; ++i){
    if(a[i - 1] < a[i] && a[i] > a[i + 1])++ret;
  }
  cout << ret << endl;
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int T; cin >> T;
  for(int t = 1; t <= T; ++t){
    cout << "Case #" << t << ": ";
    solve();
  }
}
