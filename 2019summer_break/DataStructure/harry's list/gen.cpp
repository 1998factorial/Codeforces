#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl
using namespace std;
typedef long long ll;
typedef pair<int , int> ii;

int main(){
  map<int , int , greater<int>> mp;
  for(int i = 1; i <= 5; ++i){
    mp[i] = 6 - i;
  }
  for(auto& it : mp)cout << it.first << " " << it.second << endl;
}
