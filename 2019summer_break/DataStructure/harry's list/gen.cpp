#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl
using namespace std;
typedef long long ll;
typedef pair<int , int> ii;

int main(){
  vector<int> a = {1 , 2 , 3 , 5 , 6};
  auto it = lower_bound(a.begin() , a.end() , 7);
  int n = it - a.begin();
  cout << n << endl;
  cout << *it << endl;
}
