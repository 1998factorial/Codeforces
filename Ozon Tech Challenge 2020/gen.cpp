#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl
using namespace std;
typedef long long ll;
typedef pair<int , int> ii;

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  srand(time(NULL));
  int N = 2e5;
  cout << N << endl;
  for(int i = 1; i <= N; ++i)cout << rand() << " ";
  cout << endl;
}
