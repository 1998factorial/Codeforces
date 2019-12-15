#include <iostream>
#include <cstdio>
using namespace std;

const int maxn = 2e5 + 10;
int n , k;
string a;

int main(){
  cin >> n >> k;
  cin >> a;
  if(n == 1 && k > 0){
    cout << 0 << endl;
    return 0;
  }
  for(int i = 0; i < n; ++i){
    if(k > 0){
      if(i == 0){
        cout << 1;
        if(a[i] > '1')--k;
      }
      else{
        cout << 0;
        if(a[i] > '0')--k;
      }
    }
    else{
      cout << a[i];
    }
  }
  cout << endl;
  return 0;
}
