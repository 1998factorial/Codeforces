#include <bits/stdc++.h>
using namespace std;

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int N = 1e4;
  long long K = 1e18;
  srand(time(NULL));
  cout << N << " " << K << endl;
  for(int i = 1; i <= N; ++i){
    int row = rand() % 3;
    long long l = rand() % (K - 1) + 1;
    long long r = rand() % (K - 1) + 1;
    if(l > r)swap(l , r);
    cout << row << " " << l << " " << r << endl;
  }
}
