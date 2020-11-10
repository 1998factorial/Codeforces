#include <bits/stdc++.h>
using namespace std;
typedef long long ll;


ll a , b;

int main(){
  cin >> a >> b;
  while(a != 0 && b != 0){
    if(a >= 2ll * b){
      a -= 2ll * b;
    }
    else{
      if(b >= 2ll * a){
        b -= 2ll * a;
      }
      else{
        break;
      }
    }
  }
  cout << a << " " << b << endl;
}
