#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl
using namespace std;
typedef long long ll;
typedef pair<int , int> ii;

const int maxn = 1e5 + 10;
int N , P;
char S[maxn];
int matrix[17][17];
bitset<(1 << 17)> good , cur , dp;
vector<int> pos[17];
int cnt[maxn][17];
int num[17];
int full;

void print_state(int s){
  for(int i = 0; i < P; ++i){
    if(s & (1 << i))cout << 1;
    else cout << 0;
  }
  cout << endl;
}

int main(){
  scanf("%d %d" , &N , &P);
  scanf("%s" , S + 1);
  for(int i = 0; i < P; ++i){
    for(int j = 0; j < P; ++j){
      scanf("%d" , &matrix[i][j]);
    }
  }
  for(int i = 1; i <= N; ++i){
    int x = S[i] - 'a';
    pos[x].push_back(i);
    ++num[x];
    for(int j = 0; j < P; ++j){
      cnt[i][j] = cnt[i - 1][j] + (j == x);
    }
  }
  full = (1 << P) - 1;
  good.reset();
  good.flip(); //initialise all states to be good
  for(int a = 0; a < P; ++a){
    for(int b = a; b < P; ++b){
      if(matrix[a][b])continue;
      cur.reset();
      cur.flip();
      int i = 0 , j = 0;
      while(i < pos[a].size() && j < pos[b].size()){
        int mask = 0;
        int x = pos[a][i];
        int y = pos[b][j];
        if(x < y){
          for(int e = 0; e < P; ++e)
            if(cnt[y - 1][e] - cnt[x][e] != 0)
              mask |= (1 << e);
          ++i;
        }
        else{
          for(int e = 0; e < P; ++e)
            if(cnt[x - 1][e] - cnt[y][e] != 0)
              mask |= (1 << e);
          ++j;
        }
        if((mask & (1 << a)) || (mask & (1 << b)))continue; // can ignore when a / b in between
        cur[mask ^ full] = 0; // every S that contains a and b but not mask is banned
      }
      for(int state = full; state; --state){
        if(cur[state])continue;
        for(int x = 0; x < P; ++x) // appart from changing bits on a and b, any other value's bits can be changed to 0
          if(x != a && x != b && ((1 << x) & state))
            cur[state ^ (1 << x)] = 0;
      }
      good &= cur;
    }
  }
  //cout << "good states\n";
  /*for(int s = full; s >= 0; --s){
    if(good[s])print_state(s);
  }*/
  dp[full] = 1;
  for(int state = full; state >= 0; --state){
    if(dp[state] == 0)continue;
    for(int i = 0; i < P; ++i){
      if((1 << i) & state){
        int nstate = state ^ (1 << i);
        if(dp[nstate])continue;
        dp[nstate] = good[nstate];
      }
    }
  }
  //cout << "reachable DP states\n";
  int ans = N;
  for(int state = full; state >= 0; --state){
    if(dp[state]){
      //print_state(state);
      int len = 0;
      for(int i = 0; i < P; ++i){
        if((1 << i) & state)len += num[i];
      }
      ans = min(ans , len);
    }
  }
  printf("%d\n" , ans);
}
