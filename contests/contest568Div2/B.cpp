#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdio>
#include <vector>
using namespace std;

int N;
string a,b;

bool solve(){
  int n = a.size();
  int m = b.size();
  if(n > m)return false;
  int i = 0, j = 0;
  while(i < n && j < m){
    int i_ = i;
    int j_ = j;
    if(a[i] != b[j])return false;
    while(i_ < n && a[i_] == a[i])++i_;
    while(j_ < m && b[j_] == b[j])++j_;
    if(i_ - i > j_ - j)return false;
    i = i_;
    j = j_;
  }
  return i == n && j == m;
}

int main(){
  cin >> N;
  for(int i = 1; i <= N; ++i){
    cin >> a;
    cin >> b;
    if(solve())cout << "YES\n";
    else cout << "NO\n";
  }
}
