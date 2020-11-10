#include <iostream>
#include <map>
using namespace std;

int main(){
  int Q;
  cin >> Q;
  for(int q = 1; q <= Q; ++q){
    int n;
    cin >> n;
    map<int , int> cnt;
    bool yes = false;
    for(int i = 1; i <= n; ++i){
      int x;
      cin >> x;
      if(x == 2048){
        yes = true;
      }
      ++cnt[x];
    }
    for(auto& it : cnt){
      if(it.first == 2048 && it.second > 0){
        yes = true;
        break;
      }
      cnt[it.first * 2] += it.second / 2;
    }
    if(yes){
      cout << "YES\n";
    }
    else{
      cout << "NO\n";
    }
  }
  return 0;
}
