#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>
using namespace std;

int l , r;
bool check(int n){
  if(n > r || n < l)return false;
  unordered_set<int> seen;
  while(n){
    if(seen.count(n % 10) > 0)return false;
    seen.insert(n % 10);
    n /= 10;
  }
  return true;
}

int main(){
  cin >> l >> r;
  for(int i = 0; i <= 9; ++i){
    for(int j = 0; j <= 9; ++j){
      for(int k = 0; k <= 9; ++k){
        for(int a = 0; a <= 9; ++a){
          for(int b = 0; b <= 9; ++b){
              int num = i + 10 * j + 100 * k + 1000 * a + 10000 * b;
              if(check(num)){
                cout << num << endl;
                return 0;
              }
          }
        }
      }
    }
  }
  if(check(100000))cout << 100000 << endl;
  cout << -1 << endl;
}
