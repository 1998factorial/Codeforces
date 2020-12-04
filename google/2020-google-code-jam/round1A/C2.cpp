#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl
using namespace std;
typedef long long ll;
typedef pair<int , int> ii;

int R , C , T;

vector<vector<int>> s , u , d , l , r;
set<ii> era;


bool bad(int i , int j){
  ll n = 0 , sum = 0;
  if(~u[i][j]){
    ++n;
    sum += s[u[i][j]][j];
  }
  if(~d[i][j]){
    ++n;
    sum += s[d[i][j]][j];
  }
  if(~l[i][j]){
    ++n;
    sum += s[i][l[i][j]];
  }
  if(~r[i][j]){
    ++n;
    sum += s[i][r[i][j]];
  }
  return s[i][j] * n < sum;
}

void check(int i , int j){
  if(bad(i , j))
    era.insert(make_pair(i , j));
  else
    era.erase(make_pair(i , j));
}

void solve(){
  era.clear();
  cin >> R >> C;
  s = u = d = l = r = vector<vector<int>> (R , vector<int> (C , 0));
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
      check(i , j);
    }
  }
  bool change = 1;
  ll ans = 0;
  while(change){
    change = 0;
    ans += sum;
    //cout << "sum = " << sum << endl;
    set<ii> era2 = era;
    era = {};
    for(auto& e : era2){
      change = 1;
      int i = e.first , j = e.second;
      //printf("removing %d %d\n" , i , j );
      sum -= s[i][j];
      if(~u[i][j]){
        d[u[i][j]][j] = d[i][j];
        check(u[i][j] , j);
      }
      if(~d[i][j]){
        u[d[i][j]][j] = u[i][j];
        check(d[i][j] , j);
      }
      if(~l[i][j]){
        r[i][l[i][j]] = r[i][j];
        check(i , l[i][j]);
      }
      if(~r[i][j]){
        l[i][r[i][j]] = l[i][j];
        check(i , r[i][j]);
      }
      era.erase(make_pair(i , j));
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
