#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdio>
#include <vector>
using namespace std;
const int maxn = 105;
int n,M;
int t[maxn];

int main(){
  cin >> n >> M;
  for(int i = 1; i <= n; ++i)
    cin >> t[i];
  vector<int> a;
  int sum = 0;
  vector<int> ret;
  for(int i = 1; i <= n; ++i){
    sum += t[i];
    sort(a.begin(),a.end());
    if(sum > M){
      int m = a.size();
      int j = m - 1;
      int cnt = 0;
      int acc = 0;
      while(j >= 0 && sum - acc > M){
        acc += a[j];
        ++cnt;
        --j;
      }
      ret.push_back(cnt);
    }
    else{
      ret.push_back(0);
    }
    a.push_back(t[i]);
  }
  for(int i = 0; i < n; ++i)
    cout << ret[i] << " ";
  cout << endl;
}
