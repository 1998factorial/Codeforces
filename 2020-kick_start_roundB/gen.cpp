#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl
using namespace std;
typedef long long ll;
typedef pair<int , int> ii;


int main(){
  int T;
  T = 100;
  srand(time(NULL));
  cout << T << endl;
  for(int t = 1; t <= T; ++t){
    int N = 1e2 , M = 1e2;
    int L = rand() % 100 + 1 , U = rand() % 100 + 1 , R = rand() % 100 + 1 , D = rand() % 100 + 1;
    if(L > R)swap(L , R);
    if(U > D)swap(U , D);
    cout << N << " " << M << " " << L << " " << U << " " << R << " " << D << endl;
  }
}
