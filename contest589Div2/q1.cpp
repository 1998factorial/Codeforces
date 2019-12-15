#include <iostream>
#include <unordered_map>
using namespace std;

int l , r;

bool check(int x){
  if(x > r || x < l)return false;
  unordered_map<int , int> cnt;
  while(x){
    if(cnt[x % 10] > 0)return false;
    cnt[x % 10]++;
    x /= 10;
  }
  return true;
}

// enumerate all 5 digits , check  -> O(10 ^ 6) ok

int main(){
  cin >> l >> r;
  for(int a = 0; a < 10; ++a){
    for(int b = 0; b < 10; ++b){
      for(int c = 0; c < 10; ++c){
        for(int d = 0; d < 10; ++d){
          for(int e = 0; e < 10; ++e){
            int num = a + 10 * b + 100 * c + 1000 * d + 10000 * e;
            if(check(num)){
              cout << num << endl;
              return 0;
            }
          }
        }
      }
    }
  }
  cout << -1 << endl;
}
