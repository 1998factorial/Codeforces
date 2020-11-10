#include <iostream>
#include <set>
#include <algorithm>
using namespace std;

int main(){
  int T; cin >> T;
  while(T--){
    int n , s , k; cin >> n >> s >> k;
    set<int> bad;
    for(int i = 1; i <= k; ++i){
      int x; cin >> x;
      bad.insert(x);
    }
    int down = 1e9 + 10 , up = 1e9 + 10;
    // go down
    int i = s;
    while(i >= 1){
      if(bad.count(i) == 0){
        down = s - i;
        break;
      }
      --i;
    }
    // go up
    i = s;
    while(i <= n){
      if(bad.count(i) == 0){
        up = i - s;
        break;
      }
      ++i;
    }
    cout << min(down , up) << endl;
  }
}
