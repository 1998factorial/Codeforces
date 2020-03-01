#include <bits/stdc++.h>
using namespace std;

int mod = 5e8;

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int N = 1e6 , M = 200000;
  //cout << N << " " << M << endl;
  cout << N << endl;
  srand(time(NULL));
  /*for(int i = 1; i <= N; ++i){
    int l = rand() % mod + 1 + 5e8, r = rand() % mod + 1 + 5e8;
    cout << min(l , r) << " " << max(l , r) << endl;
  }
  for(int i = 1; i <= M; ++i){
    int l = rand() % mod + 1 , r = rand() % mod + 1 , c = rand() % mod + 1;
    cout << min(l , r) << " " << max(l , r) << " " << c << endl;
  }*/
  for(int i = 1; i <= N; ++i){
    cout << i << " ";
  }
  cout << endl;
}
