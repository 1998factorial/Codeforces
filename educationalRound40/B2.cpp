#include <bits/stdc++.h>
using namespace std;

/*
  I missed read the problem statement
  I thought we can copy and paste countless many times
  and I found N is small , so I wrote a search ...
  turns out I only need to find the maximal i such that
  s[0 ... i] = s[i + 1 ... 2i + 1]
*/


int N;
string s;

bool check(string& p){
  int n = p.size();
  if(n > N)return 0;
  for(int i = 0; i < n; ++i){
    if(p[i] != s[i])return 0;
  }
  return 1;
}

int solve(string& a , int pos , bool used){
  if(pos == N)return 0;
  int n = a.size();
  int ret = 1e9;
  if(n * 2 <= N && !used){
    string tmp = a + a;
    if(check(tmp)){
      ret = min(ret , 1 + solve(tmp , pos + n , 1 - used));
    }
  }
  a += s[pos];
  ret = min(ret , 1 + solve(a , pos + 1 , used));
  return ret;
}

int main(){
  cin >> N;
  cin >> s;
  string t = "";
  t += s[0];
  cout << 1 + solve(t , 1 , 0) << endl;
}
