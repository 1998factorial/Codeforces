#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <cmath>
using namespace std;
typedef long long ll;
typedef pair<int , int > ii;

const int maxn = 3e5 + 10;
int N;
ll a[maxn];

int count(int s){
  int ret = 0;
  for(int i = 0; i < N; ++i){
    if((1 << i) & s) ++ret;
  }
  return ret;
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> N;
  ll sum = 0;
  for(int i = 0; i < N; ++i){
    cin >> a[i];
    sum += a[i];
  }
  ll ret = 0;
  ll xx = 0;
  vector<int> b;
  for(int i = 0; i < (1 << N); ++i){
    if(abs(count(i) * 2 - N ) > 1){
      continue;
    }
    ll x = 0;
    vector<int> c;
    for(int j = 0; j < N; ++j){
      if((1 << j) & i)x += a[j] , c.push_back(a[j]);
    }
    if(ret < x * x + (sum - x) * (sum - x)){
      ret  = x * x + (sum - x) * (sum - x);
      b = c;
      xx = x;
    }
  }
  //for(int i : b)cout << i << " ";
  //cout << endl;
  cout << xx << " " << sum - xx << endl;
  cout << ret << endl;
  return 0;
}
