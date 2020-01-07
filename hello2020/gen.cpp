#include <iostream>
#include <time.h>
using namespace std;
int main(){
  srand(time(NULL));
  int N = 10;
  cout << N << endl;
  for(int i = 1; i <= N; ++i){
    int len = rand() % 100 + 1;
    cout << len << " ";
    for(int j = 1; j <= len; ++j){
      cout << rand() % 6 + 1 << " ";
    }
    cout << endl;
  }
}
