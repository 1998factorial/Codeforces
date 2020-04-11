#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl
using namespace std;
typedef long long ll;
typedef pair<int , int> ii;

ll C[505][505];
const ll inf = 1e9 + 10;
int N;
ii pre[505][505];
bool vis[505][505];


void init(){
  C[1][1] = 1;
  for(int i = 2; i <= 501; ++i){
    for(int j = 1; j <= i; ++j){
      if(j == 1 || j == i)C[i][j] = 1;
      else{
        if(C[i - 1][j - 1] + C[i - 1][j] <= inf){
          C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
        }
        else{
          C[i][j] = inf;
        }
      }
    }
  }
}

void solve(){
  for(int i = 1; i <= N; ++i){
    for(int j = 1; j <= i; ++j){
      pre[i][j] = make_pair(-1 , -1);
    }
  }
  int row = 1;
  while((1ll << row) < N + 1){
    ++row;
  }
  if((1ll << row) == N + 1){
    
  }
  else{
    cout << row + 1 << endl;
  }
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int T;
  cin >> T;
  init();
  for(int t = 1; t <= T; ++t){
    cin >> N;
    cout << "Case #" << t << ": ";
    solve();
  }
}
