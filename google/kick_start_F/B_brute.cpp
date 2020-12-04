#include <iostream>
using namespace std;

const int maxn = 5e4 + 10;
int N , S;
int C[maxn];
int skills[maxn][5];


int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int T;
  cin >> T;
  for(int t = 1; t <= T; ++t){
    cin >> N >> S;
    for(int i = 1; i <= N; ++i){
      cin >> C[i];
      for(int j = 0; j < C[i]; ++j){
        cin >> skills[i][j];
      }
    }
    int ans = 0;
    for(int i = 1; i <= N; ++i){
      for(int j = 1; j <= N; ++j){
        if(i == j)continue;
        bool check = false;
        for(int x = 0; x < C[i]; ++x){
          bool f = false;
          for(int y = 0; y < C[j]; ++y){
            if(skills[i][x] == skills[j][y])f = true;
          }
          if(!f)check = true;
        }
        ans += check;
      }
    }
    cout << "Case #" << t << ": " << ans << endl;
  }

}
