#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl
using namespace std;
typedef long long ll;
typedef pair<int , int> ii;

unsigned long long A , B;
/*
  magic : A + B = ((A & B) << 1) + (A ^ B)
  so A - B = (X & Y) << 1
*/

int main(){
  cin >> A >> B;
  if((A - B) % 2 == 1 || A < B){
    cout << -1 << endl;
    return 0;
  }
  unsigned long long C = (A - B) >> 1;
  unsigned long long X = C;
  if((X ^ (A - X)) != B){
    cout << -1 << endl;
  }
  else{
    cout << X << " " << A - X << endl;
  }
}
