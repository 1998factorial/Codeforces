#include <iostream>
#include <time.h>
using namespace std;
int main(){
  int N = 25 , p = 10;
  cout << N << " " << p << endl;
  srand(time(NULL));
  for(int i = 1; i <= N; ++i){
    cout << rand() % 100 << " ";
  }
  cout << endl;
}
