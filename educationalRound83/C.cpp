#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl
using namespace std;
typedef long long ll;
typedef pair<int , int> ii;

ll a[50];
int N , K;
bool vis[100];

bool solve(){
  memset(vis , 0 , sizeof(vis));
  for(int i = 1; i <= N; ++i){
    ll n = a[i];
    int power = 0;
    while(n){
      ll t = n % K;
      if(t == 1){
        if(vis[power])return 0;
        vis[power] = 1;
      }
      if(t > 1){
        return 0;
      }
      n /= K;
      ++power;
    }
  }
  return 1;
}

int main(){
  int t; cin >> t;
  while(t--){
    cin >> N >> K;
    for(int i = 1; i <= N; ++i)cin >> a[i];
    if(solve())cout << "YES" << endl;
    else cout << "NO" << endl;
  }
}
