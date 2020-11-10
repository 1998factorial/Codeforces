#include <bits/stdc++.h>
using namespace std;

int N;
string s;

bool check(string& a , string& b){
  for(int i = 0; i < a.size(); ++i){
    if(a[i] != b[i])return 0;
  }
  return 1;
}

int main(){
  cin >> N;
  cin >> s;
  int ret = 1;
  string t = "";
  t += s[0];
  // add one at the end or copy and paste?
  int i = 1;
  while(i < N){
    if(2 * t.size() <= N){
      string tmp = t + t;
      if(check(tmp , s)){
        i += t.size();
        t += t;
      }
      else{
        t += s[i];
        ++i;
      }
    }
    else{
      t += s[i];
      ++i;
    }
    ++ret;
  }
  cout << ret << endl;
}
