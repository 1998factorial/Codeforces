#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;

const int maxn = 1e5 + 10;
int N , M;
vector<int> g[maxn];
ll out[maxn] , in[maxn];

int main(){
  cin >> N >> M;
  for(int i = 1; i <= N; ++i){
    g[i].clear();
    out[i] = in[i] = 0;
  }
  for(int i = 1; i <= M; ++i){
    int a , b;
    cin >> a >> b;
    int x = max(a , b) , y = min(a , b);
    g[y].push_back(x); // x brags to y
    ++out[x];
    ++in[y];
  }
  ll ret = 0;
  for(int i = 1; i <= N; ++i){
    ret += out[i] * in[i];
  }
  int Q;
  cin >> Q;
  cout << ret << endl;
  for(int q = 1; q <= Q; ++q){
    int x;
    cin >> x;
    ret -= out[x] * in[x];
    for(int i : g[x]){
      ret -= out[i] * in[i];
      --out[i];
      ++in[i];
      g[i].push_back(x);
      ret += out[i] * in[i];
      ++out[x];
      --in[x];
    }
    ret += out[x] * in[x];
    g[x].clear();
    cout << ret << endl;
  }
  return 0;
}
