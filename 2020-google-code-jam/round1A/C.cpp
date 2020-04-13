#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl
using namespace std;
typedef long long ll;
typedef pair<int , int> ii;

int R , C , T;

vector<vector<int>> s , u , d , l , r , vis;
set<ii> q;


bool check(int i , int j){
  //printf("checking %d %d\n" , i , j);
  ll cnt = 0 , sum = 0;
  if(~u[i][j]){
    ++cnt;
    sum += s[u[i][j]][j];
    //printf("%d %d\n" , u[i][j] , j);
  }
  if(~d[i][j]){
    ++cnt;
    sum += s[d[i][j]][j];
    //printf("%d %d\n" , d[i][j] , j);
  }
  if(~l[i][j]){
    ++cnt;
    sum += s[i][l[i][j]];
    //printf("%d %d\n" , i , l[i][j]);
  }
  if(~r[i][j]){
    ++cnt;
    sum += s[i][r[i][j]];
    //printf("%d %d\n" , i , r[i][j]);
  }
  return s[i][j] * cnt >= sum;
}


void del(int i , int j){
  if(check(i , j)){
    q.erase(make_pair(i , j));
  }
  else{
    q.insert(make_pair(i , j));
  }
}


void solve(){
  cin >> R >> C;
  s = u = d = l = r = vis = vector<vector<int>> (R , vector<int>(C , 0));
  ll sum = 0;
  for(int i = 0; i < R; ++i){
    for(int j = 0; j < C; ++j){
      cin >> s[i][j];
      sum += s[i][j];
      u[i][j] = i - 1 >= 0 ? i - 1 : -1;
      d[i][j] = i + 1 < R ? i + 1 : -1;
      l[i][j] = j - 1 >= 0 ? j - 1 : -1;
      r[i][j] = j + 1 < C ? j + 1 : -1;
    }
  }
  for(int i = 0; i < R; ++i){
    for(int j = 0; j < C; ++j){
      if(!check(i , j)){
        del(i , j);
      }
    }
  }
  int change = 1;
  ll ans = 0;
  while(change){
    //DEBUG(sum);
    change = 0;
    ans += sum;
    set<ii> q2 = q;
    for(auto& it : q2){
      change = 1;
      int i = it.first , j = it.second;
      sum -= s[i][j];
      if(~u[i][j]){
        d[u[i][j]][j] = d[i][j];
        del(u[i][j] , j);
      }
      if(~d[i][j]){
        u[d[i][j]][j] = u[i][j];
        del(d[i][j] , j);
      }
      if(~l[i][j]){
        r[i][l[i][j]] = r[i][j];
        del(i , l[i][j]);
      }
      if(~r[i][j]){
        l[i][r[i][j]] = l[i][j];
        del(i , r[i][j]);
      }
      q.erase(make_pair(i , j));
    }
  }
  cout << ans << endl;
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
