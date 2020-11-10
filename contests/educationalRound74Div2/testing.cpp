#include <iostream>
#include <time.h>
#include <cstring>
using namespace std;

int main(){
  int n = 100000 , m = 20;
  srand(time(NULL));
  string c;
  for(int i = 0; i < n; ++i){
    c += 'a' + (rand() % m);
  }
  cout << n << " " << m << endl;
  cout << c << endl;
  return 0;
}
