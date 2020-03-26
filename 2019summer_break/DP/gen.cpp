#include <bits/stdc++.h>
using namespace std;

int main(){
  srand(time(NULL));
  int N = 500;
  cout << N << endl;
  for(int i = 1; i <= N; ++i){
    int l = rand() % 1000000000 + 1;
    int r = rand() % 1000000000 + 1;
    if(l > r)swap(l , r);
    cout << l << " " << r << endl;
  }
  cout << endl;
}
