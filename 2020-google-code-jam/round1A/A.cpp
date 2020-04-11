#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl
using namespace std;
typedef long long ll;
typedef pair<int , int> ii;

/*

  split each string into [] * [] * []
  99 * 2 + 98 * 50 <= 10 ^ 4

*/

int N , T;
string P[105];
int pos[105];
vector<string> S[105];

bool check_left(string& a , string& b){
  // check if a[0..b.size() - 1] == b
  int len = b.size();
  return a.substr(0 , len) == b;
}

bool check_right(string& a , string& b){
  // check if a[a.size() - b.size() .. a.size()] == b
  int len = b.size();
  return a.substr(a.size() - len , len) == b;
}

void solve(){
  vector<string> left , right , mid;
  for(int i = 1; i <= N; ++i){
    string l = "" , r = "";
    int j = 0;
    for(; j < P[i].size() && P[i][j] != '*'; ++j){
      l += P[i][j];
    }
    int k = P[i].size() - 1;
    for(; k >= j && P[i][k] != '*'; --k){
      r += P[i][k];
    }
    reverse(r.begin() , r.end());
    if(l != "")left.push_back(l);
    if(r != "")right.push_back(r);
    string tmp = "";
    string m = "";
    for(; j <= k; ++j){
      if(P[i][j] != '*')m += P[i][j];
    }
    if(m != "")mid.push_back(m);
  }
  sort(left.begin() , left.end() , [&](string& a , string& b){
    return a.size() > b.size();
  });
  sort(right.begin() , right.end() , [&](string& a , string& b){
    return a.size() > b.size();
  });
  if(left.size()){
    for(int i = 1; i < left.size(); ++i){
      if(!check_left(left[0] , left[i])){
        cout << "*" << endl;
        return ;
      }
    }
  }
  if(right.size()){
    for(int i = 1; i < right.size(); ++i){
      if(!check_right(right[0] , right[i])){
        cout << "*" << endl;
        return ;
      }
    }
  }
  string ret = "";
  if(left.size())ret += left[0];
  for(string& e : mid)ret += e;
  if(right.size())ret += right[0];
  cout << ret << endl;
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> T;
  for(int t = 1; t <= T; ++t){
    cin >> N;
    for(int i = 1; i <= N; ++i)cin >> P[i];
    cout << "Case #" << t << ": ";
    solve();
  }
}
