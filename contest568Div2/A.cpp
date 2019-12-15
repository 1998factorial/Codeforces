#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdio>
#include <vector>
using namespace std;

int d;

int main(){
  vector<int> a(3);
  cin >> a[0] >> a[1] >> a[2] >> d;
  sort(a.begin(),a.end());
  int x1 = abs(a[0] - a[1]);
  int x2 = abs(a[1] - a[2]);
  //cout << x1 << "  " << x2 << endl;
  int ret = (x1 >= d ? 0 : d - x1) + (x2 >= d ? 0 : d - x2);
  if(a[2] - a[0] >= 2*d){
    //cout <<  abs((a[2] + a[0])/2 - a[1]) << endl;
    ret = min(ret , abs((a[2] + a[0])/2 - a[1]));
  }
  cout << ret << endl;
}
