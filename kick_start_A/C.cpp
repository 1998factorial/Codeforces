#include <iostream>
#include <algorithm>
#include <string.h>
using namespace std;

const int maxn = 1e6 + 10;
int N , Q;

struct Node{
  int sum , lazy;
}tree[maxn << 2];

int solve(){
  int ret = N;
  memset(tree , 0 , sizeof(tree));
  tree[1].lazy = 1;
  for(int q = 1; q <= Q; ++q){
    int l , r;
    cin >> l >> r;
    ret = min(ret , query());
  }
  return ret;
}


int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int T;
  cin >> T;
  for(int t = 1; t <= T; ++t){
    cin >> N >> Q;

    cout << "Case #" << t << ": " << solve() << endl;
  }
}
return 0;
