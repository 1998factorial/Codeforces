#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl
using namespace std;
typedef long long ll;
typedef pair<int , int> ii;

ll skill[105][105];
int R , C , T;
int can[105][105]; // 0 not ban , 1 more round , 2 more round , 3 more round
int dir[4][2] = {{1 , 0} , {-1 , 0} , {0 , 1} ,{0 , -1}};

void solve(){
  cin >> R >> C;
  for(int i = 1; i <= R; ++i){
    for(int j = 1; j <= C; ++j){
      cin >> skill[i][j];
    }
  }
  ll ret = 0;
  memset(can , 0 , sizeof(can));
  int change = 1;
  while(change){
    ll level = 0;
    change = 0;
    vector<ii> era;
    for(int i = 1; i <= R; ++i){
      for(int j = 1; j <= C; ++j){
        if(can[i][j] == 0){
          level += skill[i][j];
          // compute avg
          int tot = 0;
          ll sum = 0;
          for(int x = 1; i - x >= 1; ++x){
            if(can[i - x][j] == 0){
              ++tot;
              sum += skill[i - x][j];
              break;
            }
          }
          for(int x = 1; i + x <= R; ++x){
            if(can[i + x][j] == 0){
              ++tot;
              sum += skill[i + x][j];
              break;
            }
          }
          for(int x = 1; j - x >= 1; ++x){
            if(can[i][j - x] == 0){
              ++tot;
              sum += skill[i][j - x];
              break;
            }
          }
          for(int x = 1; j + x <= C; ++x){
            if(can[i][j + x] == 0){
              ++tot;
              sum += skill[i][j + x];
              break;
            }
          }
          if(tot * skill[i][j] < sum){
            change = 1;
            era.emplace_back(i , j);
          }
        }
      }
    }
    for(auto& e : era)can[e.first][e.second] = 3;// , cout << e.first << " " << e.second << endl;
    ret += level;
  }
  cout << ret << endl;
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> T;
  for(int t = 1; t <= T; ++t){
    cout << "Case #" << t << ": ";
    solve();
  }
}
