#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl
using namespace std;
typedef long long ll;
typedef pair<int , int> ii;

string s;

void solve(){
  if(s.size() == 1){
    cout << "YES" << endl;
    cout << "bacdefghijklmnopqrstuvwxyz" << endl;
    return;
  }
  set<int> g[26];
  for(int i = 0; i < s.size() - 1; ++i){
    int x = s[i] - 'a';
    int y = s[i + 1] - 'a';
    g[x].insert(y);
    g[y].insert(x);
  }
  vector<int> ends;
  int tot = 0;
  for(int i = 0; i < 26; ++i){
    if(g[i].size() > 2){
      cout << "NO" << endl;
      return;
    }
    if(g[i].size() == 1){
      ends.push_back(i);
    }
    if(g[i].size())++tot;
  }
  if(ends.size() != 2){
    cout << "NO" << endl;
    return;
  }
  vector<bool> vis(26);
  int s = ends[0];
  vector<char> ret;
  for(int i = 1; i <= tot; ++i){
    vis[s] = 1;
    ret.push_back('a' + s);
    for(int j : g[s]){
      if(!vis[j]){
        s = j;
        break;
      }
    }
  }
  if(s != ends[1]){
    cout << "NO" << endl;
    return;
  }
  for(int i = 0; i < 26; ++i){
    if(!vis[i])ret.push_back('a' + i);
  }
  cout << "YES" << endl;
  for(char i : ret)cout << i;
  cout << endl;
}

int main(){
  int T; cin >> T;
  while(T--){
    cin >> s;
    solve();
  }
}
