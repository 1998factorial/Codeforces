#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl
using namespace std;
typedef long long ll;
typedef pair<int , int> ii;

int a[105];

int main(){
  int t;
  cin >> t;
  while(t--){
    int N; cin >> N;
    vector<int> even , odd;
    for(int i = 1; i <= N; ++i){
      cin >> a[i];
      if(a[i] % 2 == 0)even.push_back(i);
      else odd.push_back(i);
    }
    if(even.size()){
      cout << 1 << endl;
      cout << even.back() << endl;
    }
    else if(odd.size() > 1){
      cout << 2 << endl;
      cout << odd[0] << " " << odd[1] << endl;
    }
    else{
      cout << -1 << endl;
    }
  }
}
