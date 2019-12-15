#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
typedef long long ll;
typedef pair<ll , ll > ii;
const int maxn = 2e5 + 10;
vector<ii> g[maxn];
int N;
int deg[maxn];


int main(){
  int T;
  cin >> T;
  for(int t = 1 ; t <= T; ++t){
    cin >> N;
    for(int i = 1; i <= 2 * N; ++i){
      g[i].clear();
      deg[i] = 0;
    }
    for(int i = 1; i <= 2 * N - 1; ++i){
      ll x , y , z;
      cin >> x >> y >> z;
      deg[x]++; deg[y]++;
      g[x].emplace_back(y , z);
      g[y].emplace_back(x , z);
    }
  }
}
