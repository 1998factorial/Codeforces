#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl
using namespace std;
typedef long long ll;
typedef pair<int , int> ii;

int T , N;
string s;


string solve(){
  int cnt = 0;
  string ret = "";
  for(int i = 0; i < s.size(); ++i){
    int x = s[i] - '0';
    if(x > cnt){
      for(int j = 1; j <= x - cnt; ++j)ret += '(';
      cnt = x;
    }
    if(x < cnt){
      for(int j = 1; j <= cnt - x; ++j)ret += ')';
      cnt = x;
    }
    ret += s[i];
  }
  for(; cnt > 0; --cnt)ret += ')';
  return ret;
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> T;
  for(int t = 1; t <= T; ++t){
    cin >> s;
    cout << "Case #" << t << ": " << solve() << endl;
  }
}
