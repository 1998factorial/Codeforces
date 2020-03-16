#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl
using namespace std;
typedef long long ll;
typedef pair<int , int> ii;

const ll mod = 998244353;
const int maxn = 2e5 + 10;

int N , M;

int main(){
  int t; cin >> t;
  while(t--){
    cin >> N >> M;
    if(N % M == 0)cout << "YES" << endl;
    else cout << "NO" << endl;
  }
}
