#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl
using namespace std;
typedef long long ll;
typedef pair<int , int> ii;

ll A , B;
/*
  magic : A + B = ((A & B) << 1) + (A ^ B)
  so A - B = (X & Y) << 1
*/

int main(){
  cin >> A >> B;
  for(ll x = 0; x <= A; ++x){
    if((x ^ (A - x)) == B){
      cout << x << " " << A - x << endl;
      return 0;
    }
  }
  cout << -1 << endl;
}
