#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl
using namespace std;
typedef long long ll;
typedef pair<int , int> ii;
typedef unsigned long long ull;

int main(){
  int T = 5;
  srand(time(NULL));
  cout << T << endl;
  for(int t = 1; t <= T; ++t){
    int N = 10 , H = rand() % 100 + 1;
    cout << N << " " << H << endl;
    for(int i = 1; i <= N; ++i){
      cout << rand() % 20 + 1 << " ";
    }
    cout << endl;
    for(int i = 1; i <= N; ++i){
      cout << rand() % 20 + 1 << " ";
    }
    cout << endl;
  }
}
