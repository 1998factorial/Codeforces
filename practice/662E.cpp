#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl
using namespace std;
typedef long long ll;
typedef pair<int , int> ii;

/*
  each problem has a maximal score of 3000
  each hack earns 100 score
  so in order to come first, we just need to get 9000 points, which, 90 hacks can gurantee the win
  otherwise, we can hack at most 89 ppl
  we can fix the maximal scores for each of 3 questions once this is done, we can easily find for each
  question, how many hacks we can have for each of question at most. So, our score can also be determined
  by this. Then , we just need to hack those who got higher score than us
  let DP[i][a][b][c] = maximal number of ppl we can beat among the first i ppl, with a hacks on q1 , b hacks
  on q2 and c hacks on q3.
  ans = # ppl higher than us - DP[i][hack 1][hack 2][hack 3]
*/

const int maxn = 5e3 + 10;
int N;
int t[maxn][3];
int solved[3];
int canhack[3];
int willhack[3];
int maximal[3];
int DP[2][90][90][90];

int get_score(int i , int j){
  if(t[i][j] == 0)return 0;
  return maximal[j] * (250 - abs(t[i][j])) / 250;
}

int get_3_score(int i){
  int ret = 0;
  for(int j = 0; j < 3; ++j)ret += get_score(i , j);
  return ret;
}

int count_hack(int i){
  int ret = 0;
  for(int j = 0; j < 3; ++j)ret += t[i][j] < 0;
  return ret;
}

int solve(){
  memset(DP , 0 , sizeof(DP));
  int my_score = 0;
  for(int i = 0; i < 3; ++i)my_score += get_score(1 , i) + 100 * willhack[i];
  for(int i = 2; i <= N; ++i){
    for(int x = 0; x <= willhack[0]; ++x){
      for(int y = 0; y <= willhack[1]; ++y){
        for(int z = 0; z <= willhack[2]; ++z){
          DP[i % 2][x][y][z] = DP[(i - 1) % 2][x][y][z];
        }
      }
    }
    if(my_score >= get_3_score(i))continue; // no need to hack ppl whose mark is less than mine
    if(count_hack(i) == 0)continue; // can not hack
    for(int a = 0; a < 2; ++a){
      for(int b = 0; b < 2; ++b){
        for(int c = 0; c < 2; ++c){
          if(a && t[i][0] >= 0)continue;
          if(b && t[i][1] >= 0)continue;
          if(c && t[i][2] >= 0)continue;
          int score = get_3_score(i);
          score -= get_score(i , 0) * a;
          score -= get_score(i , 1) * b;
          score -= get_score(i , 2) * c;
          if(score > my_score)continue; // no need to hack
          // we can hack this person
          for(int x = 0; x <= willhack[0]; ++x){
            for(int y = 0; y <= willhack[1]; ++y){
              for(int z = 0; z <= willhack[2]; ++z){
                if(x + a > willhack[0])continue;
                if(y + b > willhack[1])continue;
                if(z + c > willhack[2])continue;
                DP[i % 2][x + a][y + b][z + c] = max(
                  DP[i % 2][x + a][y + b][z + c] ,
                  DP[(i - 1) % 2][x][y][z] + 1
                );
              }
            }
          }
        }
      }
    }
  }
  int ret = DP[N % 2][willhack[0]][willhack[1]][willhack[2]];
  int tot = 0;
  for(int i = 1; i <= N; ++i)
    if(get_3_score(i) > my_score)++tot;
  ret = 1 + tot - ret;
  return ret;
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> N;
  for(int i = 1; i <= N; ++i){
    for(int j = 0; j < 3; ++j){
      cin >> t[i][j];
      solved[j] += t[i][j] != 0;
      if(i != 1)canhack[j] += t[i][j] < 0;
    }
  }
  if(canhack[0] + canhack[1] + canhack[2] >= 90){
    cout << 1 << endl;
  }
  else{
    int ret = N;
    for(int s1 = 1; s1 <= 6; ++s1){
      if(s1 < 6 && ((1 << s1) * (solved[0] - canhack[0]) > 2 * N || (1 << s1) * solved[0] <= N))continue;
      if(s1 == 6 && 32 * (solved[0] - canhack[0]) > N)continue;
      // get maximal # hacks we can do not excceeding 90 on question 1
      if(s1 < 6){
        willhack[0] = min(canhack[0] , solved[0] - (N >> s1) - 1);
      }
      else{
        willhack[0] = min(canhack[0] , solved[0]);
      }
      for(int s2 = 1; s2 <= 6; ++s2){
        if(s2 < 6 && ((1 << s2) * (solved[1] - canhack[1]) > 2 * N || (1 << s2) * solved[1] <= N))continue;
        if(s2 == 6 && 32 * (solved[1] - canhack[1]) > N)continue;
        if(s2 < 6){
          willhack[1] = min(canhack[1] , solved[1] - (N >> s2) - 1);
        }
        else{
          willhack[1] = min(canhack[1] , solved[1]);
        }
        for(int s3 = 1; s3 <= 6; ++s3){
          if(s3 < 6 && ((1 << s3) * (solved[2] - canhack[2]) > 2 * N || (1 << s3) * solved[2] <= N))continue;
          if(s3 == 6 && 32 * (solved[2] - canhack[2]) > N)continue;
          maximal[0] = 500 * s1;
          maximal[1] = 500 * s2;
          maximal[2] = 500 * s3;
          if(s3 < 6){
            willhack[2] = min(canhack[2] , solved[2] - (N >> s3) - 1);
          }
          else{
            willhack[2] = min(canhack[2] , solved[2]);
          }
          int ans = solve();
          ret = min(ret , ans);
        }
      }
    }
    cout << ret << endl;
  }
}
