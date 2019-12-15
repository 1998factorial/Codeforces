#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
typedef long long ll;

const int maxn = 1e6 + 10;
ll N , K , a[maxn];

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> N >> K;
  ll sum = 0;
  for(int i = 1; i <= N; ++i)cin >> a[i] , sum += a[i];
  if(sum > K)cout << -1 << endl;
  else{
    
  }
}
