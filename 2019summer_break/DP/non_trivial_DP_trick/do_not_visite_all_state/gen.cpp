#include <iostream>
#include <time.h>
using namespace std;

int main(){
  srand(time(NULL));
  int N = 3e4;
  cout << N << " " << 140 << endl;
  for(int i = 1; i <= N; ++i){
    cout << rand() % N + 1 << endl;
  }
}
