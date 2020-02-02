#include <iostream>
#include <cstring>
using namespace std;

int main(){
  string a;
  int n;
  cin >> n;
  cin >> a;
  int cnt = 0;
  for(int i = 0; i < n; ++i){
    cnt += a[i] == 'L';
  }
  cout << (n - cnt) + cnt + 1 << endl;
}
