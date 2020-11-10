#include <iostream>
#include <algorithm>
using namespace std;
const int maxn = 3e5 + 10;
typedef long long ll;
ll N , a[maxn];

int main(){
  cin >> N; for(int i = 1; i <= N; ++i)cin >> a[i];
  ll black = 0 , white = 0;
  for(int i = 1; i <= N; ++i){
    ll b , w;
    if(i & 1){
      b = a[i] / 2;
      w = a[i] - b;
    }
    else{
      w = a[i] / 2;
      b = a[i] - w;
    }
    black += b;
    white += w;
  }
  cout << min(black , white) << endl;
}
