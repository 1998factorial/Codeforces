#include <bits/stdc++.h>
using namespace std;

int main(){
  int t = 10;
  int R = 3 , C = 3;
  cout << t << endl;
  srand(time(NULL));
  for(int x = 1; x <= t; ++x){
    cout << R << " " << C << endl;
    for(int i = 1; i <= R; ++i){
      for(int j = 1; j <= C; ++j){
        cout << rand() % 10 + 1 << " ";
      }
      cout << endl;
    }
  }
}
