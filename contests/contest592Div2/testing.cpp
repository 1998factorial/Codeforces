#include <iostream>
#include <time.h>
#include <cstring>
using namespace std;

int main(){
  srand(time(NULL));
  int n = rand() % 100 + 100;
  cout << n << " " << (rand() % 100 + 100) << endl;
  for(int i = 1; i <= n; ++i){
    int r = rand() % 2;
    if(r % 2)cout << "B";
    else cout << "W";
  }
  cout << endl;
  return 0;
}
