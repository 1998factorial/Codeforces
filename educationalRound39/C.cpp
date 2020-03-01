#include <bits/stdc++.h>
using namespace std;

string s;
int N;

bool solve(){
  if(N < 26)return 0;
  int cur = 0;
  for(int i = 0; i < N && cur < 26; ++i){
    int v = s[i] - 'a';
    if(v <= cur)s[i] = 'a' + cur , ++cur;
  }
  return cur >= 26;
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> s;
  N = s.size();
  if(solve())cout << s << endl;
  else cout << -1 << endl;
}
