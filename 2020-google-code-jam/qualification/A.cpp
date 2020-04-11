#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl
using namespace std;
typedef long long ll;
typedef pair<int , int> ii;

int T , N , a[105][105];

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> T;
  for(int t = 1; t <= T; ++t){
    cin >> N;
    for(int i = 1; i <= N; ++i)
      for(int j = 1; j <= N; ++j)
        cin >> a[i][j];
    int x = 0;
    for(int i = 1; i <= N; ++i)x += a[i][i];
    int r = 0 , c = 0;
    for(int i = 1; i <= N; ++i){
      unordered_set<int> cols , rows;
      for(int j = 1; j <= N; ++j){
        cols.insert(a[j][i]);
        rows.insert(a[i][j]);
      }
      if(cols.size() != N)++c;
      if(rows.size() != N)++r;
    }
    cout << "Case #" << t << ": " << x << " " << r << " " << c << endl;
  }
}
