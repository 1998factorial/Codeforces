#include <iostream>
#include <cstring>
#include <vector>
using namespace std;
typedef long long ll;

const ll mod = 1e9 + 7;
string str;
int x;

ll solve(){
  ll ret = str.size();
  vector<char> s;
  for(int i = 0; i < ret; ++i){
    s.push_back(str[i]);
  }
  for(int i = 1; i <= x; ++i){
    int cnt = s[i - 1] - '1';
    if(s.size() < x){
      vector<char> sub(s.begin() + i , s.end());
      for(int j = 0; j < cnt; ++j)s.insert(s.end() , sub.begin() , sub.end());
    }
    ret = (ret + (ret - i) * cnt) % mod;
  }
  return ret;
}

int main(){
  int T; cin >> T;
  for(int t = 1; t <= T; ++t){
    cin >> x;
    cin >> str;
    cout << (solve() + mod) % mod << endl;
  }
}
