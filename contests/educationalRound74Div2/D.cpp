#include <iostream>
#include <cstring>
using namespace std;

typedef long long ll;
ll N;
string a;
ll dp[300005];

/*
instead of counting what we want , we count what we dont want
use long long for N!
*/

int main(){
  cin >> N;
  cin >> a;
  ll ret = N * (N - 1) / 2; // all possible good sequences
  dp[0] = 0;
  dp[1] = 1;
  for(int i = 2; i <= N; ++i){
    if(a[i - 1] != a[i - 2])dp[i] = 1;
    else dp[i] = dp[i - 1] + 1;
  }
  for(int i = 2; i <= N; ++i){ // subtract the bad strings end with a[i - 1]
    if(dp[i] > 1){
      if(i - dp[i] > 0)
        --ret;
    }
    else{
      ret -= dp[i - 1];
    }
  }
  cout << ret << endl;
  return 0;
}
