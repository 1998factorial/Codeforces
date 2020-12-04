#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl
using namespace std;
typedef long long ll;
typedef pair<int , int> ii;

int T , N , K;
const int maxn = 1e5 + 10;
int MAX[maxn][25][2];
int A[maxn] , B[maxn];
int logs[maxn];

void build(){
  for(int i = 2; i <= N; ++i)
    logs[i] = logs[i / 2] + 1;
  for(int i = 1; i <= N; ++i){
    MAX[i][0][0] = A[i];
    MAX[i][0][1] = B[i];
  }
  for(int j = 1; j <= logs[N] + 1; ++j){
    for(int i = 1; i <= N; ++i){
      int len = (1 << (j - 1));
      if(i + len <= N){
        MAX[i][j][0] = max(MAX[i][j - 1][0] , MAX[i + len][j - 1][0]);
        MAX[i][j][1] = max(MAX[i][j - 1][1] , MAX[i + len][j - 1][1]);
      }
      else{
        MAX[i][j][0] = MAX[i][j - 1][0];
        MAX[i][j][1] = MAX[i][j - 1][1];
      }
    }
  }
}

int query(int l , int r , int which){
    int len = r - l + 1;
    return max(MAX[l][logs[len]][which] , MAX[r - (1 << logs[len]) + 1][logs[len]][which]);
}

void solve(){
  build();
  ll ret = 0;
  for(int i = 1; i <= N; ++i){
    for(int j = i; j >= 1; --j){
      if(abs(query(j , i , 0) - query(j , i , 1)) <= K){
        ++ret;
      }
    }
  }
  cout << ret << endl;
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> T;
  for(int t = 1; t <= T; ++t){
    cin >> N >> K;
    for(int i = 1; i <= N; ++i){
      cin >> A[i];
    }
    for(int i = 1; i <= N; ++i){
      cin >> B[i];
    }
    cout << "Case #" << t << ": ";
    solve();
  }
}
