#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl
using namespace std;
typedef long long ll;
typedef pair<int , int> ii;


int main(){
  int T = 10;
  srand(time(NULL));
  cout << T << endl;
  while(T--){
    int N = 4;
    cout << N << endl;
    for(int i = 1; i <= N; ++i){
      int sz = rand() % 10 + 1;
      for(int j = 1; j <= sz; ++j){
        int k = rand() % 3;
        if(k == 0)cout << "R";
        if(k == 1)cout << "P";
        if(k == 2)cout << "S";
      }
      cout << endl;
    }
  }
}
