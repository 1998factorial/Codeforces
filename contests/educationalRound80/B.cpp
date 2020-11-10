#include <iostream>
using namespace std;
typedef long long ll;

/*
  a * b + a + b = con(a , b)
  a * b + a + b = a * 10 ^ |b| + b
  b + 1 = 10 ^ |b|
  regard less of a , only care about what b is
  for each good b , add A
*/

ll A , B;

int main(){
  int T; cin >> T;
  while(T--){
    cin >> A >> B;
    ll ret = 0;
    int x = 10;
    for(int i = 1; i <= 9; ++i){
      if(x - 1 <= B){
        ret += A;
      }
      x = 10 * x;
    }
    cout << ret << endl;
  }
}
