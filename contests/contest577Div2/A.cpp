#include <iostream>
#include <cstring>
#include <algorithm>
#include <cstdio>
#include <vector>
using namespace std;
int n,m;
const int maxn = 1005;
string s[maxn];
int a[maxn];
int main(){
  cin >> n >> m;
  for(int i = 0; i < n; ++i)
    cin >> s[i];
  for(int i = 0; i < m; ++i)
    cin >> a[i];
  int ret = 0;
  for(int i = 0; i < m; ++i){
    vector<int> cnt(5);
    for(int j = 0; j < n; ++j){
      ++cnt[s[j][i] - 'A'];
    }
    int cc = 0;
    for(int i = 0; i < 5; ++i)cc = max(cc , cnt[i]);
    ret += cc * a[i];
  }
  cout << ret << endl;
}
