#include <iostream>
using namespace std;

int main(){
  int a , b , c , d;
  cin >> a >> b >> c >> d;
  if(
    a + b == c + d ||
    a + c == b + d ||
    a + d == c + b ||
    a == b + c + d ||
    b == a + c + d ||
    c == b + a + d ||
    d == b + c + a
  ){
    cout << "YES\n";
  }
  else{
    cout << "NO\n";
  }
  return 0;
}
