#include <bits/stdc++.h>
using namespace std;

const int maxn = 2e5 + 10;
bool DP[maxn][305][2];
int C[305];
string s;
int K;

i , j , 0 -> pos = i , C[j]'s  right end
i , j , 1 -> pos = i , is white

DP[i][j][0] = 1 iff at s[i] , C[j] on it
DP[i][j][1] = 1 iff at s[i] , s[i] is white and we have used j C's

DP[i][j][0] -> DP[i + C[i] - 1][j + 1][0]


int main(){
  cin >> s;
  cin >> K;
  for(int i = 1; i <= K; ++i){
    cin >> C[i];
  }


  for(int i = 0; i < s.size(); ++i){
    if(s[i] == '.'){
      bool white = 0 , black = 0;
      for(){

      }
    }
  }

  cout << s << endl;
}
