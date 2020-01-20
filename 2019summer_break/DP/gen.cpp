#include <iostream>
#include <time.h>
using namespace std;

int main(){
  srand(time(NULL));
  int N = rand() % 100000 + 10 , X = rand() % 30 - 15;
  cout << N << " " << X << endl;
  for(int i = 1; i <= N; ++i){
    cout << rand() % 10000 - 5 << " ";
  }
  cout << endl;
}
